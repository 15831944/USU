#include "Main.h"
#include <windows.h>

int myID;
int nPlayers;

int OwnerOfCountry(int ID)
{
	COUNTRY_INFO Country;
	GetCountryInfo(ID, Country);
	return Country.OwnerID;
}

int TotEnemyArmiesOnAdjCountries(int CountID)
{	// Returns the total number of enemy armies on adjacent
	// countries
	int EnemyNeighborArmies = 0, AdjacentCountries;
	GetAdjacentCountryCount(CountID, AdjacentCountries);
	int AdjID;
	COUNTRY_INFO info;
	for (int i = 0; i < AdjacentCountries; i++)
	{
		GetAdjacentCountryID(CountID, i, AdjID);
		GetCountryInfo(AdjID, info);
		if (OwnerOfCountry(AdjID) != myID)
		{
			EnemyNeighborArmies += info.ArmyCount;
		}
	}
	return EnemyNeighborArmies;
}


extern "C" void __stdcall Initialize(int ID, int nplayers)
{
	myID = ID;
	nPlayers = nplayers;

	// one way to do this is to put the .lib file
	// in the same directory as the .dsw file and then
	// add the .lib file to the project settings...
	// then all we need to include is a header that gives
	// the function prototypes.
}

extern "C" void __stdcall ReleaseMemory()
{
	// this will be called immediately before the memory for this DLL is freed.
	// please delete any dynamically allocated memory now
}

extern "C" void __stdcall InitialPlaceArmies(int ArmiesToPlace, int &wCountry, int &nArmies)
{
	// called at the start of the game
	// if not all armies are placed then this will be called again...
	int wC;
	COUNTRY_INFO countryStruct;
	for (wC = 1; wC < 43; wC++)
	{
		GetCountryInfo(wC,countryStruct);
		if (countryStruct.OwnerID == myID)
		{
			wCountry = wC;
			nArmies = ArmiesToPlace;
			return;
		}
	}
}

extern "C" void __stdcall TurnStartPlaceArmies(int ArmiesToPlace, int &wCountry, int &nArmies)
{
	// called at the start of each turn...
	// if not all armies are placed then this function will be called again.

	int wC;
	COUNTRY_INFO countryStruct;
	for (wC = 1; wC < 43; wC++)
	{
		GetCountryInfo(wC,countryStruct);
		if (countryStruct.OwnerID == myID)
		{
			wCountry = wC;
			nArmies = ArmiesToPlace;
			return;
		}
	}
}

extern "C" BOOL __stdcall DoTradeIn(int CardCount, CARD_DATA MyCards, int wCards[3], BOOL IsMandatory)
{
	// This is called by the manager when you have 3 or more cards
	// If you wish to do a trade in, return TRUE,
	// otherwise return FALSE...
	// If the trade in is mandatory (because you 
	// have five or more cards), you must return TRUE 
	// (unless you wish to forfeit 3 cards automatically)
	// Place the index of each card in the wCard array...
	// If you want to get to 2 bonus armies because you own
	// one of the countries shown by your cards, then place
	// that card as the first card (in wCards[0]).
	
	// The rule on trade-ins is that you need three of a kind or three different
	// The card type is given by the cardType member of MyCards

	// count the cards of each type... a wild counts as each type
	int cardType[4] = {0,0,0,0};
	int wC = 0;
	for (int i = 0; i < CardCount; i++)
	{
		if (MyCards.cardType[i] > 0)
			cardType[MyCards.cardType[i]]++;
		else
		{
			cardType[1]++;
			cardType[2]++;
			cardType[3]++;
		}
	}

	for (int wType = 1; wType <= 3; wType++)
	{
		if (cardType[wType] > 2) // I can make a trade in of "wType" type
		{
			for (int i = 0; i < CardCount && wC < 3; i++)
			{
				if (MyCards.cardType[i] == wType || MyCards.cardType[i] == 0)
					wCards[wC++] = i;	
			}
			return TRUE;
		}
	}

	if (cardType[1] > 0 && cardType[2] > 0 && cardType[3] > 0) 
		// I can make a trade in of three different types
	{
		cardType[1] = 0;
		cardType[2] = 0;
		cardType[3] = 0;
		for (int i = 0; i < CardCount && wC < 3; i++)
		{
			if (cardType[MyCards.cardType[i]] == 0 || MyCards.cardType[i] == 0)
			{
				cardType[MyCards.cardType[i]]++;
				wCards[wC++] = i;
			}
		}
		return TRUE;
	}

	return FALSE;	
}

