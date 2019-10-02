#include "StdAfx.h"
#include "MainToolBar.h"
#define IDC_BACKWARD 10001
#define IDC_FORWARD 10002
#define IDC_STOP 10003
#define IDC_REFRESH 10004
#define IDC_HOME 10005
#define IDC_RESTORE 10006
#define IDC_FAVORITE 10007

CMainToolBar::CMainToolBar(void)
{
	m_btnBackward.m_hWnd = NULL;
	m_btnForward.m_hWnd = NULL;
	m_btnStop.m_hWnd = NULL;
	m_btnRefresh.m_hWnd = NULL;
	m_btnHome.m_hWnd = NULL;
	m_btnRestore.m_hWnd = NULL;
	m_btnFavorite.m_hWnd = NULL;
}


CMainToolBar::~CMainToolBar(void)
{
}
BEGIN_MESSAGE_MAP(CMainToolBar, CPanel)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CMainToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(m_btnBackward.m_hWnd)
		return 0;
	if(m_btnForward.m_hWnd)
		return 0;
	if(m_btnStop.m_hWnd)
		return 0;
	if(m_btnRefresh.m_hWnd)
		return 0;
	if(m_btnHome.m_hWnd)
		return 0;
	if(m_btnRestore.m_hWnd)
		return 0;
	if(m_btnFavorite.m_hWnd)
		return 0;
	m_btnBackward.Create(_T("BACKWORD"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 40, 51), this, IDC_BACKWARD);
	m_btnBackward.SetImage(IDB_BITMAP_BACKWARD);
	m_btnForward.Create(_T("FORWORD"), WS_CHILD | WS_VISIBLE, CRect(40, 0, 78, 51), this, IDC_FORWARD);
	m_btnForward.SetImage(IDB_BITMAP_FORWARD);
	m_btnStop.Create(_T("STOP"), WS_CHILD | WS_VISIBLE, CRect(78, 0, 117, 51), this, IDC_STOP);
	m_btnStop.SetImage(IDB_BITMAP_STOP);
	m_btnRefresh.Create(_T("REFRESH"), WS_CHILD | WS_VISIBLE, CRect(117, 0, 155, 51), this, IDC_REFRESH);
	m_btnRefresh.SetImage(IDB_BITMAP_REFRESH);
	m_btnHome.Create(_T("HOME"), WS_CHILD | WS_VISIBLE, CRect(155, 0, 187, 51), this, IDC_HOME);
	m_btnHome.SetImage(IDB_BITMAP_HOME_PAGE);
	m_btnRestore.Create(_T("RESTORE"), WS_CHILD | WS_VISIBLE, CRect(187, 0, 224, 51), this, IDC_RESTORE);
	m_btnRestore.SetImage(IDB_BITMAP_RESTORE);
	m_btnFavorite.Create(_T("FAVORITE"), WS_CHILD | WS_VISIBLE, CRect(224, 0, 260, 51), this, IDC_FAVORITE);
	m_btnFavorite.SetImage(IDB_BITMAP_FAVORITE);
	return 0;
}
