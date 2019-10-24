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
	pDoc->ToBeServicedData = CreateEvent(NULL,TRUE,FALSE,"TO_BE_SERVICED");
	pDoc->ServicingData = CreateEvent(NULL,TRUE,FALSE,"SERVICING");
	pDoc->TempServicing = CreateEvent(NULL,TRUE,FALSE,"TEMP_SERVICING");
	int nInThread = 0;
	BOOL DataError;

	int nGetLocList;
	int GetLocationList[256];
	int ListIndex[256];

	while (*InCommMode)
	{
		WaitForSingleObject( pDoc->DataRequest, INFINITE );
		ResetEvent( pDoc->DataRequest );
		
		if (!*InCommMode)
			break;
		
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
		Swap( pDoc->ThreadsToBeServiced, pDoc->ThreadsServicing );
		Swap( pDoc->ToBeServicedData, pDoc->ServicingData );
		// end critical section
		LeaveCriticalSection(&pDoc->CommCriticalSection);
		
		DataError = FALSE;

		if (*InCommMode && !pDoc->m_IsCommPaused && pDoc->m_nActiveRequests && nInThread == 1) // if any input locations have been requested for retrieval
			//nGetLocList 
		{
			
#ifdef _DEBUG
			if (pDoc->commObject == NULL)
			{
				pDoc->m_ErrorFiles->OpenFiles();
				pDoc->m_ErrorFiles->WriteHistory("Data retrieval error","commObject == NULL in commWaitTimer");
				pDoc->m_ErrorFiles->CloseFiles();	
				break;
			}
#endif
			
			if (pDoc->ApplicationIsOpen)
			{
				if (pDoc->commObject)
				{
					pDoc->m_Reads++;
					if (*InCommMode && !pDoc->m_IsCommPaused &&
						!GetData(GetLocationList, nGetLocList, ListIndex, pDoc, pDoc->commObject ))
					{
						// couldn't retrieve data...
						pDoc->m_Errors++;
						DataError = TRUE;
						if (PossiblyDisconnected)
						{
							// shut down connection...
							// write to error log
							// display error message
							pDoc->StopComm();
							
						}
					}
				}
			
				if (!DataError)
				{ 
					// START CRITICAL SECTION...
					EnterCriticalSection(&pDoc->CommCriticalSection);
					while ( pDoc->ThreadsServicing > 0 ) // if there are any input location requests...
					{
						SetEvent( pDoc->ServicingData );
						Sleep(0);
					}
					// END CRITICAL SECTION...
					LeaveCriticalSection(&pDoc->CommCriticalSection);
					
					if (pDoc->ThreadsToBeServiced == 0)
					{
						
						pDoc->CompleteRequests();
						if (pDoc->m_pMainView)
							pDoc->m_pMainView->GetDlgItem(IDC_CR10TIME)->SetWindowText(pDoc->commObject->timeBuf);
					}
					
				}
			}
		}
		nInThread--;
	}
	// get rid of event handle
	CloseHandle( pDoc->DataRequest ) ;
	CloseHandle( pDoc->ToBeServicedData ) ;
	CloseHandle( pDoc->ServicingData ) ;
	// clear information in structure (kind of a "we're done flag")

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
			
		commObject->StartCommOperation();
				
		for (t = 0; t < 5 && !commObject->SetJCommand(
			FALSE, 
			FALSE, 
			TRUE, 
			&GetLocList[LocPos], 
			LocsToGet); t++);
						

		for ( ; t < 5; t++ )
		{
			if (commObject->ExecuteKCommand(TRUE, LocsToGet) &&
				pDoc->commObject->CheckSignature())
				break;

			commObject->ForceSetJCommand = true;
			commObject->SetJCommand(
				FALSE, 
				FALSE, 
				TRUE, 
				&GetLocList[LocPos], 
				LocsToGet);
			commObject->ForceSetJCommand = false;
		}
		memcpy(dataBuf,readBuf,readBufPos);
		commObject->EndCommOperation();
		
		if (t == 5)
		{
			// write to error log...
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
		return FALSE;

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
					pDoc->m_ErrorFiles->OpenFiles();
					char buf[200];
					wsprintf(buf,"Data validation stopped on input location #%i.  Value returned was: %s",pDoc->m_GetLocationList[l], ValueToString(value));
					pDoc->m_ErrorFiles->WriteHistory(CString("Data Collection"),CString(buf));
					pDoc->m_ErrorFiles->CloseFiles();
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
