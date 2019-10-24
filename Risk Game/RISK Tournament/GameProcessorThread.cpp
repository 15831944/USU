// GameProcessorThread.cpp : implementation file
//

#include "stdafx.h"
#include "RISK Tournament.h"
#include "GameProcessorThread.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGameProcessorThread

IMPLEMENT_DYNCREATE(CGameProcessorThread, CWinThread)

CGameProcessorThread::CGameProcessorThread()
{
	nPlayers = 0;
	DLLList = NULL;
	PPG = 0;
	Repetitions = 0;
	gamesPlayed = 0;
	currentPlayers = NULL;
}

CGameProcessorThread::~CGameProcessorThread()
{
	delete [] currentPlayers;
	delete [] DLLList;
}

BOOL CGameProcessorThread::InitInstance()
{
	m_pMainWnd = NULL;
	m_pActiveWnd = NULL;
	m_bAutoDelete = FALSE;
	
	m_Processing = TRUE;
	// TODO:  perform and per-thread initialization here
	for (int i1 = 0; i1 < nPlayers; i1++)
	{
		currentPlayers[0] = i1;
		for (int i2 = 0; i2 < nPlayers; i2++)
		{
			if (i2 == i1)
				continue;
			currentPlayers[1] = i2;
			if (PPG == 2)
			{
				PlayGame();			
			}
			else
			{
				for (int i3 = 0; i3 < nPlayers; i3++)
				{
					if (i3 == i2 || i3 == i1)
						continue;
					currentPlayers[2] = i3;
					if (PPG == 3)
					{
						PlayGame();
					}
					else
					{
						for (int i4 = 0; i4 < nPlayers; i4++)
						{
							if (i4 = i1 || i4 == i2 || i4 == i3)
								continue;
							currentPlayers[3] = i4;
							if (PPG == 4)
							{
								PlayGame();
							}
							else
							{
								for (int i5 = 0; i5 < nPlayers; i5++)
								{
									if (i5 == i1 || i5 == i2 || i5 == i3 || i5 == i4)
										continue;
									currentPlayers[4] = i5;
									if (PPG == 5)
									{
										PlayGame();
									}
									else
									{
										for (int i6 = 0; i6 < nPlayers; i6++)
										{
											if (i6 == i1 || i6 == i2 || i6 == i3 || i6 == i4 || i6 == i5)
												continue;
											currentPlayers[5] = i6;
											PlayGame();
											
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return FALSE;
}

int CGameProcessorThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	m_Processing = FALSE;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CGameProcessorThread, CWinThread)
	//{{AFX_MSG_MAP(CGameProcessorThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameProcessorThread message handlers

BOOL CGameProcessorThread::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	// run till we're done...

	//return CWinThread::OnIdle(lCount);
	return 1; // means we want more time...
}

void CGameProcessorThread::PlayGame()
{
	for (int wGame = 0; wGame < Repetitions; wGame++)
	{
		if (InitializeGame())
		{
			RunGameLoop();
		}
		else
		{
			
		}
		(*gamesPlayed)++;
	}
}

void CGameProcessorThread::SetGameData(int m_PPG, int m_nPlayers, int m_nRepetitions, int * m_nGamesPlayed)
{
	delete [] currentPlayers;
	delete [] DLLList;
	PPG = m_PPG;
	nPlayers = m_nPlayers;
	Repetitions = m_nRepetitions;
	currentPlayers = new int[PPG];
	for (int i = 0; i < m_PPG; i++)
		currentPlayers[i] = 0;
	DLLList = new CString[nPlayers];
	gamesPlayed = m_nGamesPlayed;
}

void CGameProcessorThread::SetDLLName(int wDLL, CString &name)
{
	DLLList[wDLL] = name;
}

void CGameProcessorThread::PlaceNewArmies(int pIndex, int CountryID, int nArmies)
{
	if (Countries[CountryID].OwnerID == pIndex)
	{
        Players[pIndex].ArmiesToPlace = Players[pIndex].ArmiesToPlace - nArmies;
        Players[pIndex].ArmyCount = Players[pIndex].ArmyCount + nArmies;
        Countries[CountryID].ArmyCount = Countries[CountryID].ArmyCount + nArmies;
    }
}

void CGameProcessorThread::WriteToLog(CString logMessage)
{

}

BOOL CGameProcessorThread::InitializeGame()
{
	int ACount;
    switch(nPlayers)
	{
		case 2: ACount = 40; break;
		case 3: ACount = 35; break;
		case 4: ACount = 30; break;
		case 5: ACount = 25; break;
		case 6: ACount = 20; break;
    }
    
    for (wPlayer = 0; wPlayer < nPlayers; wPlayer++)
	{
        Players[wPlayer].ArmiesToPlace = ACount;
	}
    
    int wCard, cIndex;

    int qcards[43];
    for ( wCard = 1; wCard < 43; wCard++)
        qcards[wCard] = wCard;
    
    wPlayer = 0;
    
    for ( wCard = 42; wCard >= 1; wCard--)
	{   
        cIndex = rand() % wCard + 1;
        // player wPlayer receives card at cIndex
        Players[wPlayer].CountryCount++;
        Countries[qcards[cIndex]].OwnerID = wPlayer;
        PlaceNewArmies(wPlayer, qcards[cIndex], 1);
        qcards[cIndex] = qcards[wCard];
        wPlayer++;
        if (wPlayer == nPlayers)
			wPlayer = 0;
        RiskCards[wCard] = wCard;
    }
    
    RiskCards[0] = 0;   // place wild cards in the deck
    RiskCards[43] = 0;
    
    // there are 44 risk cards in all, need to shuffle the deck, so to speak
    int wSwap, cardA, cardB, tempCard;
    for ( wSwap = 1; wSwap <= 1000; wSwap++)
	{
        cardA = rand() % 44;
        cardB = rand() % 44;
        tempCard = RiskCards[cardA];
        RiskCards[cardA] = RiskCards[cardB];
        RiskCards[cardB] = tempCard;
    }
       
    for ( wPlayer = 0; wPlayer < nPlayers; wPlayer++)
	{
		SetDLLName (wPlayer, DLLList[currentPlayers[wPlayer]]);
    }
    
    GamePhase = InitialPlacement;
    wPlayer = 0;
	nTradeInsDone = 0;
            
    if (!InitializeDLL(Countries, wPlayer, nPlayers, Players, cards, nTradeInsDone, LastMove))
	{
        WriteToLog("Failed to initialize manager DLL.  Program will terminate.");
		return FALSE;
	}
    else
	{
        return TRUE;
    }
}

void CGameProcessorThread::DoArmyPlacement()
{
	// this function is called doGameAction in the VB code

    if (GamePhase == InitialPlacement)
	{
        currentArmiesToPlace = Players[wPlayer].ArmiesToPlace;
        
		if (currentArmiesToPlace > 5)
			currentArmiesToPlace = 5;
   
		if (currentArmiesToPlace > 0)
		    CompPlaceInitialArmies();
   		else
			ContinueInitialPlacement();
	}
    else if (GamePhase == TurnPlacement)
	{
		currentArmiesToPlace = 0;
        CalculateArmiesToPlace (wPlayer, currentArmiesToPlace);
        CountryCaptured = FALSE;
        HandleTradeIn( currentArmiesToPlace );
       	// called to place armies at the start of a turn, 
		// (a different function is called to place armies at the beginning)
		DoPlacement();
    }
}

void CGameProcessorThread::DoPlacement()
{
	int nArmies = 0, wCountry = 0;

    while ( currentArmiesToPlace > 0 )
	{
        if ( CallPlaceArmies(currentArmiesToPlace, wCountry, nArmies) == FALSE )
		{
            WriteToLog ("CallPlaceArmies returned FALSE");
            ReleaseAndEnd();
        }
        if ( nArmies > currentArmiesToPlace )
		{
            nArmies = currentArmiesToPlace;
		}
        else if ( nArmies <= 0 )
		{
            WriteToLog ("Error, computer decided to place 0 armies");
		}
        else if ( Countries[wCountry].OwnerID != wPlayer )
		{
            WriteToLog ("Error, computer decided to place armies on a country it does not own.");
        }
        else
		{
            AttemptToPlaceArmies (wCountry, nArmies);
        }
    }
}

void CGameProcessorThread::CompPlaceInitialArmies()
{
	// do comp sub
    // call comp sub to place armies initially
    while ( currentArmiesToPlace > 0 )
	{
		int wCountry, nArmies;
        if (!CallPlaceArmiesAtStart(currentArmiesToPlace, wCountry, nArmies))
		{
            WriteToLog ("CallPlaceArmiesAtStart returned FALSE");
            ReleaseAndEnd();
        }

        if (nArmies > currentArmiesToPlace)
		{
            nArmies = currentArmiesToPlace;
		}
		else if (nArmies == 0)
		{
            WriteToLog("Error, computer decided to place 0 armies");
		}
        
		if (Countries[wCountry].OwnerID != wPlayer)
		{
            WriteToLog("Error, computer decided to place armies on a country it does not own.");
		}
        else
            AttemptToPlaceArmies( wCountry, nArmies );

    }
}


void CGameProcessorThread::HandleTradeIn(int &ArmiesToPlace)
{
	// determine if player can do a trade in.  if so, present him/her with that option...
    while (Players[wPlayer].CardCount > 2)
	{
        GamePhase = TradeIn;
        int nCards = 8;
		if (Players[wPlayer].CardCount < nCards)
			nCards = Players[wPlayer].CardCount;

        for (int i = 0; i < nCards; i++)
		{
			m_TradeInForm.SetCard(i,cards[wPlayer].wCard[i]);
		}
        
		if (m_TradeInForm.DoTradeIn(nCards))
		{
            RemoveUsedCards();
            ArmiesToPlace = ArmiesToPlace + GetNextTradeInValue();
            nTradeInsDone = nTradeInsDone + 1;
            if (m_TradeInForm.CountryCardSelected != 0)
                PlaceNewArmies (wPlayer, m_TradeInForm.CountryCardSelected, 2);
        }
		else
		{
			break;
		}
    }
	GamePhase = TurnPlacement;
}

void CGameProcessorThread::ContinueInitialPlacement()
{
	// check to see if all players have no armies to place
    BOOL playerFound = FALSE;
    for (int i = 1; i < nPlayers; i++)
	{
        if (Players[(wPlayer + i) % nPlayers].ArmiesToPlace > 0)
		{
            wPlayer = (wPlayer + i) % nPlayers;
            playerFound = TRUE;
            DoArmyPlacement();
        }
    }
    
    if (!playerFound)
	{
        wPlayer = 0;
        GamePhase = TurnPlacement;
        DoArmyPlacement();
	}
}

void CGameProcessorThread::DoComputerTurn()
{
	int FromWhere, ToWhere, nArmies, result;
    
	if ( GamePhase == Attack )
	{
		while ( Players[wPlayer].CountryCount < 42)
		{
			// make all attacks
			if ( CallMakeMove(ToWhere, FromWhere, nArmies, result) == FALSE )
			{
				WriteToLog ("CallMakeMove returned FALSE");
				ReleaseAndEnd();
				break;
			}
        
			if ( result == FALSE )
			{
				GamePhase = Reinforcement;
				DoComputerTurn();
				break;
			}
			else
			{
				// check the validity of the attack
				result = GetAttackError(FromWhere, ToWhere);
				if ( result == FALSE )
				{
					AttackCountry (FromWhere, ToWhere, nArmies);
				}
				else
				{
					CString message;
					message.Format("Invalid Attack: %s, Computer tried to attack %s from %s with %i armies", GetRiskErrorInfo(result), GetBasicCountryName(ToWhere), GetBasicCountryName(FromWhere), nArmies);
					WriteToLog(message);
					GamePhase = Reinforcement;
					DoComputerTurn();
					break;
				}
			}
		}
	}
    else if ( GamePhase == Reinforcement )
	{
        if (CallDoReinforcement(FromWhere, ToWhere, nArmies, result) == FALSE )
		{
            WriteToLog ("CallDoReinforcement returned FALSE");
            ReleaseAndEnd();
        }
        CString message;
        if ( result )
		{
            if (FromWhere < 1 || FromWhere > 42 || ToWhere < 1 || ToWhere > 42 )
			{
				message.Format("Error - computer returned an invalid countryID.  FromWhere = %i, ToWhere = %i",FromWhere,ToWhere);
				WriteToLog(message);
			}
            else if ( Countries[FromWhere].OwnerID != wPlayer )
			{
				message.Format("Error - computer tried to make a reinforcement from country %i (%s) which they do not own.",FromWhere,GetBasicCountryName(FromWhere));
				WriteToLog(message);
			}
            else if ( Countries[ToWhere].OwnerID != wPlayer )
			{
				message.Format("Error - computer tried to make a reinforcement to country %i (%s) which they do not own.",ToWhere,GetBasicCountryName(ToWhere));
				WriteToLog(message);
			}
            else if ( Countries[FromWhere].ArmyCount < 2 )
			{
                message.Format("Error - computer tried to make a reinforcement from a country with one army.  CountryID = %i (%s)", FromWhere, GetBasicCountryName(FromWhere));
				WriteToLog(message);
			}
            else if ( nArmies < 1 )
			{
                message.Format("DoReinforcement returned true and computer requested to move %i armies as a reinforcement.", nArmies);
				WriteToLog(message);
			}
            else if (!AreCountriesAdjacent(FromWhere, ToWhere))
			{
				message.Format("Error - computer tried to reinforce armies between non-adjacent countries. (%s, %s)",GetBasicCountryName(FromWhere),GetBasicCountryName(ToWhere));
				WriteToLog(message);
			}
			else
			{
				if ( nArmies >= Countries[FromWhere].ArmyCount )
					nArmies = Countries[FromWhere].ArmyCount - 1;
				DoReinforcement (nArmies, FromWhere, ToWhere);
			}
			//WriteToLog playerName(wPlayer) & " has made a reinforcement to " + GetBasicCountryName(ToWhere), , , 1000
		}
		
	}

}

void CGameProcessorThread::DoReinforcement(int nArmiesToMove, int CountryA, int CountryB)
{
    Countries[CountryA].ArmyCount -= nArmiesToMove;
    Countries[CountryB].ArmyCount += nArmiesToMove;
}

void CGameProcessorThread::AttemptToPlaceArmies(int CountryID, int dArmies)
{
    // called during place armies
    if ( Countries[CountryID].OwnerID == wPlayer ) 
	{        
        if ( currentArmiesToPlace > 0 ) 
		{
			if (dArmies > currentArmiesToPlace)
				dArmies = currentArmiesToPlace;
            PlaceNewArmies(wPlayer, CountryID, dArmies);
            currentArmiesToPlace -= dArmies;
        }
        
        //    WriteToLog playerName(wPlayer) & " has placed armies in " & GetBasicCountryName(CountryID), , , 1000
        
        if ( currentArmiesToPlace == 0 ) 
		{
            if ( GamePhase == InitialPlacement ) 
			{
                wPlayer++;
                if ( wPlayer == nPlayers ) 
					wPlayer = 0;
                
                DoArmyPlacement();
			}
            else if ( GamePhase == TurnPlacement ) 
			{
                GamePhase = Attack;   
			}
            else
			{
                WriteToLog ("Error, AttemptToPlaceArmies called when gamephase != 0 and gamephase != 1");
            }
        }
	}   
    else
	{
        WriteToLog ("You may not place armies there.  You do not own this country."); //, vbInformation
    }
}

void CGameProcessorThread::ReleaseAndEnd()
{

}

CString CGameProcessorThread::GetBasicCountryName(int wCountry)
{
	CString name;
	GetCountryName(wCountry,name.GetBuffer(100));
	name.ReleaseBuffer();
	return name;
}

void CGameProcessorThread::RemoveUsedCards()
{
    int pos, unusedPos;
	BOOL unusedFound;

    for ( pos = 0; pos < Players[wPlayer].CardCount; pos++)
	{
        if ( IsCardUsed(pos) == TRUE ) 
		{
            unusedFound = FALSE;
            for ( unusedPos = pos + 1; unusedPos < Players[wPlayer].CardCount; unusedPos++)
			{
                if ( IsCardUsed(unusedPos) == FALSE ) 
				{
					unusedFound = TRUE;
					break;
				}
			}
			if (unusedFound == TRUE)
			{
			    int cType, wCard;
                cType = cards[wPlayer].cardType[pos];
                wCard = cards[wPlayer].wCard[pos];
                cards[wPlayer].cardType[pos] = cards[wPlayer].cardType[unusedPos];
                cards[wPlayer].wCard[pos] = cards[wPlayer].wCard[unusedPos];
                cards[wPlayer].cardType[unusedPos] = cType;
                cards[wPlayer].wCard[unusedPos] = wCard;
            }
        }
    }
    Players[wPlayer].CardCount -= 3;

	
}

void CGameProcessorThread::AttackCountry(int CountryA, int CountryB, int nDiceToRoll) // = 0
{    
    int DefenderID = Countries[CountryB].OwnerID;
       
    m_AttackForm.SetInfo (Countries[CountryA].ArmyCount - 1, 
        Countries[CountryB].ArmyCount, 
        CountryA, 
        CountryB, 
        DefenderID, 
        nDiceToRoll);
        
    m_AttackForm.Show();
    
    Players[wPlayer].ArmyCount -= m_AttackForm.TotalADead;
    Players[DefenderID].ArmyCount -= m_AttackForm.TotalDDead;
    
    if ( m_AttackForm.ACount == 0 ) 
	{
        // attacker must have died
        Countries[CountryA].ArmyCount = 1;
        Countries[CountryB].ArmyCount -= m_AttackForm.TotalDDead;
	}
    else if ( m_AttackForm.DCount == 0 ) 
	{
        // defender must have died
        int menToMove;
        if ( m_AttackForm.ACommitted != m_AttackForm.ACount ) 
		{
            int mMove;
            if ( CallCaptureCountry(CountryA, CountryB, m_AttackForm.ACommitted, m_AttackForm.ACount, mMove) == FALSE ) 
			{
                WriteToLog ("CallCaptureCountry returned False");
                ReleaseAndEnd();
            }
            menToMove = mMove;
            // do some validation
            if ( menToMove < m_AttackForm.ACommitted ) 
                menToMove = m_AttackForm.ACommitted;
            else if ( menToMove > m_AttackForm.ACount ) 
                menToMove = m_AttackForm.ACount;
            
        } 
		else 
		{
            menToMove = m_AttackForm.ACommitted;
        }
        Countries[CountryA].ArmyCount = 1 + m_AttackForm.ACount - menToMove;
        Countries[CountryB].ArmyCount = menToMove;
        if ( Countries[CountryA].ArmyCount < 1 || Countries[CountryB].ArmyCount < 1 ) 
		{
            WriteToLog ("Error: Armies in a country < 1");
        }
        Countries[CountryB].OwnerID = wPlayer;
        Players[wPlayer].CountryCount++;
        Players[DefenderID].CountryCount--;
        CountryCaptured = TRUE;
        if ( Players[DefenderID].CountryCount == 0 ) 
		{
            // this player has been destroyed... fork over the risk cards
            int wCard;
            for ( wCard = 0; wCard < Players[DefenderID].CardCount; wCard++)
			{
                cards[wPlayer].cardType[Players[wPlayer].CardCount] = cards[DefenderID].cardType[wCard];
                cards[wPlayer].wCard[Players[wPlayer].CardCount] = cards[DefenderID].wCard[wCard];
                Players[wPlayer].CardCount++;
            }
                
            Players[DefenderID].IsPlayerAlive = FALSE;
        }
        
    } 
	else 
	{
        // player must have retreated
        Countries[CountryA].ArmyCount = 1 + m_AttackForm.ACount;
        Countries[CountryB].ArmyCount -= m_AttackForm.TotalDDead;
    }
    
    
    if ( Players[wPlayer].CountryCount < 42 ) 
	{
		if ( Players[wPlayer].CardCount > 5 ) 
		{
            // got to do a trade in now
            currentArmiesToPlace = 0;
			while (Players[wPlayer].CardCount > 4)
			{
				HandleTradeIn (currentArmiesToPlace);
			}
            DoPlacement ();
        }
    }
        
}

void CGameProcessorThread::AdvanceToNextPlayer()
{
   
    if ( CountryCaptured && Players[wPlayer].CardCount < 6 ) 
	{
        // give player a risk card
        int c, cType;
        c = RiskCards[RiskCardIndex];
        GetCardType (c, cType);
        cards[wPlayer].cardType[Players[wPlayer].CardCount] = cType;
        cards[wPlayer].wCard[Players[wPlayer].CardCount] = c;
        Players[wPlayer].CardCount++;
        
        RiskCardIndex++;
        if ( RiskCardIndex == 44 )
			RiskCardIndex = 0;
    }
	
	do 
	{
        wPlayer++;
        if ( wPlayer == nPlayers )
			wPlayer = 0;
	}
    while (Players[wPlayer].IsPlayerAlive == FALSE);

}

BOOL CGameProcessorThread::IsCardUsed(int wCard)
{
    for (int i = 0; i < 3; i++)
	{
        if (cards[wPlayer].wCard[wCard] == m_TradeInForm.GetTradeInCard(i))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGameProcessorThread::RunGameLoop()
{
	DoArmyPlacement();

	while (true)
	{
		GamePhase = TurnPlacement;
		DoArmyPlacement();
		
		GamePhase = Attack;
        LastMove.LastAction = NoMove;
        DoComputerTurn();
		if (Players[wPlayer].CountryCount < 42)
			AdvanceToNextPlayer();
		else
			break;
	}
	return TRUE;
}

void CGameProcessorThread::SetLastMove(LastMoveEnum lMove, int ToWhere, int FromWhere)
{
	LastMove.LastAction = lMove;
	LastMove.FromID = FromWhere;
	LastMove.ToID = ToWhere;
}
