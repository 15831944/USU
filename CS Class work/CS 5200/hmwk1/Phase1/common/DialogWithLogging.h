/*****************************************************************************
*
*  File:          DialogWithLogging.h
*  Class:         DialogWithLogging
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*    Sep. 5, 2001  Initial version
*
*  Description:
*    An object of this class is a dialog box that includes a logging feature.
*	 The class also keeps track of the current logging window.
*
*    This is pure virtual class.  Classes derived from it must implement the
*	 WriteToLog method.
*
*/

#pragma once

class DialogWithLogging : public CDialog
{
protected:
	static DialogWithLogging* current_log_window;

// Construction
public:
	DialogWithLogging(UINT nIDTemplate, CWnd* pParent = NULL) :
		CDialog(nIDTemplate, pParent) {}
										// standard constructor
	static void SetCurrentLoggingWindow(DialogWithLogging* wnd)
		{ current_log_window=wnd; }
	static void Log(const CString& text)
		{
		  if (current_log_window)
		    current_log_window->WriteToLog(text);
		}

private:
	virtual void WriteToLog(const CString& text) = 0;

};

