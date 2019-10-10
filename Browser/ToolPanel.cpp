#include "StdAfx.h"
#include "ToolPanel.h"
#include "resource.h"
#define IDC_MAIN_TOOL_BAR	10001
#define IDC_ADDRESS_BAR		10002
#define IDC_SEARCH_BAR		10003
CToolPanel::CToolPanel(void)
{
	m_mainToolBar.m_hWnd = NULL;
	m_addressBar.m_hWnd = NULL;
	m_searchBar.m_hWnd = NULL;
}


CToolPanel::~CToolPanel(void)
{
}
BEGIN_MESSAGE_MAP(CToolPanel, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CToolPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_imgTool.IsNull())
		return 0;
	m_imgTool.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_TOOLBAR);
	if(m_mainToolBar.m_hWnd)
		return 0;
	if(m_addressBar.m_hWnd)
		return 0;
	if(m_searchBar.m_hWnd)
		return 0;
	m_mainToolBar.Create(_T("MAINTOOLBAR"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 260, 51), this, IDC_MAIN_TOOL_BAR);
	m_addressBar.Create(_T("ADDRESSBAR"), WS_CHILD | WS_VISIBLE, CRect(260, 0, lpCreateStruct->cx - 200, 51), this, IDC_ADDRESS_BAR);
	m_searchBar.Create(_T("SEARCHBAR"), WS_CHILD | WS_VISIBLE, CRect(lpCreateStruct->cx - 200, 0, lpCreateStruct->cx, 51), this, IDC_SEARCH_BAR);
	return 0;
}


void CToolPanel::OnPaint()
{
	CPaintDC dc(this);
	if(m_imgTool.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_imgTool.Draw(dc.m_hDC, rcClient);
}


void CToolPanel::OnSize(UINT nType, int cx, int cy)
{
	CPanel::OnSize(nType, cx, cy);
	if(m_addressBar.m_hWnd == NULL)
		return ;
	if(m_searchBar.m_hWnd == NULL)
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_addressBar.MoveWindow(CRect(260, 0, rcClient.Width() - 200, 51));
	m_searchBar.MoveWindow(CRect(rcClient.Width() - 200, 0, rcClient.Width(), 51));
}
