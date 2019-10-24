// ComputerPlayer.h: interface for the ComputerPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OMPUTERPLAYER_H__62C84DCF_6DE2_4336_AB40_E25E6D971036__INCLUDED_)
#define AFX_OMPUTERPLAYER_H__62C84DCF_6DE2_4336_AB40_E25E6D971036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ComputerPlayer  
{
public:
	virtual void MakeMove() = 0;
	ComputerPlayer();
	virtual ~ComputerPlayer();
};

#endif // !defined(AFX_OMPUTERPLAYER_H__62C84DCF_6DE2_4336_AB40_E25E6D971036__INCLUDED_)
