#if !defined(AFX_GAMEPROCESSORTHREAD_H__95FB4ABF_E67D_4E4A_AD52_003FBF676287__INCLUDED_)
#define AFX_GAMEPROCESSORTHREAD_H__95FB4ABF_E67D_4E4A_AD52_003FBF676287__INCLUDED_

#include "AttackForm.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameProcessorThread.h : header file
//

//#include <fstream.h>
#include "TradeInForm.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CGameProcessorThread thread

/*
enum LastMoveEnum 
{ 
	NoMove = 0,
    MadeAttack = 1,
    Retreat = 2,
    CapturedCountry = 3,
    Defeat = 4
};
*/
enum GamePhaseType { InitialPlacement = 0, TradeIn = 1, TurnPlacement = 2, Attack = 3, Reinforcement = 4 };

class CGameProcessorThread : public CWinThread
{
	DECLARE_DYNCREATE(CGameProcessorThread)
protected:
	
// Attributes
public:
	int nPlayers;
	CString * DLLList;
	int PPG;
	int Repetitions;
	int * gamesPlayed;
	int * currentPlayers;
// Operations
public:
	void SetLastMove(LastMoveEnum lmove, int ToWhere = 0, int FromWhere = 0);
	int RiskCardIndex;
	BOOL RunGameLoop();
	CAttackForm m_AttackForm;

	BOOL IsCardUsed(int wCard);
	void AdvanceToNextPlayer();
	void AttackCountry(int CountryA, int CountryB, int nDiceToRoll = 0);
	void RemoveUsedCards();
	void DoReinforcement(int nArmiesToMove, int CountryA, int CountryB);
	CString GetBasicCountryName(int wCountry);
	int currentArmiesToPlace;
	void DoComputerTurn();
	void ReleaseAndEnd();
	CTradeInForm m_TradeInForm;
	void ContinueInitialPlacement();
	void AttemptToPlaceArmies(int CountryID, int dArmies);
	void HandleTradeIn(int &ArmiesToPlace);
	void DoPlacement();
	void CompPlaceInitialArmies();
	BOOL CountryCaptured;
	void DoArmyPlacement();
	BOOL InitializeGame();
	void WriteToLog(CString logMessage);
	LAST_MOVE_INFO LastMove;
	int nTradeInsDone;
	CARD_DATA cards[6];
	GamePhaseType GamePhase;
	int RiskCards[44];
	COUNTRY_DATA Countries[43];
	void PlaceNewArmies(int pIndex, int CountryID, int nArmies);
	int wPlayer;
	void SetDLLName(int wDLL, CString & name);
	void SetGameData(int m_PPG, int m_nPlayers, int m_nRepetitions, int * m_nGamesPlayed);
	BOOL m_Processing;

	void PlayGame();
	PLAYER_INFO Players[6];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameProcessorThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	CGameProcessorThread();           // protected constructor used by dynamic creation

	virtual ~CGameProcessorThread();
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CGameProcessorThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CGameProcessorThread * gameThread;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEPROCESSORTHREAD_H__95FB4ABF_E67D_4E4A_AD52_003FBF676287__INCLUDED_)