extern "C" BOOL __stdcall MakeMove (int &AttackWhere, int &FromWhere, int &nArmiesToUse)
{
	// if your turn is over and you do not wish to make a move, 
	// then return FALSE.  otherwise return TRUE and the country
	// you wish to attack, as well as the country you are attacking
	// from and the number of dice you wish to roll.  
	// Pay attention to the lastMove struct.  This will return information
	// about the results of the last attack you made.
	// If your last move was to attack a country, you will
	// probably wish to continue attacking that same country, 
	// unless you are doing poorly attacking that country.
	AttackWhere = 0;
	FromWhere = 0;

	COUNTRY_INFO a, b;
	LAST_MOVE_INFO LastMove = GetLastMove();

	if (LastMove.LastAction == MadeAttack)
	{
		// continue attack if possible
		GetCountryInfo(LastMove.FromID,a);
		GetCountryInfo(LastMove.ToID,b);
		if (a.ArmyCount > b.ArmyCount)
		{
			// since we outnumber them, continue the attack...
			AttackWhere = LastMove.ToID;
			FromWhere = LastMove.FromID;
		}
	}

	if (AttackWhere == 0)
	{
		// let's look for some place to attack
		for (int wCountry = 1; wCountry < 43 && AttackWhere == 0; wCountry++)
		{
			GetCountryInfo(wCountry,a);
			int AdjacentCount, AdjacentID;

			if (a.OwnerID == myID && a.EnemyOwnedAdjacentCountries > 0)
			{
				GetAdjacentCountryCount(wCountry, AdjacentCount);
				for (int wAdjacent = 0; wAdjacent < AdjacentCount; wAdjacent++)
				{
					GetAdjacentCountryID(wCountry, wAdjacent, AdjacentID);
					GetCountryInfo(AdjacentID,b);
					if (b.OwnerID != myID && a.ArmyCount > b.ArmyCount)
					{
						AttackWhere = AdjacentID;
						FromWhere = wCountry;
						break;
					}
				}
			}
		}
	}

	nArmiesToUse = 3;

	if (AttackWhere != 0 && FromWhere != 0)
		return TRUE;
	else
		return FALSE;

}

extern "C" void __stdcall DefendCountry(int OpposingArmies, int myArmies, int CountryID, int &DiceToRoll)
{
	// this is called when you are defending a country... 
	// it will only be called when you have at least two armies to defend with,
	// but you may choose to roll one dice if you wish
	DiceToRoll = 2;
}

extern "C" void __stdcall CaptureCountry(int FromWhere, int ToWhere, int minArmies, int maxArmies, int &nArmiesToMove)
{
	// called when you have defeated all enemy armies in a particular country.  with this
	// you can decide how many of those attacking armies to move into the new territory.
	// minArmies is equal to the number of armies that you used to attack on your last roll.
	// maxArmies is the number of armies remaining at the end of the attack.
	// If minArmies == maxArmies, then this function is not called, because it is not necessary.
	int EnemyNeighborArmiesA = 0, EnemyNeighborArmiesB = 0,
		TotalEnemyNeighbors = 0;
	EnemyNeighborArmiesA = TotEnemyArmiesOnAdjCountries(FromWhere);
	EnemyNeighborArmiesB = TotEnemyArmiesOnAdjCountries(ToWhere);
	TotalEnemyNeighbors = EnemyNeighborArmiesA + EnemyNeighborArmiesB;
	if (TotalEnemyNeighbors != 0)
	{
		nArmiesToMove = (1+maxArmies)*(EnemyNeighborArmiesB)/(TotalEnemyNeighbors);
	}
	else
	{
		int A = 1,B = 0;
		// Commented this out while I write the function.
//		A = HowFarAwayIsNearestEnemy(FromWhere);
//		B = HowFarAwayIsNearestEnemy(ToWhere);
		if(A>B)
			nArmiesToMove = maxArmies;
		else nArmiesToMove = minArmies;
	}
// 	nArmiesToMove = maxArmies; Stalin's Philosophy
}

extern "C" BOOL __stdcall DoReinforcement(int &FromWhere, int &ToWhere, int &nArmiesToMove)
{
	// called at the end of your turn.  with this function you have the opportunity to move
	// any number of armies from one country that you own to and adjacent country that you
	// own.. if you wish to do a reinforcement, return TRUE and set the FromWhere, ToWhere, and
	// nArmiesToMove variables, otherwise return FALSE
	return FALSE;
}

extern "C" char * __stdcall GetPlayerName()
{
	// you may put any name you wish your player to be known by here.
	return "Fleet Admiral Starship";
}




