// Step.h: interface for the Step class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEP_H__EACAA511_53B6_11D5_A51E_444553540000__INCLUDED_)
#define AFX_STEP_H__EACAA511_53B6_11D5_A51E_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Step  
{
public:
	BOOL AnsweredCorrectly;
	CString RiddleHint;
	CString CompletionInfo;
	CString Distance;
	CString Heading;
	int SecondsToNextStep;
	CString Location;
	CString RiddleText;
	BOOL IsRiddle;
	Step();
	virtual ~Step();
	CString Answer;

};

#endif // !defined(AFX_STEP_H__EACAA511_53B6_11D5_A51E_444553540000__INCLUDED_)
