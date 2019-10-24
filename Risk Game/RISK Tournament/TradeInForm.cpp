// TradeInForm.cpp: implementation of the CTradeInForm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RISK Tournament.h"
#include "TradeInForm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTradeInForm::CTradeInForm()
{

}

CTradeInForm::~CTradeInForm()
{

}

BOOL CTradeInForm::DoTradeIn(int CardCount)
{
	nCards = CardCount;
	CountryCardSelected = 0;
    bool validSelection = false;

    int m;
    m = (CardCount < 5 ? 0 : 1);
    if (CallDoTradeIn(CardCount, cardsToTradeIn, m, CompDoTradeIn) == FALSE)
	{
		MsgBox ("CallDoTradeIn returned False");
        ReleaseAndEnd();
    }
	else
	{
		hasCountryCard = 0;
		CountryCardSelected = 0;
	
		// make sure the user has selected valid cards and has 
		// selected each card at most once
		bool CardUsed[10];
		
		for (int i = 0; i < 10; i++)
			CardUsed[i] = false;
		validSelection = true;
		for (i = 0; i < 3; i++)
		{
			if (cardsToTradeIn[i] < CardCount)
			{
				if (CardUsed[cardsToTradeIn[i]] == false)
				{
					CardsUsed[cardsToTradeIn[i]] = true;
				}
				else
				{
					validSelection = false;
					break;
				}
			}
			else
			{
				validSelection = false;
				break;
			}
		}

		if (validSelection)
		{
			validSelection = false;
			if (m_cards.CardType[cardsToTradeIn[0]] == 0 || m_cards.CardType[cardsToTradeIn[1]] == 0 || m_cards.CardType[cardsToTradeIn[2]] == 0 ) 
			{
				// player has a wild card
				validSelection = true;
			}
    
			if ( m_cards.CardType[cardsToTradeIn[0]] == m_cards.CardType[cardsToTradeIn[1]] && m_cards.CardType[cardsToTradeIn[1]] == m_cards.CardType[cardsToTradeIn[2]] ) 
			{
				// three of a kind
				validSelection = true;
			}
    
			if ( m_cards.CardType[cardsToTradeIn[0]] <> m_cards.CardType[cardsToTradeIn[1]] && m_cards.CardType[cardsToTradeIn[1]] <> m_cards.CardType[cardsToTradeIn[2]] && m_cards.CardType[cardsToTradeIn[0]] <> m_cards.CardType[cardsToTradeIn[2]] ) 
			{
				// three that are different
				validSelection = true;
			}
		}
	}
	return validSelection;
}

void CTradeInForm::SetCard(int handIndex, int cardID)
{
	m_cards.wCard[index] = wCard;
    int cType;
    GetCardType(wCard, cType);
    m_cards.CardType[handIndex] = cType;
}

int CTradeInForm::GetTradeInCard(int index)
{
	return m_cards.wCard[cardsToTradeIn[index]];
}
