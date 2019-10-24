//
// ManagerDLL
// Written by Mark Salisbury 8-14-2001
// Purpose:
// Manager dll for board game RISK
//

#include "TypeDecs.h"
//#include <fstream.h>

UINT LastErrorCode;
COUNTRY_DATA * Countries;
PLAYER_INFO * Players;
CARD_DATA * Cards;
AI_CALLS * CompSubs[6] = { 0, 0, 0, 0, 0, 0 };
LAST_MOVE_INFO * ptrLastMove;

int IsDLLInitialized = FALSE;
char * DLLNames[6] = { 0, 0, 0, 0, 0, 0 };
int * currPlayer;
int * TradeInsDone;
int TotalPlayers;
int TradeInValue[] = { 4, 6, 8, 10, 12 }; // TradeInValue[5] = (5-2)*5
int InCall = FALSE;

int DllIDs[6] = { 0, 0, 0, 0, 0, 0 };
int * WinCountArray;
int TotalDLLCount;

char * CountryNames[] = 
{
	"Nothing",
	"Alaska",
	"Northwest Territory",
	"Alberta",
	"Western United States",
	"Ontario",
	"Eastern United States",
	"Quebec",
	"Greenland",
	"Central America",
	"Venezuela",
	"Peru",
	"Brazil",
	"Argentina",
	"North Africa",
	"Egypt",
	"East Africa",
	"Congo",
	"South Africa",
	"Madagascar",
	"Iceland",
	"Scandinavia",
	"Ukraine",
	"Great Britain",
	"Northern Europe",
	"Western Europe",
	"Southern Europe",
	"Middle East",
	"Afghanistan",
	"Ural",
	"Siberia",
	"Yakutsk",
	"Irkutsk",
	"Mongolia",
	"Kamchatka",
	"Japan",
	"China",
	"India",
	"Siam",
	"Indonesia",
	"New Guinea",
	"Western Australia",
	"Eastern Australia"
};

CountryListEnum ContinentCountries[7][12] = 
{
	Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, Nothing, 
	Alaska,	Northwest_Territory, Alberta, Western_United_States, Ontario, Eastern_United_Stated, Quebec, Greenland, Central_America, Nothing, Nothing, Nothing,
	Venezuela, Peru, Brazil, Argentina,  Nothing, Nothing, Nothing,  Nothing, Nothing, Nothing,  Nothing, Nothing,
	North_Africa, Egypt, East_Africa, Congo, South_Africa, Madagascar,  Nothing, Nothing, Nothing,  Nothing, Nothing, Nothing,
	Iceland, Scandinavia, Ukraine, Great_Britain, Northern_Europe, Western_Europe, Southern_Europe,  Nothing, Nothing, Nothing,  Nothing, Nothing,
	Middle_East, Afghanistan, Ural, Siberia, Yakutsk, Irkutsk, Mongolia, Kamchatka, Japan, China, India, Siam, 
	Indonesia, New_Guinea, Western_Australia, Eastern_Australia,  Nothing, Nothing, Nothing,  Nothing, Nothing, Nothing,  Nothing, Nothing,
};

int ContinentCountryCount[7] = {0, 9, 4, 6, 7, 12, 4};
int ContinentArmyValue[7] = {0, 5, 2, 3, 5, 7, 2};

