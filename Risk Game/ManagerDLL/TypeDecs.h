#include <windows.h>

#define ERR_NO_ERROR						0
#define ERR_OUT_OF_BOUNDS					1
#define ERR_DONT_OWN_FROM_COUNTRY			2
#define ERR_DO_OWN_TO_COUNTRY				3
#define ERR_COUNTRIES_NOT_ADJACENT			4
#define ERR_CANT_PLACE_ARMIES_THERE			5
#define ERR_FAILED_LOAD_PLAYER_DLL			6
#define ERR_FAILED_LOAD_PLAYER_SUB			7
#define ERR_CANT_ATTACK_WITH_ZERO_ARMIES	8

typedef short BASIC_BOOL ;
#define BASIC_TRUE -1
#define BASIC_FALSE 0

enum LastMoveEnum 
{ 
	NoMove = 0,
    MadeAttack = 1,
    Retreat = 2,
    CapturedCountry = 3,
    Defeat = 4
};

struct LAST_MOVE_INFO
{
	LastMoveEnum LastAction;  // the results of the last move made 
	int FromID; // id of the country from which at attack or retreat was made
	int ToID; // id of the country which was attacked or to which a retreat was made
};

struct COUNTRY_INFO
{
	int OwnerID;  // the player id of the player who owns this country
	int ArmyCount;  // the number of armies the owner has in this country
	int AdjacentCountries;  // the number of armies adjacent to this country
	int EnemyOwnedAdjacentCountries;  // the number of adjacent enemy owned countries
	int ContinentID;
};

struct COUNTRY_DATA 
{
	int OwnerID;  // the player id of the player who owns this country
	int ArmyCount;  // the number of armies the owner has in this country
};

struct PLAYER_INFO
{
	int IsPlayerHuman;
	int ArmyCount;
	int ArmiesToPlace;
	int CountryCount;
	int IsPlayerAlive;
	int CardCount;
};

struct CARD_DATA
{
	int wCountry[10];
	int cardType[10]; // 0 = wild, 1 = soldier, 2 = horse, 3 = cannon
};

//typedefs for AI function calls

typedef BOOL (__stdcall *DO_REINFORCEMENT)(int &FromWhere, int &ToWhere, int &nArmiesToMove);
typedef void (__stdcall *CAPTURE_COUNTRY)(int FromWhere, int ToWhere, int minArmies, int maxArmies, int &nArmiesToMove);
typedef BOOL (__stdcall *MAKE_MOVE)( int &AttackWhere, int &FromWhere, int &nArmiesToUse);
typedef BOOL (__stdcall *DO_TRADE_IN)(int CardCount, CARD_DATA MyCards, int wCards[3], BOOL IsMandatory);
typedef void (__stdcall *TURN_START_PLACE)(int ArmiesToPlace, int &wCountry, int &nArmies);
typedef void (__stdcall *INITIAL_PLACE)(int ArmiesToPlace, int &wCountry, int &nArmies);
typedef void (__stdcall *INITIALIZE)(int ID, int nplayers);
typedef void (__stdcall *DEFEND_COUNTRY)(int OpposingArmies, int myArmies, int CountryID, int &DiceToRoll);
typedef char * (__stdcall *GET_PLAYER_NAME)();
typedef void (__stdcall *RELEASE_MEMORY)();
typedef void (__stdcall *TURN_COMPLETE)(int PlayerID);

struct AI_CALLS
{
	DO_REINFORCEMENT DoReinforcement;
	CAPTURE_COUNTRY CaptureCountry;
	MAKE_MOVE MakeMove;
	DEFEND_COUNTRY DefendCountry;
	DO_TRADE_IN DoTradeIn;
	TURN_START_PLACE TurnStartPlaceArmies;
	INITIAL_PLACE InitialPlaceArmies;
	INITIALIZE Initialize;
	GET_PLAYER_NAME GetPlayerName;
	TURN_COMPLETE TurnComplete;
	HMODULE hModule;
};

enum CountryListEnum 
{ 
	Nothing = 0,
	Alaska = 1,
	Northwest_Territory = 2,
	Alberta = 3,
	Western_United_States = 4,
	Ontario = 5,
	Eastern_United_Stated = 6,
	Quebec = 7,
	Greenland = 8,
	Central_America = 9,
	Venezuela = 10,
	Peru = 11,
	Brazil = 12,
	Argentina = 13,
	North_Africa = 14,
	Egypt = 15,
	East_Africa = 16,
	Congo = 17,
	South_Africa = 18,
	Madagascar = 19,
	Iceland = 20,
	Scandinavia = 21,
	Ukraine = 22,
	Great_Britain = 23,
	Northern_Europe = 24,
	Western_Europe = 25,
	Southern_Europe = 26,
	Middle_East = 27,
	Afghanistan = 28,
	Ural = 29,
	Siberia = 30,
	Yakutsk = 31,
	Irkutsk = 32,
	Mongolia = 33,
	Kamchatka = 34,
	Japan = 35,
	China = 36,
	India = 37,
	Siam = 38,
	Indonesia = 39,
	New_Guinea = 40,
	Western_Australia = 41,
	Eastern_Australia = 42 
};

