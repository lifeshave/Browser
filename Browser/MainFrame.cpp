#include "stdafx.h"
#include "Resource.h"
#include "Browser.h"
#include "MainFrame.h"
#define IDC_CAPTIONPANEL 10001
#define IDC_TOOLPANEL 10002

IMPLEMENT_DYNAMIC(CMainFrame, CWnd)

CMainFrame::CMainFrame()
{
	m_captionPanel.m_hWnd = NULL;
	m_toolPanel.m_hWnd = NULL;
}

CMainFrame::~CMainFrame()
{
}

BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	ON_WM_GETMINMAXINFO()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCACTIVATE()
END_MESSAGE_MAP()

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
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


void CMainFrame::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	delete this;
	CWnd::PostNcDestroy();
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 700;
	lpMMI->ptMinTrackSize.y = 700 * 0.618;
	lpMMI->ptMaxPosition.x = 0;
	lpMMI->ptMaxPosition.y = 0;
	CRect rcWorkArea;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	lpMMI->ptMaxSize.x = lpMMI->ptMaxTrackSize.x = rcWorkArea.Width();
	lpMMI->ptMaxSize.y = lpMMI->ptMaxTrackSize.y = rcWorkArea.Height();
	CWnd::OnGetMinMaxInfo(lpMMI);
}


void CMainFrame::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	int nCxBorder = ::GetSystemMetrics(SM_CXSIZEFRAME);
	int nCyBorder = ::GetSystemMetrics(SM_CYSIZEFRAME);
	lpncsp->rgrc[0].left -= nCxBorder;
	lpncsp->rgrc[0].right += nCxBorder;
	lpncsp->rgrc[0].top -= nCyBorder;
	lpncsp->rgrc[0].bottom += nCyBorder;

	lpncsp->rgrc[0].left += 2;
	lpncsp->rgrc[0].right -= 2;
	lpncsp->rgrc[0].top += 2;
	lpncsp->rgrc[0].bottom -= 2;
	CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}


void CMainFrame::OnNcPaint()
{
	if(m_imgBorder.IsNull())
		return ;
	CWindowDC dc(this);
	CRect rcWnd;
	GetWindowRect(&rcWnd);
	m_imgBorder.Draw(dc.m_hDC, 0, 0, rcWnd.Width(), 2);
	m_imgBorder.Draw(dc.m_hDC, 0, 0, 2, rcWnd.Width());
	m_imgBorder.Draw(dc.m_hDC, rcWnd.right - 2, 0, rcWnd.Height(), rcWnd.Width());
	m_imgBorder.Draw(dc.m_hDC, 0, rcWnd.bottom - 2, rcWnd.Height(), rcWnd.Width());
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_imgBorder.IsNull())
		return 0;
	if(m_captionPanel.m_hWnd)
		return 0;
	if(m_toolPanel.m_hWnd)
		return 0;
	m_imgBorder.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_BACKGROUND);
	m_captionPanel.Create(_T("CAPTIONPANEL"), WS_CHILD | WS_VISIBLE, CRect(0, 0, lpCreateStruct->cx, 27), this, IDC_CAPTIONPANEL);
	m_toolPanel.Create(_T("TOOLPANEL"), WS_CHILD | WS_VISIBLE, CRect(0, 0, lpCreateStruct->cx, 27), this, IDC_TOOLPANEL);
	// 边框阴影问题
	HINSTANCE hInst = LoadLibrary(_T("UxTheme.dll"));
	if(hInst)
	{
		typedef HRESULT (WINAPI *PFUN_SetWindowTheme)(HWND, LPCTSTR, LPCTSTR);
		PFUN_SetWindowTheme pFun = (PFUN_SetWindowTheme)GetProcAddress(hInst, "SetWindowTheme");
		if(pFun)
		{
			pFun(m_hWnd, _T(""), _T(""));
		}
		FreeLibrary(hInst);
	}
	hInst = LoadLibrary(_T("dwmapi.dll"));
	if(hInst)
	{
		typedef HRESULT (WINAPI *TmpFun)(HWND, DWORD, LPCVOID, DWORD);
		TmpFun pDwnSetWindowAttrbuteEx = (TmpFun)GetProcAddress(hInst, "DwnSetWindowAttrbute");
		if(pDwnSetWindowAttrbuteEx)
		{
			DWORD dwAttr = 1;
			pDwnSetWindowAttrbuteEx(GetSafeHwnd(), 2, &dwAttr, 4);
		}
		FreeLibrary(hInst);
	}
	return 0;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	if(m_captionPanel.m_hWnd == NULL)
		return ;
	if(m_toolPanel.m_hWnd == NULL)
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	CRect rcCaptionPanel = rcClient;
	rcCaptionPanel.bottom = 27;
	m_captionPanel.MoveWindow(rcCaptionPanel);
	CRect rcToolPanel = rcClient;
	rcToolPanel.top = 27;
	rcToolPanel.bottom = 78;
	m_toolPanel.MoveWindow(rcToolPanel);
}


BOOL CMainFrame::OnNcActivate(BOOL bActive)
{
	BOOL bRet = CWnd::OnNcActivate(bActive);
	SendMessage(WM_NCPAINT, 0, 0);
	Invalidate();
	return bRet;
}
