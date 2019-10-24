// CntrItem.h : interface of the CSDIOleDropCntrItem class
//

#if !defined(AFX_CNTRITEM_H__41A55BB0_16B3_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_CNTRITEM_H__41A55BB0_16B3_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSDIOleDropDoc;
class CSDIOleDropView;

class CSDIOleDropCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CSDIOleDropCntrItem)

// Constructors
public:
	CSDIOleDropCntrItem(CSDIOleDropDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CSDIOleDropDoc* GetDocument()
		{ return (CSDIOleDropDoc*)COleClientItem::GetDocument(); }
	CSDIOleDropView* GetActiveView()
		{ return (CSDIOleDropView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIOleDropCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CSDIOleDropCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__41A55BB0_16B3_11D4_B398_00A0CC548BE4__INCLUDED_)
