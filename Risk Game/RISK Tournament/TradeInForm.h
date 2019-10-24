// TradeInForm.h: interface for the CTradeInForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADEINFORM_H__89FBB100_D549_11D5_9E44_00A0CC4138F7__INCLUDED_)
#define AFX_TRADEINFORM_H__89FBB100_D549_11D5_9E44_00A0CC4138F7__INCLUDED_

#include "TypeDecs.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTradeInForm  
{
public:
	int GetTradeInCard(int wCard);
	int CountryCardSelected;
	void SetCard(int handIndex, int cardID);
	BOOL DoTradeIn(int CardCount);
	CTradeInForm();
	virtual ~CTradeInForm();

protected:
	int cardsToTradeIn[5];
	int nCards;
	CARD_DATA m_cset;
	CARD_DATA m_cards;
};

#endif // !defined(AFX_TRADEINFORM_H__89FBB100_D549_11D5_9E44_00A0CC4138F7__INCLUDED_)
