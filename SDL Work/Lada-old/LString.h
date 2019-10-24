// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This class contains all the strings in all the languages for the program
// LString.h: interface for the LString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LSTRING_H__5C7EC1C0_A5BD_11D4_8BFB_0020781F78D7__INCLUDED_)
#define AFX_LSTRING_H__5C7EC1C0_A5BD_11D4_8BFB_0020781F78D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern int curLanguage; // The current language

class LString  
{
public:
	void set(CString eng, CString russ, int num);
	void ToggleLanguage();
	CFont* Lfont;		// This is the font being used
	CString get(int, int lang = curLanguage);	// This gets the called for string
	CFile filen;		// This is the file that contains the data
	BOOL load();		// This loads the Strings from a file
	CString* Data;		// This holds the Strings
	CString* LNames;	// This holds the Language Names
	int m_FontHeight;	// The height of the font
	int m_CHARSET;		// The charset of the font
	CString m_FontName;	// The name of the font
	int nLanguages;		// The number of languages
	int nStrings;		// The number of strings
	LString();			// Constructor
	virtual ~LString();	// Destructor

};

#endif // !defined(AFX_LSTRING_H__5C7EC1C0_A5BD_11D4_8BFB_0020781F78D7__INCLUDED_)