CountryListEnum CountryAdjacencyList[43][6] =
{
	Nothing, Nothing, Nothing, Nothing, Nothing, Nothing,							// nothing territory
	Northwest_Territory, Alberta, Kamchatka, Nothing, Nothing, Nothing,				// Alaska
	Alaska, Alberta, Ontario, Greenland,Nothing, Nothing,							// Northwest_Territory
	Alaska, Northwest_Territory, Ontario, Western_United_States, Nothing, Nothing,	// Alberta 
	Alberta, Ontario, Eastern_United_Stated, Central_America, Nothing, Nothing,		// Western_United_States
	Alberta, Northwest_Territory, Greenland, Quebec, Eastern_United_Stated, Western_United_States,	//Ontario
	Western_United_States, Ontario, Quebec, Central_America,	Nothing, Nothing,		// Eastern_United_States
	Ontario, Greenland, Eastern_United_Stated, Nothing, Nothing, Nothing,			// Quebec
	Northwest_Territory,  Ontario, Quebec, Iceland, Nothing, Nothing,				// Greenland
	Eastern_United_Stated, Western_United_States, Venezuela, Nothing, Nothing, Nothing, // Central America
	Central_America,  Peru, Brazil, Nothing, Nothing, Nothing,						// Venezeula
	Venezuela, Brazil, Argentina, Nothing, Nothing, Nothing,						// Peru
	Venezuela, Peru, Argentina,	North_Africa, Nothing, Nothing,						// Brazil
	Peru, Brazil, Nothing, Nothing, Nothing, Nothing,								// Argentina
	Western_Europe, Southern_Europe, Egypt, East_Africa, Congo,	Brazil,			// North_Africa
	North_Africa, East_Africa, Middle_East, Southern_Europe, Nothing, Nothing,		// Egypt
	Egypt, North_Africa, Congo, South_Africa, Madagascar, Middle_East,				// East_Africa
	North_Africa, East_Africa, South_Africa, Nothing, Nothing, Nothing,				// Congo
	Congo, East_Africa, Madagascar, Nothing, Nothing, Nothing,						// South_Africa
	East_Africa, South_Africa, Nothing, Nothing, Nothing, Nothing,					// Madagascar
	Greenland, Great_Britain, Scandinavia, Nothing, Nothing, Nothing,				// Iceland
	Iceland, Great_Britain, Northern_Europe, Ukraine, Nothing, Nothing,				// Scandinavia
	Scandinavia, Northern_Europe, Southern_Europe, Middle_East, Afghanistan, Ural,	// Ukraine
	Iceland, Scandinavia, Northern_Europe, Western_Europe, Nothing, Nothing,		// Great Britain
	Great_Britain, Scandinavia, Ukraine, Southern_Europe, Western_Europe, Nothing,	// Northern_Europe
	Great_Britain, Northern_Europe, Southern_Europe, North_Africa, Nothing, Nothing,// Western_Eruope
	Western_Europe, Northern_Europe, Ukraine, Middle_East, Egypt, North_Africa,		// Southern_Europe
	Southern_Europe, Ukraine, Afghanistan, India, East_Africa, Egypt,				// Middle_East
	Ukraine, Ural, China, India, Middle_East, Nothing,								// Afghanistan
	Ukraine, Siberia, China, Afghanistan, Nothing, Nothing,							// Ural
	Ural, Yakutsk, Irkutsk, Mongolia, China, Nothing,								// Siberia
	Siberia, Kamchatka, Irkutsk, Nothing, Nothing, Nothing,							// Yaktusk
	Siberia, Yakutsk, Kamchatka, Mongolia, Nothing, Nothing,						// Irkutsk
	Siberia, Irkutsk, Kamchatka, Japan, China, Nothing,								// Mongolia
	Yakutsk, Alaska, Japan, Mongolia, Irkutsk, Nothing,								// Kamchatka
	Kamchatka, Mongolia, Nothing, Nothing, Nothing, Nothing,						// Japan
	Afghanistan, Ural, Siberia, Mongolia, Siam, India,								// China
	Middle_East, Afghanistan, China, Siam, Nothing, Nothing,						// India
	India, China, Indonesia, Nothing, Nothing, Nothing,								// Siam 
	Siam, New_Guinea, Western_Australia, Nothing, Nothing, Nothing,					// Indonesia
	Indonesia, Eastern_Australia, Western_Australia, Nothing, Nothing, Nothing,		// New_Guinea
	Indonesia, New_Guinea, Eastern_Australia, Nothing, Nothing, Nothing,			// Western_Australia
	New_Guinea, Western_Australia, Nothing, Nothing, Nothing, Nothing,				// Eastern_Australia
};

