// String EditorView.cpp : implementation of the CStringEditorView class
//

#include "stdafx.h"
#include "String Editor.h"
#include "String EditorDoc.h"
#include "String EditorView.h"
#include "String EditorDoc.h"
#include "StringProperties.h"
#include "StringInfo.h"
#include "Find.h"
#include <fstream.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char* clipboard="C:\\clipboard.txt";
/////////////////////////////////////////////////////////////////////////////
// CStringEditorView

IMPLEMENT_DYNCREATE(CStringEditorView, CListView)

BEGIN_MESSAGE_MAP(CStringEditorView, CListView)
	//{{AFX_MSG_MAP(CStringEditorView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_PASTE, OnPaste)
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(IDC_NEW_STRING, OnNewString)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringEditorView construction/destruction

CStringEditorView::CStringEditorView()
{

	pDoc=NULL;

	rightClickMenu=NULL;
	m_buffer=NULL;

}

CStringEditorView::~CStringEditorView()
{
	delete pfont;
	delete printfont;
	delete rightClickMenu;
}

BOOL CStringEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStringEditorView drawing

void CStringEditorView::OnDraw(CDC* pDC)
{
	CStringEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CStringEditorView::OnInitialUpdate()
{

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	// this code only works for a report-mode list view
	pDoc = GetDocument();
		//CFont Hello;
//	if (pDoc->m_FontHeight<0)
//		pDoc->m_FontHeight*=-1;
		pfont=new CFont;
		pfont->CreateFont(
				pDoc->m_FontHeight,                        // nHeight
				0,                         // nWidth
				0,                         // nEscapement
				0,                         // nOrientation
				FW_NORMAL,                 // nWeight   
				0,                     // bItalic
				0,                     // bUnderline
				0,                         // cStrikeOut
				pDoc->m_CHARSET,              // nCharSet
				0,        // nOutPrecision
				0,       // nClipPrecision
				0,           // nQuality
				0,  // nPitchAndFamily   
				pDoc->m_FontName);    
	printfont=new CFont;
	printfont->CreateFont(
				3*pDoc->m_FontHeight,                        // nHeight
				0,                         // nWidth
				0,                         // nEscapement
				0,                         // nOrientation
				FW_NORMAL,                 // nWeight   
				0,                     // bItalic
				0,                     // bUnderline
				0,                         // cStrikeOut
				pDoc->m_CHARSET,              // nCharSet
				0,        // nOutPrecision
				0,       // nClipPrecision
				0,           // nQuality
				0,  // nPitchAndFamily   
				pDoc->m_FontName);    
   
//	docfont.CreateFont(pDoc->m_FontHeight,0,0,0,FW_NORMAL,0,0,0,pDoc->m_CHARSET,0,0,0,0,pDoc->m_FontName);
	GetListCtrl().SetFont(pfont);
	//GetListCtrl().SetFont(&docfont);

	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	ASSERT(GetStyle() & LVS_REPORT);
   // Gain a reference to the list control itself
   CListCtrl& theCtrl = GetListCtrl();
   int i;
   // Insert a column. This override is the most convenient.
   theCtrl.InsertColumn(0, _T("Resource Symbol"), LVCFMT_LEFT);
   theCtrl.InsertColumn(1, _T("Resource ID"), LVCFMT_LEFT);
   
   for (i = 0; i < pDoc->m_nLanguages; i++)
   {
		theCtrl.InsertColumn(2+i, _T(pDoc->m_LanguageNames[i]), LVCFMT_LEFT);
   }
   

   	pDoc=GetDocument();
	CStringInfo tempi;
	for (int x=0;x<pDoc->m_nStrings;x++)
	{
		GetListCtrl().InsertItem(x,pDoc->m_s[x].m_Symbol);
		char temp[5];
		tempi=pDoc->m_s[x];
		pDoc->m_s[x].m_ID=x;
		wsprintf(temp,"%i",pDoc->m_s[x].m_ID);
		GetListCtrl().SetItemText(x,1,temp);
		for (int y=0;y<pDoc->m_nLanguages;y++)
			GetListCtrl().SetItemText(x,y+2,pDoc->m_s[x].m_Strings[y]);		
	}
  
 	theCtrl.InsertItem(pDoc->m_nStrings,NULL);
	for (i = 0; i < pDoc->m_nLanguages + 2; i++)
	{
		theCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
	
	
	if (!rightClickMenu)
	{
		rightClickMenu = new CMenu;
		rightClickMenu->CreatePopupMenu();
		rightClickMenu->AppendMenu(MF_ENABLED, ID_EDIT_CUT, "Cu&t" );
		rightClickMenu->AppendMenu(MF_ENABLED, ID_EDIT_COPY, "&Copy" );
		rightClickMenu->AppendMenu(MF_ENABLED, ID_EDIT_PASTE, "&Paste" );
		rightClickMenu->AppendMenu(MF_ENABLED, ID_DELETE, "&Delete" );
		rightClickMenu->AppendMenu(MF_SEPARATOR);
		rightClickMenu->AppendMenu(MF_ENABLED, IDC_NEW_STRING, "&New String" );
		rightClickMenu->AppendMenu(MF_SEPARATOR);
		rightClickMenu->AppendMenu(MF_ENABLED, ID_PROPERTIES, "&Properties" );
	}
	
	//rightClickMenu->LoadMenu(IDR_RIGHTPOPUP);
	CString String;
	rightClickMenu->GetMenuString( 0, String, MF_BYPOSITION ); 
	
	Invalidate();

	CListView::OnInitialUpdate();
	pDoc->UpdateAllViews(NULL);
	//m_buffer.SetString(pDoc->m_nLanguages, "", 0,  NULL);

}

/////////////////////////////////////////////////////////////////////////////
// CStringEditorView printing

BOOL CStringEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	//pInfo->m_rectDraw.Size().cy;


	pInfo->SetMaxPage(pDoc->m_nStrings);
	pInfo->SetMinPage(0);
	// default preparation
	BOOL bRet = DoPreparePrinting(pInfo);   // default preparation
	pInfo->m_nNumPreviewPages = pDoc->m_nStrings;  // Preview 2 pages at a time
	// Set this value after calling DoPreparePrinting to override
	// value read from .INI file
	return bRet;
}

void CStringEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SelectObject(printfont);
	current=pInfo->GetFromPage();

}

void CStringEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStringEditorView diagnostics

#ifdef _DEBUG
void CStringEditorView::AssertValid() const
{
	CListView::AssertValid();
}

void CStringEditorView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CStringEditorDoc* CStringEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStringEditorDoc)));
	return (CStringEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStringEditorView message handlers
void CStringEditorView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}


void CStringEditorView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CStringEditorView::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	pDispInfo->item;
	// it is either a new item or an existing item

	// return false to allow user to edit this control
	// this message is sent when a user begins editing 
	// an item in a list control
	// LVN_ENDLABELEDIT  is sent when they finish.
	// custom editing can be done by use the geteditcontrol function.
	//CEdit* pmyEdit = pmyListCtrl->EditLabel(1);
	// I get the impression that can be used to force the editing 
	// of a label....  First the focus should be set to the ListView window...
	*pResult = 0;
}

void CStringEditorView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	const MSG *pMSG = GetCurrentMessage();
	memcpy(&m_messPoint,&pMSG->pt,sizeof(POINT));
	rightClickMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_LEFTBUTTON, pMSG->pt.x, 
      pMSG->pt.y, this);
}


void CStringEditorView::OnNewString()
{
	NewString(GetListCtrl().GetSelectionMark());
}

void CStringEditorView::OnDelete() 
{
	if (pDoc->hadH)
	{
		POSITION pos=GetListCtrl().GetFirstSelectedItemPosition();
		int item;
		pDoc->update=TRUE;
		int z=GetListCtrl().GetItemCount();
		while(pos)
		{
			pos=GetListCtrl().GetFirstSelectedItemPosition();
			item=GetListCtrl().GetNextSelectedItem(pos);
			if (item==-1 || item==pDoc->m_nStrings)
				return;
			GetListCtrl().DeleteItem(item);
			pDoc->m_s.Remove(item);
			pDoc->m_nStrings--;
	//		Reset();
			char temp[5];
			CStringInfo * ptrData = &pDoc->m_s[item];
			for (int x=item;x<pDoc->m_nStrings;x++)
			{
				pDoc->m_s[x].m_ID=x;
				wsprintf(temp,"%i",pDoc->m_s[x].m_ID);
				GetListCtrl().SetItemText(x,1,temp);
			}
			item--;	//if two are in a row this allows both to be deleted
		}
	}
	else
		MessageBox("You need the .h file to delete from your str file");

}	

