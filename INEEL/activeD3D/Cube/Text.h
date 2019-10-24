// text.h : interface of the CText class
//
// Copyright (c)1996 Luhan Software
//
// Used with permission by Stan Trujillo.
//
// Luhan Software
// P.O. Box 2572
// Las Vegas, NM 87701
//

/////////////////////////////////////////////////////////////////////////////

#ifndef __CText_h
#define __CText_h

class CText : public CWnd
{
public:
  CText();
  ~CText();
  BOOL Create( int x, int y, const CString& text, CWnd* ParentWnd, 
    LPCTSTR FontName = 0, int FontSize = 0, 
    UINT style = WS_CHILD | WS_VISIBLE, UINT ID = 0xffff );
  void SetText( const CString& text );
  void SetTextColor( COLORREF color );
  void SetBkColor( COLORREF color );
  void SetOpaqueMode(void);
  void SetTransparentMode(void);
  BOOL SetFont( const CString& name, int height, int weight );
  void SetLocation( int x, int y );
	//{{AFX_VIRTUAL(CText)
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CText)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  void FigureSize(void);
public:
  COLORREF m_TextColor;
  COLORREF m_BkColor;
  int m_BkMode;
  CString m_text;
  CString m_FontName;
  int m_FontSize;
  CFont* m_font;
  int m_x, m_y;
};

#endif //__CText_h

/////////////////////////////////////////////////////////////////////////////
