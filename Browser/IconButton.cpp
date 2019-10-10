#include "stdafx.h"
#include "Browser.h"
#include "IconButton.h"

IMPLEMENT_DYNAMIC(CIconButton, CWnd)

CIconButton::CIconButton()
{
	m_hIcon = NULL;
}

CIconButton::~CIconButton()
{
}


BEGIN_MESSAGE_MAP(CIconButton, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


BOOL CIconButton::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("ICONBUTTON"), lpszWindowName, dwStyle, rect, pParentWnd, nID);
}


BOOL CIconButton::PreCreateWindow(CREATESTRUCT& cs)
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

void CIconButton::SetIcon(UINT uIDResource)
{
	m_hIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(uIDResource));
	Invalidate();
}

void CIconButton::OnPaint()
{
	CPaintDC dc(this);
	if(m_hIcon == NULL)
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	::DrawIconEx(dc.m_hDC, 0, 0, m_hIcon, rcClient.Width(), rcClient.Height(), 0, NULL, DI_NORMAL);
}

void CIconButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);
	CWnd* pParent = GetParent();
	if(pParent)
	{
		WORD wID = GetDlgCtrlID();
		pParent->SendMessage(WM_COMMAND, MAKEWPARAM(wID, BN_CLICKED), (LPARAM)m_hWnd);
	}
}