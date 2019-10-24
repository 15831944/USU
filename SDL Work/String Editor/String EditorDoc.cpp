// String EditorDoc.cpp : implementation of the CStringEditorDoc class
//

#include "stdafx.h"
#include "String Editor.h"
#include "StringInfo.h"
#include "String EditorDoc.h"
#include "NewStringTableDlg.h"
#include "String EditorView.h"
#include <fstream.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStringEditorDoc

IMPLEMENT_DYNCREATE(CStringEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CStringEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CStringEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringEditorDoc construction/destruction

CStringEditorDoc::CStringEditorDoc()
{

	m_nStrings=0;// TODO: add one-time construction code here
//	m_s=NULL;
	m_LanguageNames=NULL;
}

CStringEditorDoc::~CStringEditorDoc()
{
//	delete []m_Strings;
//	if (m_s)
//		delete []m_s;
	if (m_LanguageNames)
		delete []m_LanguageNames;
	DeleteFile("C:\\clipboard.txt");
}

BOOL CStringEditorDoc::OnNewDocument()
{
	update=FALSE;
	nextinternal=0;
	hadH=TRUE;
	if (!CDocument::OnNewDocument())
		return FALSE;
/*	DeleteContents();
	int x=m_nLanguages,y;
	m_LanguageNames=new CString[m_nLanguages];
	m_s=new CStringInfo[500];
	for (int z=0;z<500;z++)
		m_s[x].SetString((m_nLanguages));
	for (y=0;y<x;y++)
		m_s[y].m_Strings=new CString[m_nLanguages];
		*/
	CNewStringTableDlg tDlg(this);	
	return (tDlg.DoModal() == IDOK ? TRUE : FALSE);

	//return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStringEditorDoc serialization

void CStringEditorDoc::Serialize(CArchive& ar)
{
	update=FALSE;
	int z;
	CFile* file=ar.GetFile();
	CString Filename=file->GetFilePath();
	Filename.Replace(".str",".h");
	CStringInfo tempi;
	if (ar.IsStoring())
	{
		ofstream fout(Filename);
		ar << nextinternal;
		ar << m_CHARSET;
		ar << m_FontHeight;
		ar << m_FontName;
		ar << m_nLanguages;
		for (int x=0;x<m_nLanguages;x++)
			ar.WriteString(m_LanguageNames[x] + "\n");
		ar << m_nStrings;
		for (x=0;x<m_nStrings;x++)
		{
			tempi=m_s[x];
			ar << m_s[x].internal;
			for(z=0;z<m_nLanguages;z++)
				ar.WriteString(m_s[x].m_Strings[z]+"\n");
			fout << "#define " << m_s[x].m_Symbol << " " << x << endl;
		}
	}
	else
	{

		DeleteContents();
		HANDLE fileIn;
		fileIn = CreateFile(Filename,GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fileIn == INVALID_HANDLE_VALUE)		
			hadH=FALSE;
		else
			hadH=TRUE;
		CloseHandle(fileIn);
		ifstream fin;
		if (hadH)
			fin.open(Filename);
		
		int x=0,y;
		ar >> nextinternal;
		ar >> m_CHARSET;
		ar >> m_FontHeight;
		ar >> m_FontName;
		ar >> m_nLanguages;
		m_LanguageNames=new CString[m_nLanguages];
		for (x=0;x<m_nLanguages;x++)
			ar.ReadString(m_LanguageNames[x]);
		ar >> x;
		char temp[50];
		for (y=0;y<x;y++)
		{
			tempi.SetString(m_nLanguages);
			ar >> tempi.internal;
		//	tempi.internal=x;			
			//			tempi.m_Strings=new CString[m_nLanguages];
			for(z=0;z<m_nLanguages;z++)
				ar.ReadString(tempi.m_Strings[z]);
			if (hadH)
			{
				fin >> temp;
				fin	>> temp;
				tempi.m_Symbol=temp;
				fin >> temp;
			}
			else
				tempi.m_Symbol="";
			m_s.Insert(tempi,y);			
		}
		tempi=m_s[y-1];
		m_nStrings=x;
		tempi.SetString(m_nLanguages);
		//nextinternal=x;


	}
}

/////////////////////////////////////////////////////////////////////////////
// CStringEditorDoc diagnostics

#ifdef _DEBUG
void CStringEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStringEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStringEditorDoc commands

BOOL CStringEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::OnSaveDocument(lpszPathName);
}

void CStringEditorDoc::OnCloseDocument() 
{
/*	if (update)
	{
		int x=MessageBox(NULL,"Would you like to Save before you exit?", "Save?", MB_YESNO);
		if (x==6)
			OnSaveDocument();
	}
	*/
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(update);
	SaveModified();
	CDocument::OnCloseDocument();
}

void CStringEditorDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	POSITION pos = GetFirstViewPosition();
//	CView* pFirstView = GetNextView( pos );
	// This example uses CDocument::GetFirstViewPosition
	// and GetNextView to repaint each view.
	
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf( RUNTIME_CLASS( CStringEditorView ) ) )
		{
			((CStringEditorView *)pView)->DeleteWindowContents();
			break;
		}
	}   

		
	CDocument::DeleteContents();

}