int AdjacentCountryCount[43] = { 0, 3, 4, 4, 4, 6, 4, 3, 4, 3, 3, 3, 4, 2, 6, 4, 6, 3, 3, 2, 3, 4, 6, 4, 5, 4, 6, 6, 5, 4, 5, 3, 4, 5, 5, 2, 6, 4, 3, 3, 3, 3, 2};

// 0 is wild
// 1 is soldier
// 2 is horse
// 3 is cannon
int CardType[43] = {0, 1, 3, 2, 3, 2, 3, 2, 2, 3, 1, 1, 3, 1, 2, 1, 1, 1, 3, 2, 1, 2, 2, 3, 3, 3, 3, 1, 2, 2, 2, 2, 2, 1, 1, 3, 1, 2, 1, 3, 1, 3, 3};

int LoadPlayerDLLs();
int GetCountryContinentID(int wCountry);

/////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS BEGIN HERE
/////////////////////////////////////////////////////////////

extern "C" UINT __stdcall GetLastErrorCode()
{
	return LastErrorCode;
}

extern "C" const char * __stdcall GetLastErrorDescription()
{
	return GetRiskErrorInfo(LastErrorCode);
}

extern "C" const char * __stdcall GetRiskErrorInfo( UINT ErrCode )
{
	switch(ErrCode)
	{
	case ERR_NO_ERROR:					return "No error";
	case ERR_OUT_OF_BOUNDS:				return "Out of bounds error."; 
	case ERR_DONT_OWN_FROM_COUNTRY:		return "Can't attack from a country you don't own.";
	case ERR_DO_OWN_TO_COUNTRY:			return "Can't attack a country you do own.";
	case ERR_COUNTRIES_NOT_ADJACENT:	return "Specified countries are not adjacent.";
	case ERR_CANT_PLACE_ARMIES_THERE:	return "Cannot place armies there.  You do not own specified country.";
	case ERR_FAILED_LOAD_PLAYER_DLL:	return "Failed to load player DLL";
	case ERR_FAILED_LOAD_PLAYER_SUB:	return "Failed to load procedure within player DLL";
	case ERR_CANT_ATTACK_WITH_ZERO_ARMIES: return "Attack is not valid because attacker does not have enough armies to attack.";
	}
	return NULL;
}

extern "C" int __stdcall InitializeDLL(COUNTRY_DATA * CountryArray, 
									   int & currentPlayer, 
									   int nPlayers, 
									   PLAYER_INFO * PlayerInfoArray, 
									   CARD_DATA * CardArray, 
									   int &TradeIns, 
									   LAST_MOVE_INFO & LastMove,
									   int useWinCountPtr,
									   int *ptrWinCountArray,
									   int TotalDLLs)
{
	// before this sub is called the players should all
	// be in their correct order, with the playerinfo array
	// all filled.
	if (!IsDLLInitialized)
	{
		Countries = CountryArray;
		Players = PlayerInfoArray;
		TotalPlayers = nPlayers;
		currPlayer = &currentPlayer;
		IsDLLInitialized = TRUE;
		Cards = CardArray;
		TradeInsDone = &TradeIns;
		ptrLastMove = &LastMove;

		if (useWinCountPtr && ptrWinCountArray)
		{
			WinCountArray = ptrWinCountArray;
			TotalDLLCount = TotalDLLs;
		}
		else
		{
			WinCountArray = NULL;
		}

		return LoadPlayerDLLs();
	}			
	return FALSE;
}

extern "C" int __stdcall SetDLLName(int wPlayer, char * DLLName)
{
	if (!IsDLLInitialized)
	{
		if (DLLNames[wPlayer] == NULL)
		{
			DLLNames[wPlayer] = new char[255];
		}
		strcpy(DLLNames[wPlayer],DLLName);
		return TRUE;
	}
	return FALSE;
}

