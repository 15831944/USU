// AttackForm.cpp: implementation of the CAttackForm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RISK Tournament.h"
#include "AttackForm.h"
#include "GameProcessorThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAttackForm::CAttackForm()
{

}

CAttackForm::~CAttackForm()
{

}

void CAttackForm::SetInfo(int aCount, int dCount, int CountryA, int CountryB, int dID, int nDiceToRoll)
{
	DefenderID = dID;
    ACount = aCount;
    DCount = dCount;
    TotalADead = 0;
    TotalDDead = 0;
    FromWhichCountryID = CountryA;
    ToWhichCountryID = CountryB;
    ACommitted = nDiceToRoll;
    
}

void CAttackForm::Show()
{
	while (true)
	{
		CompActionD();
		if (ResolveCombat())
			break;
		else
		{
			if (!CompActionA())
			{
				return;
			}
		}
	}
}

template <class T>
void Swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

BOOL CAttackForm::CompActionA()
{
    
	// figure out how many dice to commit
	int result, nArmies, ToWhere, FromWhere;

    if ( CallMakeMove(ToWhere, FromWhere, nArmies, result) == FALSE ) 
	{
        gameThread->WriteToLog ( "CallMakeMove in AttackForm returned FALSE" );
		gameThread->ReleaseAndEnd();
		return FALSE;
    }
    
    if ( (result == FALSE) || (ToWhere != ToWhichCountryID) || (FromWhere != FromWhichCountryID) ) 
	{
		gameThread->SetLastMove (Retreat, ToWhichCountryID, FromWhichCountryID);

		if ( result == FALSE )
		{
			gameThread->GamePhase = Reinforcement;
			return FALSE;
		}
	}
	if ( nArmies > ACount )
		nArmies = ACount;
	if ( nArmies > 3 )
		nArmies = 3;
	if (nArmies < 1)
		nArmies = 1;

	ACommitted = nArmies;
	return TRUE;
}

void CAttackForm::CompActionD()
{
    // figure out how many dice to commit
    int DiceToRoll = 1;
    
    if ( DCount > 1 ) 
	{
        if ( !CallDefendCountry(DefenderID, ACount, DCount, ToWhichCountryID, DiceToRoll)) 
		{
            gameThread->WriteToLog ( "CallDefendCountry returned FALSE" );
            gameThread->ReleaseAndEnd();
        }
    }
    DCommitted = DiceToRoll;
}

BOOL CAttackForm::ResolveCombat() // returns TRUE if someone lost.
{
    int ADie[3];
	int DDie[2];

    ADie[0] = rand() % 6 + 1;
    ADie[1] = rand() % 6 + 1;
    ADie[2] = rand() % 6 + 1;
    DDie[0] = rand() % 6 + 1;
    DDie[1] = rand() % 6 + 1;
    
    if ( ACommitted == 3 ) 
	{
        if ( ADie[2] > ADie[1] && ADie[2] > ADie[0] )  Swap (ADie[2], ADie[0]);
        if ( ADie[1] > ADie[0] ) Swap (ADie[1], ADie[0]);
        if ( ADie[2] > ADie[1] ) Swap (ADie[2], ADie[1]);
	}
    else if ( ACommitted == 2 ) 
	{
        if ( ADie[1] > ADie[0] ) Swap (ADie[1], ADie[0]);
    }
    
    if ( DCommitted == 2 ) 
	{
        if ( DDie[1] > DDie[0] ) Swap (DDie[1], DDie[0]);
    }
    
	int i = 0;
    int ADead = 0, DDead = 0;
    do
	{
        if ( ADie[i] > DDie[i] ) 
            DDead++;
        else
			ADead++;
        i++;
    }
	while (i < ACommitted && i < DCommitted);
    
    ACount -= ADead;
    DCount -= DDead;
    TotalADead += ADead;
    TotalDDead += DDead;
    
    if ( ACount == 0 ) 
	{
		gameThread->SetLastMove (Defeat, FromWhichCountryID, ToWhichCountryID);
    }
    else if ( DCount == 0 ) 
	{
		gameThread->SetLastMove (CapturedCountry, FromWhichCountryID, ToWhichCountryID);
    }
    else
	{
		gameThread->SetLastMove (MadeAttack, FromWhichCountryID, ToWhichCountryID);
        return FALSE;
    }
	return TRUE;
    
}

