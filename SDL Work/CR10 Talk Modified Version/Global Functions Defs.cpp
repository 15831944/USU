#include "global defs.h"

void LoadInitData(BOOL LoadFromFile){

	if (!LoadFromFile){
		// the file didn't exist
		char locationName[25];
		for (int i = 0; i < MAX_DISPLAY_INPUT_LOCATIONS; i++){
			InputLocScreenList[i] = i + 1;
			InputLocSaveList[i] = i + 1;
		}
		for (i = 0; i < 8; i++){
			//FlagNames[8][2][30];
			toggleFlags[i][USERFLAGS] = (i % 2 == 0) * CONTINUAL;
			toggleFlags[i][PORTFLAGS] = (i % 2 == 1) * CONTINUAL;
			wsprintf(locationName, "%1i: [no name]", i + 1);
			//strcpy(FlagNames[i][USERFLAGS], locationName);
			//strcpy(FlagNames[i][PORTFLAGS], locationName);
			FlagNames[i][USERFLAGS] = locationName;
			FlagNames[i][PORTFLAGS] = locationName;
			toggleFlagsFreqLevel[i][USERFLAGS] = 0;
			toggleFlagsFreqLevel[i][PORTFLAGS] = 0;
		}
		for (i = 0; i < N_UPDATEABLE_ITEMS; i++){
			UpdateItems[i] = TRUE;
			FreqLevel[i] = 0;
		}
		DoToggleFlags[USERFLAGS] = TRUE;
		DoToggleFlags[PORTFLAGS] = FALSE;
		ModifyWhichFlags = USERFLAGS;

		InputLocScreenRequests = 15;
		InputLocSaveRequests = 15;
		FreqLevel[SAVE_LOCATIONS] = 7; // once every five minutes
		DSP = 1;
		LastDSP = 0;
		FStartRetrievalFromCurrentPosOnStart = FALSE;
		defaultPort = 0;
		SaveFinalStorage = FALSE;
		nPEvents = 0;
		
		for (i = 1; i <= MAX_INPUT_LOCATIONS; i++){
			wsprintf(locationName, "%3i:[no name]", i);
			//strcpy(AvailableInputLocations[i - 1], locationName);
			AvailableInputLocations[i-1] = locationName;
		}
	}
	else {
		HANDLE fileIn;
		fileIn = CreateFile("defaults.dat", 
			GENERIC_READ, 
			0, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
	
		if (fileIn == INVALID_HANDLE_VALUE){
			CloseHandle(fileIn);
			//LoadFromFile = FALSE;
			//GetLastError();
			LoadInitData(FALSE);
			return;
		}
		DWORD bytesRead;
		//DWORD fileSize = GetFileSize(fileIn, NULL);
		
		/*
		if (fileSize !=  8416 ){
			CloseHandle(fileIn);
			LoadInitData(FALSE);
			return;
		}
		*/

		int readSize;
		size_t dataSize = sizeof(size_t);
		
		ReadFile(fileIn,&InputLocScreenRequests,sizeof(InputLocScreenRequests),&bytesRead,NULL);
		ReadFile(fileIn,&InputLocSaveRequests,sizeof(InputLocSaveRequests),&bytesRead,NULL);
		ReadFile(fileIn,&LastDSP,sizeof(LastDSP),&bytesRead,NULL);
		ReadFile(fileIn,&FStartRetrievalFromCurrentPosOnStart,sizeof(FStartRetrievalFromCurrentPosOnStart),&bytesRead,NULL);
		ReadFile(fileIn,&defaultPort,sizeof(defaultPort),&bytesRead,NULL);
		ReadFile(fileIn,&ModifyWhichFlags,sizeof(ModifyWhichFlags),&bytesRead,NULL);
		ReadFile(fileIn,&SaveFinalStorage,sizeof(SaveFinalStorage),&bytesRead,NULL);
		ReadFile(fileIn,&nPEvents,sizeof(nPEvents),&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,UpdateItems,readSize,&bytesRead,NULL);

		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,toggleFlags,readSize,&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,DoToggleFlags,readSize,&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,FlagNames,readSize,&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,toggleFlagsFreqLevel,readSize,&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,InputLocScreenList,readSize,&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,InputLocSaveList,readSize,&bytesRead,NULL);
		
		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,FreqLevel,readSize,&bytesRead,NULL);

		ReadFile(fileIn,&readSize,dataSize,&bytesRead,NULL);
		ReadFile(fileIn,AvailableInputLocations,readSize,&bytesRead,NULL);
	/*
		ReadFile(fileIn,InputLocScreenList,sizeof(InputLocScreenList),&bytesRead,NULL);
		ReadFile(fileIn,UpdateItems,sizeof(UpdateItems),&bytesRead,NULL);
		ReadFile(fileIn,FreqLevel,sizeof(FreqLevel),&bytesRead,NULL);
		ReadFile(fileIn,&InputLocScreenRequests,sizeof(InputLocScreenRequests),&bytesRead,NULL);
		ReadFile(fileIn,&LastDSP,sizeof(LastDSP),&bytesRead,NULL);
		ReadFile(fileIn,&FStartRetrievalFromCurrentPosOnStart,sizeof(FStartRetrievalFromCurrentPosOnStart),&bytesRead,NULL);
		ReadFile(fileIn,&defaultPort,sizeof(defaultPort),&bytesRead,NULL);
		ReadFile(fileIn,AvailableInputLocations,sizeof(AvailableInputLocations),&bytesRead,NULL);
		ReadFile(fileIn,toggleFlags,sizeof(toggleFlags),&bytesRead,NULL);
		ReadFile(fileIn,DoToggleFlags,sizeof(DoToggleFlags),&bytesRead,NULL);
		ReadFile(fileIn,&ModifyWhichFlags,sizeof(ModifyWhichFlags),&bytesRead,NULL);
		ReadFile(fileIn,FlagNames,sizeof(FlagNames),&bytesRead,NULL);
		ReadFile(fileIn,toggleFlagsFreqLevel,sizeof(toggleFlagsFreqLevel),&bytesRead,NULL);
*/
		CloseHandle( fileIn );
	}
	
}