enum ContinentListEnum
{
	North_America = 1,
	South_America = 2,
	Europe = 3,
	Africa = 4,
	Asia = 5,
	Australia = 6
};

// this code can check to see if there are any errors in my adjacency list
//for (int i = 1; i < 43; i++)
//{
//	int aCount = 0;
//	for(int w = 0; CountryAdjacencyList[i][w] != Nothing && w < 6; w++)
//	{
//		aCount++;
//		if (AreCountriesAdjacent(i, CountryAdjacencyList[i][w]) && !AreCountriesAdjacent(CountryAdjacencyList[i][w], i))
//		{
//			int x = 0; // error
//		}
//	}
//	if ( aCount != AdjacentCountryCount[i] )
//		int x = 0; // error
//}

/////////////////////////////////////////////////////////////
// Exported functions' prototype list:
/////////////////////////////////////////////////////////////

extern "C" unsigned int __stdcall GetLastErrorCode();
extern "C" const char * __stdcall GetRiskErrorInfo( unsigned int ErrCode );
extern "C" const char * __stdcall GetLastErrorDescription();
extern "C" int  __stdcall AreCountriesAdjacent(int CountryA, int CountryB);
extern "C" int  __stdcall InitializeDLL(COUNTRY_DATA * CountryArray, int & currentPlayer, int TotalPlayers, PLAYER_INFO * PlayerInfoArray, CARD_DATA * CardArray, int &TradeIns, LAST_MOVE_INFO & LastMove, int useWinCountPtr, int *ptrWinCountArray, int TotalDLLs);
extern "C" int  __stdcall TestPlayerDLL(char * DLLName, char * PlayerName);
extern "C" int  __stdcall SetDLLName(int wPlayer, char * DLLName);
extern "C" int  __stdcall GetAttackError(int FromCountry, int ToCountry);
extern "C" int  __stdcall GetCountryInfo(int wCountry, COUNTRY_INFO &InfoStruct);
extern "C" int  __stdcall GetCountryName(int wCountry, char *name);
extern "C" int  __stdcall GetAdjacentCountryCount(int wCountry, int &AdjacentCount);
extern "C" int  __stdcall GetAdjacentCountryID(int wCountry, int wIndex, int &AdjacentID);
extern "C" int  __stdcall GetContinentOwner(int wContinent, int &Owner);
extern "C" int  __stdcall GetContinentCountryCount(int wContinent, int &Count);
extern "C" int  __stdcall GetContinentCount();
extern "C" int  __stdcall GetContinentCountryID(int ContinentCountryIndex, int wContinent, int & wCountry);
extern "C" int  __stdcall GetContinentValue(int wContinent, int &ArmyValue);
extern "C" int  __stdcall GetPlayerInfo(int wPlayer, PLAYER_INFO &Player);
extern "C" int  __stdcall GetNextTradeInValue();
extern "C" int  __stdcall GetCardType(int wCard,int &rCardType);
extern "C" LAST_MOVE_INFO __stdcall GetLastMove();
extern "C" const char * __stdcall GetDLLName(int wPlayer);
extern "C" int  __stdcall LookAtCards(CARD_DATA &MyCards);
extern "C" int  __stdcall CalculateArmiesToPlace(int wPlayer, int &ArmyCount);
extern "C" void __stdcall ReleaseDLLs();
//extern "C" int __stdcall GetCountryContinentID(int wCountry, int &ContinentID);
extern "C" int __stdcall GetTotalDLLCount();
extern "C" int __stdcall GetDLLID(int PlayerID);
extern "C" int __stdcall GetDLLWinCount(int DLLID);
extern "C" int __stdcall GetPlayerWinCount(int PlayerID);

extern "C" int __stdcall SetDLLID(int wPlayer, int DLLID);
extern "C" BASIC_BOOL __stdcall CallPlaceArmiesAtStart(int ArmiesToPlace, int &wCountry, int &nArmies);
extern "C" BASIC_BOOL __stdcall CallPlaceArmies(int ArmiesToPlace, int &wCountry, int &nArmies);
extern "C" BASIC_BOOL __stdcall CallCaptureCountry(int FromWhere, int ToWhere, int minArmies, int maxArmies, int &nArmiesToMove);
extern "C" BASIC_BOOL __stdcall CallDefendCountry(int DefenderID, int OpposingArmies, int myArmies, int CountryID, int &DiceToRoll);
extern "C" BASIC_BOOL __stdcall CallGetPlayerName(char * name);
extern "C" void __stdcall CallTurnComplete();
extern "C" BASIC_BOOL __stdcall CallDoTradeIn(int CardCount, int wCards[3], BOOL IsMandatory, int &result);
extern "C" BASIC_BOOL __stdcall CallDoReinforcement(int &FromWhere, int &ToWhere, int &nArmies, int &result);
extern "C" BASIC_BOOL __stdcall CallMakeMove (int &AttackWhere, int &FromWhere, int &nArmiesToUse, int &result);
