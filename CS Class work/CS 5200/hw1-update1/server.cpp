/*****************************************************************************
*
*  File:          server.cpp
*  Class:         CServerApp
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 15, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*	Sep. 15, 2001	InitInstance updated so it called loadEventData but bringing
*					up the main dialog box and unloadEventData on exit.
*					An unloadEventData method added to the code.
*
*  Description:
*     A DString is a dynamic string that combines common features
*     of MFC's CString with Unix's String.
*
*/



#include "stdafx.h"
#include "../common/constants.h"
#include "../common/Configuration.h"
#include "../common/Event.h"
#include "server.h"
#include "serverDlg.h"
#include "ServerComChannel.h"
#include "../common/ConfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CServerApp

BEGIN_MESSAGE_MAP(CServerApp, CWinApp)
	//{{AFX_MSG_MAP(CServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerApp construction
CServerApp::CServerApp() :
	event_set(),
	event_set_status(FALSE),
	next_event_id(0),
	local_port(0),
	com_channel(NULL),
	status(STOPPED)
{
	event_set.SetSize(0,30);
}

/////////////////////////////////////////////////////////////////////////////
//
// CServerApp::start()
//
// This method starts the communications for the server and loads the event
// database.
//
CServerApp::STATUS CServerApp::start(void)
{
	if (com_channel) stop();		// stop existing communication channel if
									// one is already starting

	com_channel = new ServerComChannel(local_port);
	status=STARTED;

	// TO DO (later): Add better error handling

	return status;
}

/////////////////////////////////////////////////////////////////////////////
//
// CServerApp::start()
//
// This method starts the communications for the server and loads the event
// database.
//
CServerApp::STATUS CServerApp::stop(void)
{
	if (com_channel)
	{
		delete com_channel;
		com_channel=NULL;
		status=STOPPED;
	}

	return status;
}

/////////////////////////////////////////////////////////////////////////////
// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	DString conf_file("c:\\DCS\\server.ini");

	CConfDlg conf_dlg;
	conf_dlg.setConfFile(conf_file);
	if (conf_dlg.DoModal()==IDOK)
		conf_file = conf_dlg.getConfFile();

	conf = new Configuration(conf_file);


	WSADATA socket_parameters;

	if (!AfxSocketInit(&socket_parameters))
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	local_port = conf->getProfileUShort("Communications","Local_Port",12000);

	loadEventData();			// Load the event data

	CServerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	unloadEventData();			// Save all event data and remove from memory;

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//
//	LoadEventData
//
//	This routine loads all of the Event data from a file.  The name of the
//	file is a parameter in the configuration.
//
void CServerApp::loadEventData()
{
    // The following constants are specific to this version of the LoadEventData
    // function and the format of the Event Data file.  They are not tied to the
    // implementation of the Event class.

	char	datafile[MAX_CONFIG_VALUE_LENGTH+1];
	if (!conf->getProfileString("Data","File",datafile,MAX_CONFIG_VALUE_LENGTH))
		throw InvalidConfigFile("Data file not specified in configuration");

    ifstream in(datafile);
	if (!in.good() || in.peek()==EOF)
	{
		in.close();
		throw GeneralException("Data","Data file cannot be found or is empty");
	}

    while (in.good() && in.peek()!=EOF)
    {
        Event *e = new Event(in);
        addEvent(e);
    }
    next_event_id++;
	event_set_status = TRUE;
    in.close();
}

/////////////////////////////////////////////////////////////////////////////
//
//	unloadEventData
//
//	This routine saves all of the Event data into the data file and removes it
//	from memory.  The name of the file is a parameter in the configuration.
//
void CServerApp::unloadEventData()
{
    // The following constants are specific to this version of the LoadEventData
    // function and the format of the Event Data file.  They are not tied to the
    // implementation of the Event class.

	char	datafile[MAX_CONFIG_LINE_LENGTH+1];
	if (!conf->getProfileString("Data","File",datafile,MAX_CONFIG_LINE_LENGTH))
		throw InvalidConfigFile("Data file not specified in configuration");

    ofstream out(datafile);
	if (!out.good())
	{
		out.close();
		throw GeneralException("Data","Data file cannot for output");
	}

	int max_index = event_set.GetUpperBound();
	for (int i=0; i<=max_index; i++)
	{
		if (event_set[i])
		{
		    Event* tmp = (Event*) event_set[i];
			tmp->save(out);
		}
	}
	event_set_status = FALSE;
    out.close();
}

