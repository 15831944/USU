// server.h : main header file for the SERVER application
//

#if !defined(AFX_SERVER_H__61FFC008_A499_11D5_B509_000086204AC6__INCLUDED_)
#define AFX_SERVER_H__61FFC008_A499_11D5_B509_000086204AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"					// main symbols
#include "../common/DString.h"
#include "../common/Configuration.h"

class Configuration;
class Event;
class ServerComChannel;

/////////////////////////////////////////////////////////////////////////////
// CServerApp:
// See server.cpp for the implementation of this class
//

class CServerApp : public CWinApp
{
public:
	CServerApp();
	~CServerApp()
		{  if (conf) delete conf; }

	typedef enum {STARTED, STOPPED} STATUS;

	// Event data manipulation methods
	void loadEventData();
	void unloadEventData();
	int getEventIdx(long id);
	Event* getEvent(long id);
	long getNextEventId();
	int getMaxEventIndex() const { return event_set.GetUpperBound(); }
    int addEvent(Event *e);
	int updateEvent(Event *e);
	int deleteEvent(long id);
    void removeEventData(void);

	// Request processing methods
	void processQuery(const DString& client_ip, UINT client_port, CTime &start_date, CTime &end_date);
	void processNewEvent(const DString& client_ip, UINT client_port);

	// Server startup and shutdown functions
	STATUS start(void);
	STATUS stop(void);
	STATUS getStatus(void) const { return status; }

	// Communication functions
	ServerComChannel* getComChannel() { return com_channel; }

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	// Implementation
	//{{AFX_MSG(CServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// Configuration information
	Configuration*		conf;

	// Event data
	long				next_event_id;		// Next event id
	CPtrArray			event_set;			// Event data
	bool				event_set_status;	// TRUE = o.k., FALSE = Event data is unavailable

	// Communication information
	STATUS				status;
	UINT				local_port;			// local server port
	ServerComChannel*	com_channel;		// Server Communications Channel
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVER_H__61FFC008_A499_11D5_B509_000086204AC6__INCLUDED_)