void CStringEditorView::OnEditCut() 
{
	OnEditCopy();
	OnDelete();
}

void CStringEditorView::OnEditPaste() 
{
	if (pDoc->hadH)
	{
		pDoc->update=TRUE;
		CFile clip(clipboard,CFile::modeRead);
		CArchive ar(&clip,CArchive::load);
		CString temp;
		int x=0,y,z;
		ar >> x;
		CStringInfo tempi;
		for (y=0;y<x;y++)
		{
			int item=GetListCtrl().GetSelectionMark();
			ar.ReadString(tempi.m_Symbol);
			for(z=0;z<pDoc->m_nLanguages;z++)
			{
				ar.ReadString(tempi.m_Strings[z]);
			}
			GetListCtrl().InsertItem(item,tempi.m_Symbol);
			char temp[5];
			wsprintf(temp,"%i",item);
			GetListCtrl().SetItemText(item,1,temp);
			for (int x=0;x<pDoc->m_nLanguages;x++)
				GetListCtrl().SetItemText(item,x+2,tempi.m_Strings[x]);
			pDoc->m_nStrings++;
			tempi.internal=pDoc->nextinternal;
			pDoc->nextinternal++;
			pDoc->m_s.Insert(tempi,item);
			for (x=item;x<pDoc->m_nStrings;x++)
			{
				item=x;
				wsprintf(temp,"%i",item);
				GetListCtrl().SetItemText(x,1,temp);
			}
		}
	}
	else
		MessageBox("You can not copy to this document without the .h file.");
}

void CStringEditorView::OnEditCopy() 
{
	pDoc->update=TRUE;
	int z=GetListCtrl().GetSelectedCount();
	int y=GetListCtrl().GetItemCount();
	//Reset();
	m_buffercount=0;
	POSITION pos=GetListCtrl().GetFirstSelectedItemPosition();
	int item;
	CFile clip(clipboard,CFile::modeWrite);
	CArchive ar(&clip,CArchive::store);
	ar << z;
	while (pos)
	{
		item=GetListCtrl().GetNextSelectedItem(pos);
		if (item==pDoc->m_nStrings)
			z--;
		else
		{
			ar.WriteString(pDoc->m_s[item].m_Symbol+"\n");
			for (int x=0;x<pDoc->m_nLanguages;x++)
				ar.WriteString(pDoc->m_s[item].m_Strings[x]+"\n");
	//		m_buffer[m_buffercount].m_Symbol=pDoc->m_s[item].m_Symbol;
			m_buffercount++;
		}
	}
	ar.Close();
}

void CStringEditorView::OnPaste() 
{
	
}

void CStringEditorView::OnProperties() 
{
	pDoc->update=TRUE;
	int item=GetListCtrl().GetSelectionMark();
	if (item==pDoc->m_nStrings || item==-1)
		NewString(item);
	else
	{
		CStringInfo * ptrData = &pDoc->m_s[item];
		StringProperties dlg(pDoc->m_LanguageNames,pDoc->m_nLanguages,ptrData,&docfont);
		dlg.DoModal();
	//	GetListCtrl().InsertItem(pDoc->m_nStrings,ptrData->m_Symbol);
		char temp[5];
		GetListCtrl().SetItemText(item,0,ptrData->m_Symbol);
		ptrData->m_ID=item;
		wsprintf(temp,"%i",ptrData->m_ID);
		GetListCtrl().SetItemText(item,1,temp);
		for (int y=0;y<pDoc->m_nLanguages;y++)
			GetListCtrl().SetItemText(item,y+2,ptrData->m_Strings[y]);
	}
	//Reset();
	
}

