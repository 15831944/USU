// This is Version 1.0 PLEASE DOCUMENT CHANGES
// WaitTimerInfo.cpp: implementation of the CWaitTimerInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "WaitTimerInfo.h"
#include "HistoryClass.h"
#include "Ladastrings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL GetData(int * GetLocList, int nGetLocList, int * GetLocationListIndex, CLADAControlModuleDoc *pDoc, CCommOperations *commObject);
BOOL ValidateData(CLADAControlModuleDoc * pDoc, int * GetLocationListIndex, int LocPos, int LocsToGet);
int ThreadsInCommWaitTimer = 0;
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern BOOL PossiblyDisconnected;
extern UINT NotificationBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox
extern void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char * AdditionalMessage = NULL);
extern CString IntToString(int number);
template <class T> Swap (T &A, T &B)
{
	T temp = A;
	A = B;
	B = temp;
}

DWORD __stdcall CommWaitTimer(void *lpdata)
{
	ThreadsInCommWaitTimer++;

	CWaitTimerInfo *TimerInfo = (CWaitTimerInfo *) lpdata;
	//CCommOperations **commObject = &(*TimerInfo->commObject);
	CLADAControlModuleDoc *pDoc = TimerInfo->pDoc;
	BOOL *InCommMode = TimerInfo->InCommMode;
	delete lpdata;
	
	pDoc->DataRequest = CreateEvent(NULL,TRUE,FALSE,"DATA_REQUEST");
	//pDoc->ToBeServicedData = CreateEvent(NULL,TRUE,FALSE,"TO_BE_SERVICED");
	//pDoc->ServicingData = CreateEvent(NULL,TRUE,FALSE,"SERVICING");
	pDoc->DataCompletion = CreateEvent(NULL,TRUE,FALSE,"SERVICING");
	
	int nInThread = 0;
	
	int nGetLocList;
	int GetLocationList[256];
	int ListIndex[256];

	while (*InCommMode)
	{
		pDoc->GotData = 0;
		WaitForSingleObject( pDoc->DataRequest, INFINITE );
		
		pDoc->GotData = 1;

		//Sleep(0);

		if (!*InCommMode)
			break;
		
		while (pDoc->m_IsCommPaused)
			Sleep(0);

		// START CRITICAL SECTION...
		EnterCriticalSection(&pDoc->CommCriticalSection);
		
		nInThread++;
		// critical section...
		nGetLocList = pDoc->m_nGetLocList;
#ifdef _DEBUG
		if (nGetLocList > 255)
			MessageBox("Number of input locations requested in CommWait > 255","Fatal Error",MB_ICONSTOP);
#endif
		memcpy(GetLocationList,pDoc->m_GetLocationList,sizeof(int)*nGetLocList);
		memcpy(ListIndex,pDoc->m_GetLocationListIndex,sizeof(int)*nGetLocList);
		//Swap( pDoc->ThreadsToBeServiced, pDoc->ThreadsServicing );
		//Swap( pDoc->ToBeServicedData, pDoc->ServicingData );
		pDoc->GotData = 3;
		ResetEvent( pDoc->DataRequest );
		pDoc->GotData = 4;
		// end critical section
		ResetEvent( pDoc->DataCompletion );
		LeaveCriticalSection(&pDoc->CommCriticalSection);
		
		
		if (*InCommMode && pDoc->m_nActiveRequests && nInThread == 1) // if any input locations have been requested for retrieval
			//nGetLocList 
		{
			pDoc->GotData = 5;
			if (pDoc->ApplicationIsOpen && pDoc->commObject)
			{
				pDoc->GotData = 7;
				pDoc->GotData = TRUE;
				pDoc->m_Reads++;
				
				if (*InCommMode && 
					!GetData(GetLocationList, nGetLocList, ListIndex, pDoc, pDoc->commObject ))
				{
					pDoc->GotData = 8;
					pDoc->DataError = TRUE; 
					// couldn't retrieve data...
					pDoc->m_ErrorFiles->WriteHistory("Error","GetData in CommWatchProc failed");
					
					pDoc->m_Errors++;
				}
				else
				{
					pDoc->GotData = 9;
					pDoc->DataError = FALSE;
				}
				
				if (pDoc->nInGetInputLocations)
				{
					pDoc->GotData = 10;
					SetEvent( pDoc->DataCompletion );
					Sleep(0);
				}

				if (pDoc->DataError || !*InCommMode)
				{
					// flush requests
					pDoc->GotData = 11;
					pDoc->FlushAllRequests();
					pDoc->m_ErrorFiles->WriteHistory("Error","All requests flushed, DataError in CommWatchProc == TRUE");
					if (PossiblyDisconnected)
					{
						// shut down connection...
						// write to error log
						pDoc->m_ErrorFiles->WriteHistory("Error","PossiblyDisconnected in CommWatchProc == TRUE");
						// display error message
						pDoc->StopComm();
					}

				}
				else
				{
					pDoc->GotData = 12;
					pDoc->CompleteRequests();
					if (pDoc->m_pMainView)
						pDoc->m_pMainView->GetDlgItem(IDC_CR10TIME)->SetWindowText(pDoc->commObject->timeBuf);
				}
			}
			pDoc->GotData = 13;
		}

		if (pDoc->nInGetInputLocations)
		{
			pDoc->GotData = 14;
			SetEvent( pDoc->DataCompletion );
			Sleep(0);
			pDoc->GotData = 15;
		}
		nInThread--;
		pDoc->GotData = 16;
	}
	// get rid of event handle
	CloseHandle( pDoc->DataRequest ) ;
	CloseHandle( pDoc->DataCompletion );
	//CloseHandle( pDoc->ToBeServicedData ) ;
	//CloseHandle( pDoc->ServicingData ) ;
	// clear information in structure (kind of a "we're done flag")
	
	pDoc->FlushAllRequests();

	ThreadsInCommWaitTimer--;
	if (PossiblyDisconnected)
		MessageBox(IDS_M_CONNECTION_BROKEN,IDS_PROGRAM_NAME,MB_ICONINFORMATION);

	return( TRUE ) ;

} // end of CommWatchProc()



