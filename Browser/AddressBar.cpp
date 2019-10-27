#include "StdAfx.h"
#include "AddressBar.h"
#define IDC_ADDRESS_COMBOBOX 10001
#define IDC_BTN_GO	10002

CAddressBar::CAddressBar(void)
{
	m_btnGo.m_hWnd = NULL;
	m_addressComboBox.m_hWnd = NULL;
}


CAddressBar::~CAddressBar(void)
{
}
BEGIN_MESSAGE_MAP(CAddressBar, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CAddressBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_imgTool.IsNull())
		return 0;
	m_imgTool.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_TOOLBAR);
	if(m_btnGo.m_hWnd)
		return 0;
	if(m_addressComboBox.m_hWnd)
		return 0;
	CRect rcClient;
	GetClientRect(rcClient);
	m_addressComboBox.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS | CBS_OWNERDRAWVARIABLE,
		CRect(20, 11, rcClient.Width() - 22, 200), this, IDC_ADDRESS_COMBOBOX);
	for(int i = 0; i < 100; i++)
	{
		CString strItem;
		strItem.Format(_T("%d"), i);
		HICON hIcon = LoadIcon(NULL, IDI_INFORMATION);
		m_addressComboBox.AddString(strItem, hIcon);
	}
	m_btnGo.Create(_T(""), WS_VISIBLE | WS_CHILD, CRect(rcClient.Width() - 22, 11, rcClient.Width(), 39), this, IDC_ADDRESS_COMBOBOX);
	m_btnGo.SetImage(IDB_BITMAP_COMBOBOX_GO);
	return 0;
}


void CAddressBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(m_imgTool.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_imgTool.Draw(dc.m_hDC, rcClient);
}




void CAddressBar::OnSize(UINT nType, int cx, int cy)
{
	CPanel::OnSize(nType, cx, cy);
	if(m_btnGo.m_hWnd == NULL)
		return ;
	if(m_addressComboBox.m_hWnd == NULL)
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_addressComboBox.MoveWindow(CRect(20, 11, rcClient.Width() - 22, 200));
	m_btnGo.MoveWindow(CRect(rcClient.Width() - 22, 11, rcClient.Width(), 39));
}