void WriteInitData(){

	SetCurrentDirectory(workingDirectory);

	HANDLE fOut = CreateFile("defaults.dat", 
			GENERIC_WRITE | DELETE, 
			0, 
			NULL, 
			TRUNCATE_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
	
	if (fOut == INVALID_HANDLE_VALUE){
		DisplayErrorMessage(GetLastError());
		fOut = CreateFile("defaults.dat", 
			GENERIC_WRITE | DELETE, 
			0, 
			NULL, 
			CREATE_NEW, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL);
	}

	if (fOut == INVALID_HANDLE_VALUE){
		DisplayErrorMessage(GetLastError());
		return;
	}

	DWORD bytesWritten;
	size_t dataSize = sizeof(size_t);
	size_t szData;
	
	WriteFile(fOut,&InputLocScreenRequests,sizeof(InputLocScreenRequests),&bytesWritten,NULL);
	WriteFile(fOut,&InputLocSaveRequests,sizeof(InputLocScreenRequests),&bytesWritten,NULL);	
	WriteFile(fOut,&LastDSP,sizeof(LastDSP),&bytesWritten,NULL);
	WriteFile(fOut,&FStartRetrievalFromCurrentPosOnStart,sizeof(FStartRetrievalFromCurrentPosOnStart),&bytesWritten,NULL);
	WriteFile(fOut,&defaultPort,sizeof(defaultPort),&bytesWritten,NULL);
	WriteFile(fOut,&ModifyWhichFlags,sizeof(ModifyWhichFlags),&bytesWritten,NULL);
	WriteFile(fOut,&SaveFinalStorage,sizeof(SaveFinalStorage),&bytesWritten,NULL);
	WriteFile(fOut,&nPEvents,sizeof(nPEvents),&bytesWritten,NULL);
	szData = sizeof(UpdateItems);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,UpdateItems,szData,&bytesWritten,NULL);
	szData = sizeof(toggleFlags);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,toggleFlags,szData,&bytesWritten,NULL);
	szData = sizeof(DoToggleFlags);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,DoToggleFlags,szData,&bytesWritten,NULL);
	szData = sizeof(FlagNames);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,FlagNames,szData,&bytesWritten,NULL);
	szData = sizeof(toggleFlagsFreqLevel);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,toggleFlagsFreqLevel,szData,&bytesWritten,NULL);
	szData = sizeof(InputLocScreenList);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,InputLocScreenList,szData,&bytesWritten,NULL);
	szData = sizeof(InputLocSaveList);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,InputLocSaveList,szData,&bytesWritten,NULL);
	szData = sizeof(FreqLevel);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,FreqLevel,szData,&bytesWritten,NULL);
	szData = sizeof(AvailableInputLocations);
	WriteFile(fOut,&szData,dataSize,&bytesWritten,NULL);
	WriteFile(fOut,AvailableInputLocations,szData,&bytesWritten,NULL);

	CloseHandle( fOut );  
}