BOOL GetData(int * GetLocList, int nGetLocList, int * GetLocationListIndex, CLADAControlModuleDoc *pDoc, CCommOperations *commObject)
{
	char dataBuf[1000];
	int LocPos = 0; 
	int nSuccessiveFailures = 0;

	do
	{
		int LocsToGet = nGetLocList - LocPos;
		
		if (LocsToGet > 62)
			LocsToGet = 62;
						
		//do {
		int t = 0;
			
		if (!commObject->StartCommOperation(11))
		{
			commObject->EndCommOperation();
			pDoc->m_ErrorFiles->WriteHistory("Error","GetData in CommWatchProc failed.  StartCommOperation failed");
			return FALSE;
		}
				
		for (t = 0; t < 5 && !commObject->SetJCommand(
			FALSE, 
			FALSE, 
			nGetLocList, 
			&GetLocList[LocPos], 
			LocsToGet); t++)
		{
			commObject->WriteToCommLog("Error- J command failed");
			Sleep(20);	
		}

		if (t == 5)
		{
			commObject->WriteToCommLog("Error- GetData in CommWatchProc failed.  J command executed 5 times");
			pDoc->m_ErrorFiles->WriteHistory("Error","GetData in CommWatchProc failed.  J command executed 5 times");
			return FALSE;
		}				

		for (t = 0 ; t < 5; t++ )
		{
			if (commObject->ExecuteKCommand(TRUE, LocsToGet))
			{
				if (pDoc->commObject->CheckSignature())
				{
					break;
				}
				else
				{
					commObject->WriteToCommLog("Error- CheckSignature() after K command failed");
					Sleep(20);
				}
			}
			else
			{
				commObject->WriteToCommLog("Error- K command failed");
				Sleep(20);
			}

		}
		memcpy(dataBuf,readBuf,readBufPos);
		commObject->EndCommOperation();
		
		if (t == 5)
		{
			commObject->WriteToCommLog("Error- GetData in CommWatchProc failed.  K command executed 5 times");
			pDoc->m_ErrorFiles->WriteHistory("Error","GetData in CommWatchProc failed.  K command executed 5 times");
			return FALSE;
		}
		
		if (commObject)
		{
			commObject->ProcessCR10Time(pDoc);
			if (LocsToGet)
			{
				if (commObject->ProcessInputLocations(dataBuf, pDoc->newData, &GetLocList[LocPos], LocsToGet))
				{
					if (ValidateData(pDoc, GetLocationListIndex, LocPos, LocsToGet))
						nSuccessiveFailures = 0;
					else
						nSuccessiveFailures++;
				}
				else
					nSuccessiveFailures++;
			}
			
		}
		
		if (nSuccessiveFailures == 0)
			LocPos += 62;

	} while (commObject && nSuccessiveFailures < 3 &&
			 nGetLocList - LocPos > 0);

	if (nSuccessiveFailures)
	{
		pDoc->m_ErrorFiles->WriteHistory(CString("Error"),CString("GetData in CommWatchProc failed.  nSuccessiveFailures = ") + CString(char(nSuccessiveFailures + '0')));
		return FALSE;
	}

	pDoc->ResetGetLocList();
	
	return TRUE;
}

BOOL ValidateData(CLADAControlModuleDoc * pDoc, int * GetLocationListIndex, int LocPos, int LocsToGet)
{
	double min;
	double max;
	int index;
	double value;
	BOOL noBadData = TRUE;
	for (int l = LocPos; l < LocPos + LocsToGet; l++)
	{
		index = GetLocationListIndex[l];
		if (pDoc->m_HasMinMax[index] && pDoc->m_DoValidation[index])
		{
			//InputLocValue[InputList[i] - 1] = result; 
			min = pDoc->m_minValues[index];
			max = pDoc->m_maxValues[index];
			value = pDoc->newData[ pDoc->m_GetLocationList[l] - 1 ];
			
			//if ( value != -99999.00 && (value < min || value > max))
			if ( value < min || value > max )
			{ // bad data
				if (pDoc->m_HasMinMax[index] == 3)
				{
					// 
					char buf[200];
					wsprintf(buf,"Data validation stopped on input location #%i.  Value returned was: %s",pDoc->m_GetLocationList[l], ValueToString(value));
					pDoc->m_ErrorFiles->WriteHistory(CString("Data Collection"),CString(buf));
					pDoc->m_DoValidation[index] = FALSE;
					pDoc->m_HasMinMax[index] = 1;
				}
				else
				{
					noBadData = FALSE;
					pDoc->m_HasMinMax[index]++;
				}
				
			}
			else
			{
				pDoc->m_HasMinMax[index] = 1;
			}
		}
	}
	return noBadData;
}