void CStringEditorView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	pDoc->update=TRUE;
	int now;
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	if (pLVKeyDow->wVKey==13)
		NewString(GetListCtrl().GetSelectionMark());
	if (pLVKeyDow->wVKey==46)
		OnDelete();
	if (pLVKeyDow->wVKey==70)
	{
		now=GetListCtrl().GetSelectionMark();
		GetListCtrl().SetItemState(GetListCtrl().GetSelectionMark(),0,LVIS_SELECTED);
		CFind dlg(pDoc);
		dlg.DoModal();
		if (pDoc->m_foundnumber>-1)
		{
			GetListCtrl().SetItemState(pDoc->m_foundnumber,2,LVIS_SELECTED);
			GetListCtrl().EnsureVisible(pDoc->m_foundnumber,TRUE);		
		}
		else
			MessageBox("String not found","Not Found");
	}

	if (pLVKeyDow->wVKey==114 && pDoc->m_foundnumber>-1)
	{

		OnScroll(SB_LINEDOWN,pDoc->m_foundnumber-now);
		int temp=pDoc->m_foundnumber;
		GetListCtrl().SetItemState(pDoc->m_foundnumber,0,LVIS_SELECTED);
		for (int x=pDoc->m_foundnumber+1;(x<pDoc->m_nStrings && pDoc->m_foundnumber==temp);x++)
		{
			if (pDoc->m_findlabel==TRUE && IsInside(pDoc->m_findfind,pDoc->m_s[x].m_Symbol))
			{
				pDoc->m_foundnumber=x;
			}
			if (pDoc->m_findstring==TRUE)
			{
				for (int y=0; y<pDoc->m_nLanguages;y++)
					if (IsInside(pDoc->m_findfind,pDoc->m_s[x].m_Strings[y]))
					{
						pDoc->m_foundnumber=x;
					}
			}
		}
		if (pDoc->m_foundnumber==temp)
		{
			bool found=false;
			for (int x=0;(x<=temp)&&(!found);x++)
			{
				if (pDoc->m_findlabel==TRUE && IsInside(pDoc->m_findfind,pDoc->m_s[x].m_Symbol))
				{
					found=true;
					pDoc->m_foundnumber=x;
				}
				if (pDoc->m_findstring==TRUE)
				{
					for (int y=0; y<pDoc->m_nLanguages;y++)
						if (IsInside(pDoc->m_findfind,pDoc->m_s[x].m_Strings[y]))
						{
							found=true;
							pDoc->m_foundnumber=x;
						}
				}
			}
		}
		if (pDoc->m_foundnumber>-1)
		{
			GetListCtrl().SetItemState(pDoc->m_foundnumber,2,LVIS_SELECTED);
			//GetListCtrl().SetScrollPos(SB_VERT,pDoc->m_foundnumber);
			GetListCtrl().EnsureVisible(pDoc->m_foundnumber,TRUE);
		}
		else
			MessageBox("String not found","Not Found");
	}

	
	*pResult = 0;
}



void CStringEditorView::NewString(int item)
{
	if (pDoc->hadH)
	{
		pDoc->update=TRUE;
		if (item==-1)
			item=pDoc->m_nStrings;
		CStringInfo* tempi=new CStringInfo;
		tempi->SetString(pDoc->m_nLanguages,"",0,NULL);
		StringProperties dlg(pDoc->m_LanguageNames,pDoc->m_nLanguages,tempi,&docfont);
		dlg.DoModal();
		if (tempi->m_Symbol=="" || tempi->m_Symbol=="IDS_")
			return;
		GetListCtrl().InsertItem(item,tempi->m_Symbol);
		char temp[5];
		tempi->m_ID=item;
		wsprintf(temp,"%i",tempi->m_ID);
		GetListCtrl().SetItemText(item,1,temp);
		for (int y=0;y<pDoc->m_nLanguages;y++)
			GetListCtrl().SetItemText(item,y+2,tempi->m_Strings[y]);
		tempi->internal=pDoc->nextinternal;
		pDoc->m_s.Insert(*tempi,item);
		pDoc->nextinternal++;
		pDoc->m_nStrings++;
		for (int x=item;x<pDoc->m_nStrings;x++)
		{
			pDoc->m_s[x].m_ID=x;
			wsprintf(temp,"%i",pDoc->m_s[x].m_ID);
			GetListCtrl().SetItemText(x,1,temp);
		}
	//	tempi=new CStringInfo;
	//	Reset();
	}
	else
		MessageBox("You must have the .h file to add strings");

}

