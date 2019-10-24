// WaitTimerInfo.cpp: implementation of the CWaitTimerInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "WaitTimerInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


DWORD __stdcall CommWaitTimer(void *lpdata)
{


	CWaitTimerInfo *TimerInfo = (CWaitTimerInfo *) lpdata;
	CCommOperations *commObject = TimerInfo->commObject;
	CLADAControlModuleDoc *pDoc = TimerInfo->pDoc;
	CLADAControlModuleView *pView = TimerInfo->pView;
	BOOL *InCommMode = TimerInfo->InCommMode;
	delete lpdata;
	
	SYSTEMTIME SystemTime;
	GetSystemTime(&SystemTime);
	FILETIME DueTime;
	SystemTimeToFileTime(&SystemTime,&DueTime);
	
	HANDLE DataTimer = CreateWaitableTimer(NULL,FALSE,"GetCR10DataTimer");
	pDoc->DataTimer = DataTimer;
	if (!SetWaitableTimer(DataTimer,(LARGE_INTEGER*) &DueTime,1000,NULL,NULL,TRUE))
	{
		AfxMessageBox( "Failed to set timer for new thread!", 
                  MB_ICONEXCLAMATION | MB_OK ) ;
		return ( FALSE ) ;
	}
	BOOL needSetJCommand = TRUE;

	while (*InCommMode)
	{
		WaitForSingleObject( DataTimer, INFINITE );
		pDoc->ThreadsInFunction++;
		pDoc->StartCommBlock();
		pDoc->ThreadsInCommunication++;

		DWORD sTime = timeGetTime();
		while (timeGetTime() - sTime < pDoc->DelayTime);

		if (*InCommMode)
		{
		
			if (commObject == NULL){
				commObject = new CCommOperations(FALSE);
					
				if (commObject->IsConnected()){
					pView->m_Connected.SetBitmap((HBITMAP)pView->ConnectedBMP->m_hObject);
					pView->m_ConnStatus.SetWindowText("Connected");
				}
				else
				{
					pView->m_ConnStatus.SetWindowText("Trying to Connect");
					delete commObject;
					commObject = NULL;
				}
			}
			if (commObject)
			{
				for (int LocPos = 0; pDoc->nData - LocPos > 0; LocPos += 62){
					int LocsToGet = pDoc->nData - LocPos;
					if (LocsToGet > 62)
						LocsToGet = 62;

					do {
						int t = 0;
						if (pDoc->nData > 62 || needSetJCommand )
						{
							for (t = 0; t < 5 && !commObject->SetJCommand(
								FALSE, 
								FALSE, 
								TRUE, 
								&pDoc->InputLocationSaveList[LocPos], 
								LocsToGet); t++);
							needSetJCommand = FALSE;
						}

						for ( ; t < 5 && !commObject->ExecuteKCommand(TRUE, LocsToGet); t++ );
						
						if (t < 5)
							break;
						
						Sleep(200);
						if (!(commObject->PingCR10(20) || commObject->PingCR10(50) || commObject->PingCR10(200) || commObject->PingCR10(500)))
						{
							// an error occured
							pView->m_ConnStatus.SetWindowText("Trying to Connect");
							if (!commObject->Reconnect()){
								commObject->EndCR10Comm();
								delete commObject;
								commObject = NULL;
								pView->m_Connected.SetBitmap((HBITMAP)pView->NConnectedBMP->m_hObject);
								break;
							}
							else
							{
								pView->m_ConnStatus.SetWindowText("Connected");
								pView->m_Connected.SetBitmap((HBITMAP)pView->ConnectedBMP->m_hObject);
							}
						}
					} while (true);

					if (commObject)
						commObject->ProcessInputLocations(&pDoc->newData[LocPos], LocsToGet);
								
				}
				if (commObject){
					pDoc->AddData(pDoc->newData,CTime::GetCurrentTime());
					pDoc->NewDataExists = TRUE;
				}
			}
		}
		pDoc->ThreadsInCommunication--;
		pDoc->EndCommBlock();
		pDoc->ThreadsInFunction--;
		pDoc->RTime = timeGetTime() - sTime;
	}
   // get rid of event handle
   CloseHandle( DataTimer ) ;
   // clear information in structure (kind of a "we're done flag")
	pDoc->DataTimer = NULL;
   return( TRUE ) ;

} // end of CommWatchProc()
