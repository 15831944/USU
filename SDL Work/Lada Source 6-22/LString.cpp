// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This class contains all the strings in all the languages for the program
// LString.cpp: implementation of the LString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LString.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define NUMBER_OF_TEMP_STRING 100
extern UINT IDS_TEMP;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern int curLanguage; defined in header file

// Constructor
LString::LString()
{
	filen.SetFilePath("Ladastrings.str");
	Lfont=new CFont;
}

// Destructor
LString::~LString()
{
	
	//if (Lfont)
		delete Lfont;
	//if (LNames)
		delete [] LNames;
	//if (Data)
		delete [] Data;
	//Lfont = NULL;
	//LNames = NULL;
	//Data = NULL;
}

// Loads the data from the file
BOOL LString::load()
{	
	int NUMBEROFTEMPSTRINGS=100;
	int x,z;
	CFile * file = NULL;
	TRY
	{
	   file = new CFile(filen.GetFilePath(), CFile::modeRead);
	}
	CATCH( CFileException, e )
	{
		delete file;
		if( e->m_cause == CFileException::fileNotFound )
			MessageBox(NULL, "String file LadaStrings.str not found.  Program cannot load.","Error",MB_ICONSTOP);
		else
			MessageBox(NULL, "Unknown error occured trying to open string file LadaStrings.str.  Program cannot load.","Error",MB_ICONSTOP);
		return FALSE;
	}
	END_CATCH

	int tempi;
	CArchive ar( file, CArchive::load);
	ar >> tempi;
	ar >> m_CHARSET;
	ar >> m_FontHeight;
	ar >> m_FontName;
//	Lfont->CreateFont(m_FontHeight,0,0,0,0,0,0,0,m_CHARSET,0,0,0,0,m_FontName);
	ar >> nLanguages;
	LNames=new CString[nLanguages];
	for (x=0;x<nLanguages;x++)
		ar.ReadString(LNames[x]);
	ar >> nStrings;
	Data=new CString[nLanguages*nStrings+2+NUMBEROFTEMPSTRINGS];
	IDS_TEMP = nStrings;
	for (x=0;x<nStrings;x++)
	{
		ar >> tempi;
		for (z=0;z<nLanguages;z++)
		{
			int wString = x+z*(nStrings);
			ar.ReadString(Data[wString]);
			Data[wString].Replace("\\n","\n");
			Data[wString].Replace("\\t","\t");
			Data[wString].Replace("\\r","\r");
		}
	}
	ar.Close();
	delete file;

	return TRUE;
}

// Return the requested String (x) from the current language
CString LString::get(int x, int lang)//=curLanguage
{
	return (Data[x+lang*(nStrings)]);
}

void LString::ToggleLanguage()
{
	curLanguage=!curLanguage;
}

void LString::set(CString eng, CString russ, int x)
{
	Data[x]=eng;
	Data[x+1*(nStrings)]=russ;
}