extern "C" int __stdcall SetDLLID(int wPlayer, int DLLID)
{
	if (!IsDLLInitialized)
	{
		DllIDs[wPlayer] = DLLID;
		return TRUE;
	}
	return FALSE;
}

extern "C" const char * __stdcall GetDLLName(int wPlayer)
{
	return DLLNames[wPlayer];
}

extern "C" int __stdcall TestPlayerDLL(char * DLLName, char * PlayerName)
{
	// returns TRUE if DLL was loaded successfully, FALSE
	// if it failed.
	if (!IsDLLInitialized)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;

		hFind = FindFirstFile(DLLName, &FindFileData);

		if (hFind == INVALID_HANDLE_VALUE) 
		{
			//printf ("Invalid File Handle. Get Last Error reports %d\n", GetLastError ());
			FindClose(hFind);
			return FALSE;
		} 
		FindClose(hFind);
  
		HMODULE hModule;
		hModule = LoadLibrary(DLLName);
		BOOL failed = FALSE;

		if (hModule == NULL)
		{
			LastErrorCode = ERR_FAILED_LOAD_PLAYER_DLL;
			return FALSE;
		}

		AI_CALLS * Subs = new AI_CALLS;
		Subs->DoReinforcement = (DO_REINFORCEMENT) GetProcAddress(hModule,"DoReinforcement");
		Subs->CaptureCountry = (CAPTURE_COUNTRY) GetProcAddress(hModule,"CaptureCountry");
		Subs->MakeMove = (MAKE_MOVE) GetProcAddress(hModule,"MakeMove");
		Subs->DoTradeIn = (DO_TRADE_IN) GetProcAddress(hModule,"DoTradeIn");
		Subs->TurnStartPlaceArmies = (TURN_START_PLACE) GetProcAddress(hModule,"TurnStartPlaceArmies");
		Subs->InitialPlaceArmies = (INITIAL_PLACE) GetProcAddress(hModule,"InitialPlaceArmies");
		Subs->Initialize = (INITIALIZE) GetProcAddress(hModule,"Initialize");
		Subs->DefendCountry = (DEFEND_COUNTRY) GetProcAddress(hModule,"DefendCountry");
		Subs->GetPlayerName = (GET_PLAYER_NAME) GetProcAddress(hModule,"GetPlayerName");
		
		if (Subs->GetPlayerName)
		{
			char * ptrname = (Subs->GetPlayerName)();
			if (ptrname == NULL)
				strcpy(PlayerName,"Computer");
			else
				strcpy(PlayerName,ptrname);
		}

		if (Subs->DoReinforcement == NULL ||
			Subs->CaptureCountry == NULL ||
			Subs->MakeMove == NULL ||
			Subs->DoTradeIn == NULL ||
			Subs->TurnStartPlaceArmies == NULL ||
			Subs->InitialPlaceArmies == NULL ||
			Subs->Initialize == NULL ||
			Subs->DefendCountry == NULL||
			Subs->GetPlayerName == NULL)
		{
			LastErrorCode = ERR_FAILED_LOAD_PLAYER_SUB;
			failed = TRUE;
		}
		
		FreeLibrary(hModule);
		delete Subs;

		return !failed;
	}
	return FALSE;
}