void DisplayErrorMessage(DWORD ErrorNum){
	if (ErrorNum){
	
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			ErrorNum,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		char messageString[100];
		wsprintf(messageString,"Error %i\n%s",ErrorNum,(LPCTSTR)lpMsgBuf);
		MessageBox( NULL, messageString, "Error", MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
}

void OutputCEError(DWORD error){
	if (error & CE_BREAK)
		OutputDebugString("\nError: The hardware detected a break condition.");
	if (error & CE_DNS)
		OutputDebugString("\nError: A parallel device is not selected.");
	if (error & CE_FRAME)
		OutputDebugString("\nError: The hardware detected a framing error.");
	if (error & CE_IOE)
		OutputDebugString("\nError: An I/O error occurred during communications with the device.");
	if (error & CE_MODE)
		OutputDebugString("\nError: The requested mode is not supported, or the hfile"
		                  "\nparameter is invalid.  If this value is specified, it is"
						  "\nthe only valid error.");	
	if (error & CE_OOP)
		OutputDebugString("\nError: Out of paper.");
	if (error & CE_OVERRUN)
		OutputDebugString("\nError: A character buffer overrun has occured.");
	if (error & CE_PTO)
		OutputDebugString("\nError: A time-out occured on a parallel device.");
	if (error & CE_RXOVER)
		OutputDebugString("\nError: Input buffer overflow.");
	if (error & CE_RXPARITY)
		OutputDebugString("\nError: Parity error.");
	if (error & CE_TXFULL)
		OutputDebugString("\nError: Output buffer full, unable to transmit character.");
}

//template <class T>
//void SortDescending( T array[], int n ){
void SortDescending( int array[], int n ){
	int temp;
	for (int pass = 0; pass < n - 1; pass++){
		for (int i = n - 2; i >= 0; i--){
			if (array[i] < array[i + 1]){
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}

void SortAscending( int array[], int n ){
	int temp;
	for (int pass = 0; pass < n - 1; pass++){
		for (int i = 0; i < n - 1; i++){
			if (array[i] > array[i + 1]){
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}

/*
template <class T>
T Min(const T &a, const T &b){
	if (a < b)
		return a;
	else
		return b;
}
*/

void iToString(int number, int exponent, char *s, bool isNeg /*= false*/){
	static int pos;
		
	if (number < 0){
		number *= -1;
		isNeg = true;
	}
	pos = 0;
	char lastdigit = number % 10 + '0';

	++exponent;
	if (number > 9)
		iToString(number / 10, exponent, s, isNeg);
	
	if (number < 10 && isNeg)
		s[pos++] = '-';
	if (exponent == 0){
		if (pos == 0 || (pos == 1 && isNeg))
			s[pos++] = '0';
		s[pos++] = '.';
	}
	s[pos++] = lastdigit;
	s[pos] = '\0';
}

void WriteToBuf(const BYTE *buf, int bytesToWrite){
	if (readBufPos == -1)
		return;
	else if (readBufPos + bytesToWrite > BUF_SIZE - 1)
		readBufPos = 0;
	
	if (readBufPos + bytesToWrite > BUF_SIZE - 1){
		readBufPos = -1;
		return;
	}

	int j = 0;
	for (int i = readBufPos; i < readBufPos + bytesToWrite; i++)
		readBuf[i] = buf[j++];
	//strncpy(&readBuf[readBufPos], buf, bytesToWrite);
	readBufPos += bytesToWrite;
	readBuf[readBufPos] = '\0';
}

