#include "StdAfx.h"
#include "TabManager.h"
#define IDC_TABBUTTON_NEW 10001
#define IDC_TABBUTTON_FULL_SCREEN 10002
#define IDC_TABBUTTON_LEFT 10003
#define IDC_TABBUTTON_RIGHT 10004
#define IDC_TABBUTTON_CLOSE 10005


CTabManager::CTabManager(void)
{
	m_imgTabButtonNew.m_hWnd = NULL;
	m_imgTabButtonFullScreen.m_hWnd = NULL;
	m_imgTabButtonLeft.m_hWnd = NULL;
	m_imgTabButtonRight.m_hWnd = NULL;
	m_imgTabButtonClose.m_hWnd = NULL;
}


CTabManager::~CTabManager(void)
{
}
BEGIN_MESSAGE_MAP(CTabManager, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	// ON_BN_CLICKED(IDC_TABBUTTON_NEW, OnTabButtonNew)
END_MESSAGE_MAP()


int CTabManager::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(m_imgTabPanel.IsNull())
	{
		m_imgTabPanel.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_TAB_BAR);
	}
	if(m_imgTabButtonNew.m_hWnd == NULL)
	{
		m_imgTabButtonNew.Create(_T("TABBUTTONNEW"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 20, 29), this, IDC_TABBUTTON_NEW);
		m_imgTabButtonNew.SetImage(IDB_BITMAP_TABBUTTON_NEW);
	}
	if(m_imgTabButtonFullScreen.m_hWnd == NULL)
	{
		m_imgTabButtonFullScreen.Create(_T("TABBUTTONFULLSCREEN"), WS_CHILD | WS_VISIBLE, CRect(20, 0, 38, 29), this, IDC_TABBUTTON_FULL_SCREEN);
		m_imgTabButtonFullScreen.SetImage(IDB_BITMAP_TABBUTTON_FULL_SCREEN);
	}
	if(m_imgTabButtonLeft.m_hWnd == NULL)
	{
		m_imgTabButtonLeft.Create(_T("TABBUTTONLEFT"), WS_CHILD | WS_VISIBLE, CRect(38, 0, 56, 29), this, IDC_TABBUTTON_LEFT);
		m_imgTabButtonLeft.SetImage(IDB_BITMAP_TABBUTTON_LEFT);
	}
	if(m_imgTabButtonRight.m_hWnd == NULL)
	{
		m_imgTabButtonRight.Create(_T("TABBUTTONRIGHT"), WS_CHILD | WS_VISIBLE, CRect(56, 0, 74, 29), this, IDC_TABBUTTON_RIGHT);
		m_imgTabButtonRight.SetImage(IDB_BITMAP_TABBUTTON_RIGHT);
	}
	if(m_imgTabButtonClose.m_hWnd == NULL)
	{
		m_imgTabButtonClose.Create(_T("TABBUTTONCLOSE"), WS_CHILD | WS_VISIBLE, CRect(74, 0, 92, 29), this, IDC_TABBUTTON_CLOSE);
		m_imgTabButtonClose.SetImage(IDB_BITMAP_TABBUTTON_CLOSE);
	}
	return 0;
}


void CTabManager::OnPaint()
{
	CPaintDC dc(this); 
	if(m_imgTabPanel.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_imgTabPanel.Draw(dc.m_hDC, rcClient);
}