int LoadPlayerDLLs()
{
	// this sub should not return false... the player should
	// call testDLL to make sure that the functions can be 
	// load OK first...
	BOOL failed = FALSE;

	for (int wPlayer = 0; wPlayer < TotalPlayers; wPlayer++)
	{
		if (Players[wPlayer].IsPlayerHuman == FALSE)
		{
			CompSubs[wPlayer] = new AI_CALLS;
			CompSubs[wPlayer]->hModule = LoadLibrary(DLLNames[wPlayer]);
			if (CompSubs[wPlayer]->hModule == NULL)
			{
				LastErrorCode = ERR_FAILED_LOAD_PLAYER_DLL;
				return FALSE;
			}
			
			CompSubs[wPlayer]->DoReinforcement = (DO_REINFORCEMENT) GetProcAddress(CompSubs[wPlayer]->hModule,"DoReinforcement");
			CompSubs[wPlayer]->CaptureCountry = (CAPTURE_COUNTRY) GetProcAddress(CompSubs[wPlayer]->hModule,"CaptureCountry");
			CompSubs[wPlayer]->MakeMove = (MAKE_MOVE) GetProcAddress(CompSubs[wPlayer]->hModule,"MakeMove");
			CompSubs[wPlayer]->DefendCountry = (DEFEND_COUNTRY) GetProcAddress(CompSubs[wPlayer]->hModule,"DefendCountry");
			CompSubs[wPlayer]->DoTradeIn = (DO_TRADE_IN) GetProcAddress(CompSubs[wPlayer]->hModule,"DoTradeIn");
			CompSubs[wPlayer]->TurnStartPlaceArmies = (TURN_START_PLACE) GetProcAddress(CompSubs[wPlayer]->hModule,"TurnStartPlaceArmies");
			CompSubs[wPlayer]->InitialPlaceArmies = (INITIAL_PLACE) GetProcAddress(CompSubs[wPlayer]->hModule,"InitialPlaceArmies");
			CompSubs[wPlayer]->Initialize = (INITIALIZE) GetProcAddress(CompSubs[wPlayer]->hModule,"Initialize");
			CompSubs[wPlayer]->GetPlayerName = (GET_PLAYER_NAME) GetProcAddress(CompSubs[wPlayer]->hModule,"GetPlayerName");
			CompSubs[wPlayer]->TurnComplete = (TURN_COMPLETE) GetProcAddress(CompSubs[wPlayer]->hModule,"TurnComplete");
			if (CompSubs[wPlayer]->DoReinforcement == NULL ||
				CompSubs[wPlayer]->CaptureCountry == NULL ||
				CompSubs[wPlayer]->MakeMove == NULL ||
				CompSubs[wPlayer]->DoTradeIn == NULL ||
				CompSubs[wPlayer]->TurnStartPlaceArmies == NULL ||
				CompSubs[wPlayer]->InitialPlaceArmies == NULL ||
				CompSubs[wPlayer]->Initialize == NULL)
			{
				LastErrorCode = ERR_FAILED_LOAD_PLAYER_SUB;
				return FALSE;
			}
			else
			{
				(CompSubs[wPlayer])->Initialize(wPlayer,TotalPlayers);
			}
		}
	}

	return TRUE;
}

extern "C" LAST_MOVE_INFO __stdcall GetLastMove()
{
	return *ptrLastMove;
}

extern "C" int __stdcall AreCountriesAdjacent(int CountryA, int CountryB)
{
	if (CountryA < 1 || CountryA > 42 || CountryB < 1 || CountryB > 42)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}

	for (int i = 0; i < 6; i++)
	{
		if (CountryAdjacencyList[CountryA][i] == CountryB)
			return TRUE;
	}
	return FALSE;
}

extern "C" int __stdcall GetAttackError(int FromCountry, int ToCountry)
{
	if (FromCountry < 1 || FromCountry > 42)
		return ERR_OUT_OF_BOUNDS;
	if (ToCountry < 1 || ToCountry > 42)
		return ERR_OUT_OF_BOUNDS;
	if (Countries[FromCountry].OwnerID != *currPlayer)
		return ERR_DONT_OWN_FROM_COUNTRY;
	if (Countries[ToCountry].OwnerID == *currPlayer)
		return ERR_DO_OWN_TO_COUNTRY;
	if (!AreCountriesAdjacent(FromCountry,ToCountry))
		return ERR_COUNTRIES_NOT_ADJACENT;
	if (Countries[FromCountry].ArmyCount < 2)
		return ERR_CANT_ATTACK_WITH_ZERO_ARMIES;
	return 0;
}