/////////////////////////////////////////////////////////////////////////////
//
//	GetEventIdx
//
//	This method returns the index of an event, given the id.
//
//	Input:
//		id		Id of Event to look up
//
//	Output:
//		Index of Event object if one was found; Otherwise -1
//
int CServerApp::getEventIdx(long id)
{
    int result=-1;

	int max_index = event_set.GetUpperBound();
	for (int i=0; i<=max_index && result==NULL; i++)
	{
		if (event_set[i])
	    {
		    Event* tmp = (Event*) event_set[i];
		    if (tmp->getId()==id)
				result=i;
	    }
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////
//
//	GetEvent
//
//	This routine looks up a Event by id and retures a pointer to the
//	Event object
//
//	Input:
//		id		Id of Event to look up
//
//	Output:
//		Pointer to Event object if one was found; Otherwise NULL
//
Event* CServerApp::getEvent(long id)
{
    Event* result=NULL;

	int idx = getEventIdx(id);
	if (idx>=0)
		result = (Event*) event_set[idx];

	return result;
}

/////////////////////////////////////////////////////////////////////////////
//
//	GetNextEventId()
//
//	This routine returns the new Event id that can be used in creating a
//	new Event object
//
//	Output:
//		New Event id
//
long CServerApp::getNextEventId()
{
    long result = next_event_id++;
    return result;
}

/////////////////////////////////////////////////////////////////////////////
//
//	AddEvent
//
//	This routine add a Event to the database
//
//	Input:
//		e		A pointer to Event object to add to the database
//
//	Output:
//		The array index where the Event object was address
//
int CServerApp::addEvent(Event *e)
{
    int index = event_set.Add(e);
    if (e->getId()>=next_event_id)
      next_event_id = e->getId()+1;
    return index;
}

/////////////////////////////////////////////////////////////////////////////
//
//	UpdateEvent
//
//	This routine updates a Event to the database
//
//	Input:
//		e		A pointer to Event object to new version of the
//				Event object
//	Output:
//		0		Success
//		-1		Event not found
//		-2		Update was based on old Event data
//
int CServerApp::updateEvent(Event *e)
{
	int result=0;

	// Look up the old Event
	Event* old_e = getEvent(e->getId());

	// If the old Event was found, then proceed otherwise return a -1
	if (old_e)
	{
		*old_e = *e;
		result = 0;
	}
	else
		result = -2;

    return result;
}

/////////////////////////////////////////////////////////////////////////////
//
//	DeleteEvent
//
//	This routine deletes a Event to the database
//
//	Input:
//		id		An event id
//
//	Output:
//		0		Success
//		-1		Event not found
//		-2		Update was based on old Event data
//
int CServerApp::deleteEvent(long id)
{
	int result = -1;
	int i;

	Event* old_e=NULL;

	// Look up the Event in the database
	int max_index = event_set.GetUpperBound();
	for (i=0; i<=max_index && old_e==NULL; i++)
	{
		if (event_set[i])
	    {
		    Event* tmp = (Event*) event_set[i];
		    if (tmp->getId()==id)
			    old_e=tmp;
	    }
	}

	// If the old Event was found, then proceed otherwise return a -1
	if (old_e)
	{
		event_set.RemoveAt(i);
		delete old_e;
		result = 0;
	}
	else
		result = -2;

    return result;
}

//////////////////////////////////////////////////////////////////////////////
//
//	RemoveEventData
//
//	Method to remove all Event from the Event set
//	
void CServerApp::removeEventData(void)
{
	// Clear all Event Data
    int max_index = event_set.GetUpperBound();
    for (int i=0; i<=max_index; i++)
    {
        if (event_set[i])
            delete (Event*) event_set[i];
    }
	event_set.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////////
//
//	ProcessQuery
//
//	Method to processes a request for an event list
//	
void CServerApp::processQuery(CTime &start_date, CTime &end_date)
{
	// CS5700 TO DO: IMPLEMENT THIS METHOD
}

//////////////////////////////////////////////////////////////////////////////
//
//	ProcessNewEvent
//
//	Method to processes a new-event request
//	
void CServerApp::processNewEvent(void)
{
	// CS5700 TO DO: IMPLEMENT THIS METHOD
}
