#include "stdafx.h"
#include "Browser.h"
#include "TabButton.h"

IMPLEMENT_DYNAMIC(CTabButton, CWnd)

CTabButton::CTabButton()
{
	m_bIsSelected	= FALSE;
}

CTabButton::~CTabButton()
{
}


BEGIN_MESSAGE_MAP(CTabButton, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CTabButton::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("IMAGEBUTTON"), lpszWindowName, dwStyle, rect, pParentWnd, nID);
}


BOOL CTabButton::PreCreateWindow(CREATESTRUCT& cs)
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

void CTabButton::SetImage(UINT uIDResource)
{
	if(!m_imgButton.IsNull())
	{
		m_imgButton.Destroy();
	}
	m_imgButton.LoadFromResource(AfxGetInstanceHandle(), uIDResource);
	Invalidate();
}

void CTabButton::OnPaint()
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
	if(m_bIsSelected)
	{
		CRect rcItemLeft = rcClient;
		rcItemLeft.right = m_imgButton.GetWidth() / 8 - 1;
		m_imgButton.Draw(dc.m_hDC, rcItemLeft, CRect(m_imgButton.GetWidth() * 1 / 2, 0, m_imgButton.GetWidth() * 5 / 8 - 1, m_imgButton.GetHeight()));
		CRect rcItemCenter = rcClient;
		rcItemCenter.left = m_imgButton.GetWidth() / 8 - 1;
		rcItemCenter.right = rcClient.Width() - (m_imgButton.GetWidth() / 8 - 1);
		m_imgButton.Draw(dc.m_hDC, rcItemCenter, CRect(m_imgButton.GetWidth() * 5 / 8 - 1, 0, m_imgButton.GetWidth() * 5 / 8, m_imgButton.GetHeight()));
		CRect rcItemRight = rcClient;
		rcItemRight.left = rcClient.Width() - (m_imgButton.GetWidth() / 8 - 1);
		m_imgButton.Draw(dc.m_hDC, rcItemRight, CRect(m_imgButton.GetWidth() * 5/ 8 + 1, 0, m_imgButton.GetWidth() * 3 / 4, m_imgButton.GetHeight()));
	}
	else
	{
		CRect rcItemLeft = rcClient;
		rcItemLeft.right = m_imgButton.GetWidth() / 8 - 1;
		m_imgButton.Draw(dc.m_hDC, rcItemLeft, CRect(0, 0, m_imgButton.GetWidth() / 8 - 1, m_imgButton.GetHeight()));
		CRect rcItemCenter = rcClient;
		rcItemCenter.left = m_imgButton.GetWidth() / 8 - 1;
		rcItemCenter.right = rcClient.Width() - (m_imgButton.GetWidth() / 8 - 1);
		m_imgButton.Draw(dc.m_hDC, rcItemCenter, CRect(m_imgButton.GetWidth() / 8 - 1, 0, m_imgButton.GetWidth() / 8, m_imgButton.GetHeight()));
		CRect rcItemRight = rcClient;
		rcItemRight.left = rcClient.Width() - (m_imgButton.GetWidth() / 8 - 1);
		m_imgButton.Draw(dc.m_hDC, rcItemRight, CRect(m_imgButton.GetWidth() / 4 - (m_imgButton.GetWidth() / 8 - 1), 0, m_imgButton.GetWidth() * 1 / 4, m_imgButton.GetHeight()));
	}
	int nOldBkMode = dc.SetBkMode(TRANSPARENT);
	CString strText;
	GetWindowText(strText);
	if(!strText.IsEmpty())
	{
		dc.DrawText(strText, rcClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_WORD_ELLIPSIS);
	}
	dc.SetBkMode(nOldBkMode);
}

void CTabButton::OnMouseMove(UINT nFlag, CPoint point)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = 1; // HOVER_DEFAULT改为1, 解决Win10上停留较长时间才切换图片的问题
	TrackMouseEvent(&tme);
	CWnd::OnMouseMove(nFlag, point);
}

LRESULT CTabButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CTabButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

void CTabButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bIsSelected)
	{
		m_bIsSelected = TRUE;
		Invalidate();
	}
	CWnd* pParent = GetParent();
	if(pParent)
	{
		WORD wID = GetDlgCtrlID();
		pParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_hWnd);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CTabButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);
}

void CTabButton::SetSelected(BOOL bIsSelected)
{
	if(bIsSelected != m_bIsSelected)
	{
		m_bIsSelected = bIsSelected;
		Invalidate(TRUE);
	}
}