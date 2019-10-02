#include "stdafx.h"
#include "Browser.h"
#include "ImageButton.h"

IMPLEMENT_DYNAMIC(CImageButton, CWnd)

CImageButton::CImageButton()
{
	m_bIsHover	= FALSE;
	m_bIsDown	= FALSE;
}

CImageButton::~CImageButton()
{
}


BEGIN_MESSAGE_MAP(CImageButton, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CImageButton::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("IMAGEBUTTON"), lpszWindowName, dwStyle, rect, pParentWnd, nID);
}


BOOL CImageButton::PreCreateWindow(CREATESTRUCT& cs)
{
	HINSTANCE hInstance = AfxGetInstanceHandle();
	ASSERT(hInstance);
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	BOOL bRet = GetClassInfoEx(hInstance, cs.lpszClass, &wcex);
	if(bRet)
	{
		return TRUE;
	}
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = AfxWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	// wcex.hIcon = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	// wcex.hIcon = (HICON)theApp->LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcex.hIcon = (HICON)AfxGetApp()->LoadIcon( MAKEINTRESOURCE(IDR_MAINFRAME));
	wcex.hCursor = wcex.hIconSm = (HCURSOR)LoadCursor(NULL,IDC_ARROW);
	// wcex.hCursor = (HCURSOR)theApp->LoadStandardCursor(IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;
	bRet = RegisterClassEx(&wcex);
	return bRet;
}

void CImageButton::SetImage(UINT uIDResource)
{
	if(!m_imgButton.IsNull())
	{
		m_imgButton.Destroy();
	}
	m_imgButton.LoadFromResource(AfxGetInstanceHandle(), uIDResource);
}

void CImageButton::OnPaint()
{
	CPaintDC dc(this);
	if(m_imgButton.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);

	BOOL bIsEnabled = IsWindowEnabled();
	if(!bIsEnabled)
	{
		m_imgButton.Draw(dc.m_hDC, rcClient, CRect(m_imgButton.GetWidth() * 3 / 4, 0, m_imgButton.GetWidth() * 4 / 4, m_imgButton.GetHeight() + 10));
		return ;
	}
	if(m_bIsHover)
	{
		if(m_bIsDown)
		{
			m_imgButton.Draw(dc.m_hDC, rcClient, CRect(m_imgButton.GetWidth() * 2 / 4, 0, m_imgButton.GetWidth() * 3 / 4, m_imgButton.GetHeight()));
		}
		else
		{
			m_imgButton.Draw(dc.m_hDC, rcClient, CRect(m_imgButton.GetWidth() * 1 / 4, 0, m_imgButton.GetWidth() * 2 / 4, m_imgButton.GetHeight()));
		}
	}
	else
	{
		m_imgButton.Draw(dc.m_hDC, rcClient, CRect(m_imgButton.GetWidth() * 0 / 4, 0, m_imgButton.GetWidth() * 1 / 4, m_imgButton.GetHeight()));
	}
}

void CImageButton::OnMouseMove(UINT nFlag, CPoint point)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = 1; // HOVER_DEFAULT改为1, 解决Win10上停留较长时间才切换图片的问题
	TrackMouseEvent(&tme);
	CWnd::OnMouseMove(nFlag, point);
}

LRESULT CImageButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	if(!m_bIsHover)
	{
		m_bIsHover = TRUE;
		Invalidate();
	}
	
	return TRUE;
}

LRESULT CImageButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_bIsHover)
	{
		m_bIsHover = FALSE;
		Invalidate();
	}
	return TRUE;
}

void CImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bIsDown)
	{
		m_bIsDown = TRUE;
		Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);
	if(m_bIsDown)
	{
		m_bIsDown = FALSE;
		Invalidate();
	}
	CWnd* pParent = GetParent();
	if(pParent)
	{
		WORD wID = GetDlgCtrlID();
		pParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_hWnd);
	}
}