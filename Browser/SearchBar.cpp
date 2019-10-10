#include "StdAfx.h"
#include "SearchBar.h"
#include "MenuEx.h"
#define IDC_SEARCH_GO 10001
#define IDC_EDIT_SEARCH 10002
#define IDC_BUTTON_ICON 10003
CSearchBar::CSearchBar(void)
{
	m_btnSearch.m_hWnd = NULL;
	m_btnIcon.m_hWnd = NULL;
	m_editSearch.m_hWnd = NULL;
}


CSearchBar::~CSearchBar(void)
{
}
BEGIN_MESSAGE_MAP(CSearchBar, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ICON, OnSelIconButton)
END_MESSAGE_MAP()


int CSearchBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(m_imgTool.IsNull())
	{
		m_imgTool.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_TOOLBAR);
	}
	if(m_imgBand.IsNull())
	{
		m_imgBand.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_COMBOBOX);
	}
	if(m_btnSearch.m_hWnd)
		return 0;
	CRect rcClient;
	GetClientRect(rcClient);
	m_btnSearch.Create(_T("SEARCH"), WS_CHILD | WS_VISIBLE, CRect(rcClient.Width() - 40, 11, rcClient.Width() - 1, 39), this, IDC_SEARCH_GO);
	m_btnSearch.SetImage(IDB_BITMAP_SEARCH_GO);
	if(m_editSearch.m_hWnd)
		return 0;
	m_editSearch.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, CRect(30, 16, rcClient.Width() - 41, 36), this, IDC_EDIT_SEARCH);
	if(m_btnIcon.m_hWnd)
		return 0;
	m_btnIcon.Create(_T("ICON"), WS_CHILD | WS_VISIBLE, CRect(7, 16, 26, 35), this, IDC_BUTTON_ICON);
	m_btnIcon.SetIcon(IDI_ICON_BAIDU);
	return 0;
}


void CSearchBar::OnPaint()
{
	CPaintDC dc(this); 
	if(m_imgTool.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_imgTool.Draw(dc.m_hDC, rcClient);
	if(m_imgBand.IsNull())
		return ;
	CRect rcLeft;
	rcLeft.left = 0;
	rcLeft.right = 10;
	rcLeft.top = 11;
	rcLeft.bottom = 39;
	m_imgBand.Draw(dc.m_hDC, rcLeft, CRect(0, 0, 10, m_imgBand.GetHeight()));

	CRect rcRight = rcLeft;
	rcRight.left = rcLeft.right;
	rcRight.right = rcClient.right - 40;
	m_imgBand.Draw(dc.m_hDC, rcRight, CRect(10, 0, m_imgBand.GetWidth(), m_imgBand.GetHeight()));
}

void CSearchBar::OnSelIconButton()
{
	CMenuEx menu;
	BOOL bRet = menu.CreatePopupMenu();
	ASSERT(bRet);
	MENUITEM mi1;
	mi1.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_BAIDU));
	mi1.strText = _T("°Ù¶È");
	MENUITEM mi2;
	mi2.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_GOOGLE));
	mi2.strText = _T("¹È¸è");
	menu.AppendMenu(MF_OWNERDRAW | MF_BYCOMMAND, 10001, (LPCTSTR)&mi1);
	menu.AppendMenu(MF_OWNERDRAW | MF_BYCOMMAND, 10002, (LPCTSTR)&mi2);
	CPoint pt;
	GetCursorPos(&pt);
	int nID = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, pt.x, pt.y, this);
	switch(nID)
	{
	case 0:
		return ;
	case 10001:
		if(m_btnIcon.m_hWnd)
		{
			m_btnIcon.SetIcon(IDI_ICON_BAIDU);
		}
		break;
	case 10002:
		if(m_btnIcon.m_hWnd)
		{
			m_btnIcon.SetIcon(IDI_ICON_GOOGLE);
		}
		break;
	default:
		break;
	}
}