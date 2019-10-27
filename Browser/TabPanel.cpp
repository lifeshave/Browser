#include "StdAfx.h"
#include "TabPanel.h"
#define IDB_TAB_CTRL 10001
#define IDB_TAB_MANAGER 10002
CTabPanel::CTabPanel(void)
{
	m_wndTabCtrl.m_hWnd = NULL;
	m_tabManager.m_hWnd = NULL;
}


CTabPanel::~CTabPanel(void)
{
}
BEGIN_MESSAGE_MAP(CTabPanel, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CTabPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(m_imgTabPanel.IsNull())
	{
		m_imgTabPanel.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_TAB_BAR);
	}
	if(m_wndTabCtrl.m_hWnd)
		return 0;
	CRect rcClient;
	GetClientRect(rcClient);
	CRect rcTabCtrl = rcClient;
	rcTabCtrl.left = 4;
	rcTabCtrl.right = rcClient.Width() - 100;
	m_wndTabCtrl.Create(_T("TABCTRL"), WS_VISIBLE | WS_CHILD, rcTabCtrl, this, IDB_TAB_CTRL);
	m_wndTabCtrl.AddItem(_T("item1"));
	m_wndTabCtrl.AddItem(_T("item2"));
	m_wndTabCtrl.AddItem(_T("item3"));
	if(m_tabManager.m_hWnd)
		return 0;
	CRect rcTabManager = rcClient;
	rcTabManager.left = rcClient.Width() - 100;
	rcTabManager.right = rcClient.Width();
	m_tabManager.Create(_T("TABMANAGER"), WS_VISIBLE | WS_CHILD, rcTabManager, this, IDB_TAB_MANAGER);
	return 0;
}


void CTabPanel::OnPaint()
{
	CPaintDC dc(this); 
	if(m_imgTabPanel.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_imgTabPanel.Draw(dc.m_hDC, rcClient);
}


void CTabPanel::OnSize(UINT nType, int cx, int cy)
{
	CPanel::OnSize(nType, cx, cy);
	CRect rcClient;
	GetClientRect(rcClient);
	if(m_wndTabCtrl.m_hWnd)
	{
		CRect rcTabCtrl = rcClient;
		rcTabCtrl.left = 4;
		rcTabCtrl.right = rcClient.Width() - 100;
		m_wndTabCtrl.MoveWindow(rcTabCtrl);
	}
	if(m_tabManager.m_hWnd)
	{
		CRect rcTabManager = rcClient;
		rcTabManager.left = rcClient.Width() - 100;
		rcTabManager.right = rcClient.Width();
		m_tabManager.MoveWindow(rcTabManager);
	}
}