extern "C" int __stdcall GetCountryInfo(int wCountry, COUNTRY_INFO &CountryInfoStruct )
{
	if (wCountry < 1 || wCountry > 42)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}

	CountryInfoStruct.OwnerID = Countries[wCountry].OwnerID;
	CountryInfoStruct.ArmyCount = Countries[wCountry].ArmyCount;
	CountryInfoStruct.AdjacentCountries = AdjacentCountryCount[wCountry];
	CountryInfoStruct.EnemyOwnedAdjacentCountries = 0;
	CountryInfoStruct.ContinentID = GetCountryContinentID(wCountry);
	for (int i = 0; i < CountryInfoStruct.AdjacentCountries; i++)
	{
		if ( Countries[CountryAdjacencyList[wCountry][i]].OwnerID != *currPlayer)
			CountryInfoStruct.EnemyOwnedAdjacentCountries++;
	}

	return TRUE;
}

//extern "C" int __stdcall GetCountryContinentID(int wCountry, int &ContinentID)
int GetCountryContinentID(int wCountry)
{
	if (wCountry < 10)
		return 1;
	else if (wCountry < 14)
		return 2;
	else if (wCountry < 20)
		return 3;
	else if (wCountry < 27)
		return 4;
	else if (wCountry < 39)
		return 5;
	else 
		return 6;
}

extern "C" int __stdcall GetCountryName(int wCountry, char * name)
{
	if (wCountry < 1 || wCountry > 42)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	//memcpy(name,CountryNames[wCountry],strlen(CountryNames[wCountry]));
	strcpy(name,CountryNames[wCountry]);

	return TRUE;
}

extern "C" int __stdcall GetAdjacentCountryCount(int wCountry, int &AdjacentCount)
{
	if (wCountry < 1 || wCountry > 42)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	AdjacentCount = AdjacentCountryCount[wCountry];
	return TRUE;
}

extern "C" int __stdcall GetAdjacentCountryID(int wCountry, int wIndex, int &AdjacentID)
{
	if (wCountry < 1 || wCountry > 42 || wIndex < 0 || wIndex >= AdjacentCountryCount[wCountry])
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	
	AdjacentID = CountryAdjacencyList[wCountry][wIndex];
	return TRUE;
}

extern "C" int __stdcall GetContinentOwner(int wContinent, int &Owner)
{
	if (wContinent < 1 || wContinent > 6)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}

	int FirstOwner;
	FirstOwner = Countries[ContinentCountries[wContinent][0]].OwnerID;

	for (int wC = 1; wC < ContinentCountryCount[wContinent]; wC++)
	{
		if (Countries[ContinentCountries[wContinent][wC]].OwnerID != FirstOwner)
		{
			Owner = -1;
			return TRUE;
		}
	}
	Owner = FirstOwner;
	return TRUE;
}

extern "C" int __stdcall GetContinentCountryCount(int wContinent, int &Count)
{
	if (wContinent < 1 || wContinent > 6)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	Count = ContinentCountryCount[wContinent];
	return TRUE;
}

extern "C" int __stdcall GetContinentCount()
{
	return 6;
}

extern "C" int __stdcall GetContinentCountryID(int ContinentCountryIndex, int wContinent, int & wCountry)
{
	if (wContinent < 1 || wContinent > 6)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	if (ContinentCountryIndex < 0 || ContinentCountryIndex >= ContinentCountryCount[wContinent])
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}

	wCountry = ContinentCountries[wContinent][ContinentCountryIndex];
	return TRUE;
}

extern "C" int __stdcall GetContinentValue(int wContinent, int &ArmyValue)
{
	if (wContinent < 1 || wContinent > 6)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	
	ArmyValue = ContinentArmyValue[wContinent];
	return TRUE;
}

extern "C" int __stdcall GetPlayerInfo(int wPlayer, PLAYER_INFO &Player)
{
	if (wPlayer < 0 || wPlayer >= TotalPlayers)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;
	}
	memcpy(&Player,&Players[wPlayer],sizeof(PLAYER_INFO));
	
	return TRUE;
}