void CStringEditorView::Reset()
{
	for (int x=0;x<pDoc->m_nStrings;x++)
	{
		if (pDoc->m_s[x].m_Strings==NULL)
			pDoc->m_s[x].SetString(pDoc->m_nLanguages);			;
			
		pDoc->m_s[x].m_Symbol=GetListCtrl().GetItemText(x,0);
		for (int y=0;y<pDoc->m_nLanguages;y++)
			pDoc->m_s[x].m_Strings[y]=GetListCtrl().GetItemText(x,y+2);
	}
}

void CStringEditorView::CheckForDuplicate()
{
	int x=pDoc->m_nStrings,y,z;
	CString message="";
	for (y=0;y<x;y++)
		for (z=0;z<y;z++)
		{
			if (pDoc->m_s[y].m_Symbol==pDoc->m_s[z].m_Symbol)
			{
				message="Duplicate " + pDoc->m_s[z].m_Symbol;
				MessageBox(message,"Duplicate",MB_OK);
			}
		}




}

void CStringEditorView::DeleteWindowContents()
{
	if (pDoc)
	{
		for (int item=0;item<pDoc->m_nStrings+1;item++)
			GetListCtrl().DeleteItem(0);
		for (int x=0;x<pDoc->m_nLanguages;x++)
			GetListCtrl().DeleteColumn(2);
		GetListCtrl().DeleteColumn(1);
		GetListCtrl().DeleteColumn(0);
		pDoc=NULL;
		
	}


}

void CStringEditorView::load(int num)
{
	pDoc=GetDocument();
	for (int x=0;x<num;x++)
	{
		GetListCtrl().InsertItem(x,pDoc->m_s[x].m_Symbol);
		char temp[5];
		pDoc->m_s[x].m_ID=x;
		wsprintf(temp,"%i",pDoc->m_s[x].m_ID);
		GetListCtrl().SetItemText(x,1,temp);
		GetListCtrl().SetItemText(x,2,pDoc->m_s[x].m_Strings[0]);
		GetListCtrl().SetItemText(x,3,pDoc->m_s[x].m_Strings[1]);
		pDoc->m_nStrings++;
	}
}

void CStringEditorView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnProperties();		
	*pResult = 0;
}

BOOL CStringEditorView::IsInside(CString a, CString b)
{
	CString temp;
	int y=b.GetLength();
	int z=a.GetLength();
	for (int x=0;x<(y-z+1);x++)
	{
		temp=b.Mid(x);
		temp=temp.Left(z);
		if (!temp.CollateNoCase(a))
		{
			return TRUE;
		}
	}
	return FALSE;

}

void CStringEditorView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{

	//if (pInfo->m_nCurPage==0)
	//	pInfo->m_nCurPage=1;
	int size=abs(3*pDoc->m_FontHeight)*3/2;	
	lh=pInfo->m_rectDraw.bottom/(abs(3*pDoc->m_FontHeight)*3/2);
	lpp=lh/(pDoc->m_nLanguages+1);
	//if (pInfo->m_nCurPage==0)
	//	current=0;
	//else
	//	current=(pInfo->m_nCurPage-1)*lh+pInfo->GetMinPage();
	int now=current;
	if ((int)pInfo->GetToPage()<current)
		pInfo->m_nCurPage=pInfo->GetMaxPage()+1;
	char numBuf[5];
	for (int x=current;(x<now+lpp) &&(x<=(int)pInfo->GetToPage());x++)
	{
		wsprintf(numBuf,"%03i   %s", x);
		CString temp = CString(numBuf) + pDoc->m_s[x].m_Symbol;
		//CSize textSize= pDC->GetTextExtent(temp);
		pDC->TextOut(200,size*(pDoc->m_nLanguages+1)*(x-now),temp);
		for (int y=0;y<pDoc->m_nLanguages;y++)
			pDC->TextOut(400,size*(pDoc->m_nLanguages+1)*(x-now)+size*(y+1),pDoc->m_s[x].m_Strings[y]);

	}

	current=x;
	if ((int)pInfo->GetToPage()<current)
		pDC->EndDoc();
//	CListView::OnPrint(pDC, pInfo);
	
}
