// AttackForm.h: interface for the CAttackForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTACKFORM_H__CB94D200_EFD8_11D5_B023_0002E3059EB4__INCLUDED_)
#define AFX_ATTACKFORM_H__CB94D200_EFD8_11D5_B023_0002E3059EB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGameProcessorThread;

class CAttackForm  
{
public:
	CGameProcessorThread * gameThread;
	int ACommitted;
	int DCount;
	int ACount;
	int TotalDDead;
	int TotalADead;
	void Show();
	void SetInfo(int aCount, int dCount, int CountryA, int CountryB, int dID, int nDiceToRoll);
	CAttackForm();
	virtual ~CAttackForm();
private:
	int FromWhichCountryID;
	int DCommitted;
	int ToWhichCountryID;
	int DefenderID;
	BOOL CompActionA();
	void CompActionD();
	BOOL ResolveCombat();
};

#endif // !defined(AFX_ATTACKFORM_H__CB94D200_EFD8_11D5_B023_0002E3059EB4__INCLUDED_)
