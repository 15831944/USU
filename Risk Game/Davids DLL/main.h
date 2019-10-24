#include <windows.h>

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
	int wCountry[8];
	int cardType[8]; // 0 = wild, 1 = soldier, 2 = horse, 3 = cannon
};

// Exported functions' prototype list:

extern "C" unsigned int __stdcall GetLastErrorCode();
extern "C" const char * __stdcall GetRiskErrorInfo( unsigned int ErrCode );
extern "C" const char * __stdcall GetLastErrorDescription();
extern "C" int  __stdcall AreCountriesAdjacent(int CountryA, int CountryB);
extern "C" int  __stdcall InitializeDLL(COUNTRY_DATA * CountryArray, int & currentPlayer, int TotalPlayers, PLAYER_INFO * PlayerInfoArray, CARD_DATA * CardArray, int &TradeIns, LAST_MOVE_INFO & LastMove );
extern "C" int  __stdcall TestPlayerDLL(char * DLLName);
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
extern "C" int  __stdcall PlaceArmies(int wCountry, int nArmies);
extern "C" int  __stdcall LookAtCards(CARD_DATA &MyCards);
extern "C" int  __stdcall CalculateArmiesToPlace(int wPlayer, int &ArmyCount);
extern "C" void __stdcall CallPlaceArmiesAtStart(int ArmiesToPlace, int &wCountry, int &nArmies);
extern "C" void __stdcall CallPlaceArmies(int ArmiesToPlace, int &wCountry, int &nArmies);
extern "C" BOOL __stdcall CallMakeMove (int &AttackWhere, int &FromWhere, int &nArmiesToUse);
extern "C" int  __stdcall GetCardType(int wCard,int &CardType);
extern "C" LAST_MOVE_INFO __stdcall GetLastMove();


