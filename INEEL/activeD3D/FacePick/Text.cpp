// text.cpp : implementation of the CText class
//
// Copyright (c)1996 Luhan Software
//
// Used with permission by Stan Trujillo.
//
// Luhan Software
// P.O. Box 2572
// Las Vegas, NM 87701
//

#include <AfxWin.h>
#include <AfxExt.h>
#include "text.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CText

BEGIN_MESSAGE_MAP(CText, CWnd)
	//{{AFX_MSG_MAP(CText)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CText message handlers

CText::CText()
{
  m_TextColor = GetSysColor( COLOR_WINDOWTEXT );
  m_BkColor = GetSysColor( COLOR_WINDOW );
  m_BkMode = OPAQUE;
  m_font = 0;
  m_x = 0, m_y = 0;
}

CText::~CText()
{
  if ( m_font )
    delete m_font;
}

BOOL CText::Create( int x, int y, const CString& text, CWnd* ParentWnd, 
  LPCTSTR FontName /*= 0*/, int FontSize /*= 0*/, 
  UINT style /*= WS_CHILD | WS_VISIBLE*/, 
  UINT ID /*= 0xffff*/ )
{
  m_x = x, m_y = y;
  m_font = new CFont;
  if ( m_font == 0 )
    return FALSE;
  CString ClassName;
  ClassName = AfxRegisterWndClass( CS_HREDRAW | CS_VREDRAW, LoadCursor( NULL, IDC_ARROW ), (HBRUSH)(COLOR_WINDOW+1) );
  BOOL result = CWnd::Create( ClassName, "LuhanTextControl", style, CRect(m_x,m_y,0,0), ParentWnd, ID );
  if ( result )
  {
    m_text = text;
    m_FontName = FontName;
    m_FontSize = FontSize;

    CDC* pDC = GetDC();
    if ( m_FontName != "" )
    {
	    LOGFONT logfont;
	    memset( &logfont, 0, sizeof( logfont ) );
	    logfont.lfHeight = -MulDiv( m_FontSize, GetDeviceCaps( pDC->GetSafeHdc(), LOGPIXELSY ), 72);
	    logfont.lfWeight = FW_NORMAL;
	    lstrcpy( logfont.lfFaceName, m_FontName );
	    if ( m_font->CreateFontIndirect( &logfont ) == FALSE )
        return FALSE;
    }
    FigureSize();
    return TRUE;
  }
  return FALSE;
}

void CText::FigureSize(void)
{
  CDC* pDC = GetDC();
  pDC->SelectObject( m_font );
  SIZE size;
  GetTextExtentPoint32( pDC->GetSafeHdc(), m_text, m_text.GetLength(), &size );
  SetWindowPos( 0, m_x, m_y, size.cx, size.cy, SWP_NOZORDER );
}

void CText::SetText( const CString& text )
{
  m_text = text;
  FigureSize();
  InvalidateRect( NULL );
}

void CText::SetTextColor( COLORREF color )
{
  m_TextColor = color;
  InvalidateRect( NULL );
}

void CText::SetBkColor( COLORREF color )
{
  m_BkColor = color;
  InvalidateRect( NULL );
}

void CText::SetOpaqueMode(void)
{
  m_BkMode = OPAQUE;
  InvalidateRect( NULL );
}

void CText::SetTransparentMode(void)
{
  m_BkMode = TRANSPARENT;
  InvalidateRect( NULL );
}

BOOL CText::SetFont( const CString& name, int height, int weight )
{
  delete m_font;
  m_font = new CFont;
  if ( m_font == 0 )
    return FALSE;

  m_FontName = name;
  m_FontSize = height/10;

  CDC* pDC = GetDC();
	LOGFONT logfont;
	memset( &logfont, 0, sizeof( logfont ) );
	logfont.lfHeight = -MulDiv( m_FontSize, GetDeviceCaps( pDC->GetSafeHdc(), LOGPIXELSY ), 72);
	logfont.lfWeight = weight;
	lstrcpy( logfont.lfFaceName, m_FontName );
  if ( m_font->CreateFontIndirect( &logfont ) == FALSE )
    return FALSE;
  FigureSize();
  InvalidateRect( NULL );
  return TRUE;
}

void CText::SetLocation( int x, int y )
{
  m_x = x, m_y = y;
  FigureSize();
  InvalidateRect( NULL );
}

void CText::OnPaint() 
{
	CPaintDC dc(this);
  dc.SelectObject( m_font );
  dc.SetBkMode( m_BkMode );
  dc.SetTextColor( m_TextColor );
  dc.SetBkColor( m_BkColor );
  dc.TextOut( 0, 0, m_text );
	// Do not call CStatic::OnPaint() for painting messages
}