extern "C" int __stdcall GetNextTradeInValue()
{
	if (*TradeInsDone < 5)
		return TradeInValue[*TradeInsDone];
	else
		return (*TradeInsDone - 2) * 5;
}

extern "C" int __stdcall LookAtCards(CARD_DATA &MyCards)
{
	memcpy(&MyCards,&Cards[*currPlayer],sizeof(CARD_DATA));
	return TRUE;
}

extern "C" int __stdcall GetCardType(int wCard,int &rCardType)
{
	if (wCard >= 0 && wCard <= 42)
	{
		rCardType = CardType[wCard];
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

extern "C" int __stdcall CalculateArmiesToPlace(int wPlayer, int &ArmyCount)
{
	if (wPlayer < 0 || wPlayer >= TotalPlayers)
	{
		LastErrorCode = ERR_OUT_OF_BOUNDS;
		return FALSE;	
	}
	
	int Owner, ArmyValue;
	ArmyCount = 0;

	for (int wContinent = 1; wContinent < 7; wContinent++)
	{
		GetContinentOwner(wContinent,Owner);
		if (Owner == wPlayer)
		{
			GetContinentValue(wContinent,ArmyValue);
			ArmyCount += ArmyValue;
		}
	}

	int CountryArmies;
	CountryArmies = Players[wPlayer].CountryCount / 3;
	if (CountryArmies < 3) 
		CountryArmies = 3;
	ArmyCount += CountryArmies;

	return TRUE;
}

extern "C" BASIC_BOOL __stdcall CallGetPlayerName(char * name)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;	
		if (currPlayer && CompSubs[*currPlayer] && CompSubs[*currPlayer]->GetPlayerName)
		{
			char * ptrname = (CompSubs[*currPlayer]->GetPlayerName)();

			if (ptrname == NULL)
			{
				strcpy(name,"Computer");
			}
			else
				strcpy(name,ptrname);
		}
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" BASIC_BOOL __stdcall CallPlaceArmiesAtStart(int ArmiesToPlace, int &wCountry, int &nArmies)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		(CompSubs[*currPlayer]->InitialPlaceArmies)(ArmiesToPlace,wCountry,nArmies);
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;

}

extern "C" BASIC_BOOL __stdcall CallPlaceArmies(int ArmiesToPlace, int &wCountry, int &nArmies)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		(CompSubs[*currPlayer]->TurnStartPlaceArmies)(ArmiesToPlace,wCountry,nArmies);
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" BASIC_BOOL __stdcall CallMakeMove (int &AttackWhere, int &FromWhere, int &nArmiesToUse, int &result)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		result = (CompSubs[*currPlayer]->MakeMove)(AttackWhere,FromWhere,nArmiesToUse);
		if (result && FromWhere > 0 && FromWhere < 43)
		{
			if (nArmiesToUse < 1)
				nArmiesToUse = 1;
			else if (nArmiesToUse > 3)
				nArmiesToUse = 3;
		}
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" BASIC_BOOL __stdcall CallDefendCountry(int DefenderID, int OpposingArmies, int myArmies, int CountryID, int &DiceToRoll)
{
	if (CompSubs[DefenderID]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		(CompSubs[DefenderID]->DefendCountry)(OpposingArmies,myArmies,CountryID,DiceToRoll);
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" BASIC_BOOL __stdcall CallCaptureCountry(int FromWhere, int ToWhere, int minArmies, int maxArmies, int &nArmiesToMove)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		(CompSubs[*currPlayer]->CaptureCountry)(FromWhere,ToWhere,minArmies,maxArmies,nArmiesToMove);
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" BASIC_BOOL __stdcall CallDoReinforcement(int &FromWhere, int &ToWhere, int &nArmies, int &result)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		result = (CompSubs[*currPlayer]->DoReinforcement)(FromWhere,ToWhere,nArmies);
		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" BASIC_BOOL __stdcall CallDoTradeIn(int CardCount, int wCards[3], BOOL IsMandatory, int &result)
{
	if (CompSubs[*currPlayer]==NULL)
	{
		return BASIC_FALSE;
	}
	else if (!InCall)
	{
		InCall = TRUE;
		CARD_DATA MyCards;
		LookAtCards(MyCards);
		//ofstream fout("tradein.txt");
		//fout << "Pre-trade in info: CardCount = "<< CardCount << ", IsMandatory = " << IsMandatory << endl;
		//for (int i = 0; i < CardCount; i++)
		//{
		//	fout << "MyCards.wCountry["<<i<<"] = " << MyCards.wCountry[i] << endl;
		//	fout << "MyCards.cardType["<<i<<"] = " << MyCards.cardType[i] << endl;
		//}
		//	
		result = (CompSubs[*currPlayer]->DoTradeIn)(CardCount, MyCards, wCards, IsMandatory);
		//fout << "result = " << result << endl;
		//if (result)
		//{
		//	fout << "Cards picked: " << wCards[0] << ", " << wCards[1] << ", " << wCards[2] << endl;
		//}
		//fout.close();

		InCall = FALSE;
		return BASIC_TRUE;
	}
	return BASIC_FALSE;
}

extern "C" void __stdcall CallTurnComplete()
{
	for (int p = 0; p < TotalPlayers; p++)
	{
		if (Players[p].IsPlayerAlive && p != *currPlayer && Players[p].IsPlayerHuman == FALSE)
		{
			if (CompSubs[p]!=NULL && CompSubs[p]->TurnComplete != NULL)
			{
				int playerID = *currPlayer;
				(CompSubs[p]->TurnComplete)(playerID);	
			}		
		}
	}
}

extern "C" void __stdcall ReleaseDLLs()
{
	if (!InCall)
	{
		InCall = TRUE;
		for (int i = 0; i < TotalPlayers; i++)
		{
			if (Players[i].IsPlayerHuman == FALSE && CompSubs[i])
			{
				RELEASE_MEMORY Release;
				Release = (RELEASE_MEMORY) GetProcAddress(CompSubs[i]->hModule,"ReleaseMemory");
				if (Release)
					Release();

				FreeLibrary(CompSubs[i]->hModule);
				CompSubs[i]->CaptureCountry = 0;
				CompSubs[i]->DefendCountry = 0;
				CompSubs[i]->DoReinforcement = 0;
				CompSubs[i]->DoTradeIn = 0;
				CompSubs[i]->GetPlayerName = 0;
				CompSubs[i]->hModule = 0;
				CompSubs[i]->Initialize = 0;
				CompSubs[i]->InitialPlaceArmies = 0;
				CompSubs[i]->MakeMove = 0;
				CompSubs[i]->TurnStartPlaceArmies = 0;
				delete CompSubs[i];
				CompSubs[i] = 0;
				delete [] DLLNames[i];
				DLLNames[i] = 0;
			}
		}
		InCall = FALSE;
	}
}

extern "C" int __stdcall GetPlayerWinCount(int PlayerID)
{
	if (PlayerID >= 0 && PlayerID < 6 &&
		DllIDs[PlayerID] >= 0 && DllIDs[PlayerID] < TotalDLLCount && WinCountArray)
	{
		return WinCountArray[DllIDs[PlayerID]];
	}
	else
		return -1;
}

extern "C" int __stdcall GetDLLWinCount(int DLLID)
{
	if (DLLID >= 0 && DLLID < TotalDLLCount && WinCountArray)
	{
		return WinCountArray[DLLID];
	}
	else
		return -1;
}

extern "C" int __stdcall GetDLLID(int PlayerID)
{
	if (PlayerID >= 0 && PlayerID < 6 && WinCountArray)
	{
		return DllIDs[PlayerID];
	}
	else
		return -1;
}

extern "C" int __stdcall GetTotalDLLCount()
{
	return TotalDLLCount;
}