#include "StdAfx.h"
#include "TabCtrlEx.h"
#define IDC_TAB_BUTTON 10001

CTabCtrlEx::CTabCtrlEx(void)
{
}


CTabCtrlEx::~CTabCtrlEx(void)
{
	int nCount = m_arrTabButton.GetSize();
	if(nCount == 0)
	{
		return ;
	}
	for(int i = 0; i < nCount; i++)
	{
		CTabButton* pTabButton = m_arrTabButton.GetAt(i);
		delete pTabButton;
		pTabButton = NULL;
	}
	m_arrTabButton.RemoveAll();
}
BEGIN_MESSAGE_MAP(CTabCtrlEx, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


int CTabCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(m_imgTabPanel.IsNull())
	{
		m_imgTabPanel.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_TAB_BAR);
	}

	return 0;
}


void CTabCtrlEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if(m_imgTabPanel.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	m_imgTabPanel.Draw(dc.m_hDC, rcClient);
}

int CTabCtrlEx::AddItem(CString strText)
{
	int nIndex = m_arrTabButton.GetSize();
	CRect rcTabButton;
	if(nIndex < 0)
	{
		return -1;
	}
	if(nIndex == 0)
	{
		rcTabButton.left = 0;
		rcTabButton.right = 100;
		rcTabButton.top = 2;
		rcTabButton.bottom = 29;
	}
	else
	{
		CTabButton* pLastTabButton = m_arrTabButton.GetAt(nIndex - 1);
		if(pLastTabButton == NULL)
		{
			return -1;
		}
		if(pLastTabButton->m_hWnd == NULL)
		{
			return -1;
		}
		CRect rcLastTabButton;
		pLastTabButton->GetWindowRect(rcLastTabButton);
		ScreenToClient(rcLastTabButton);
		rcTabButton.left = rcLastTabButton.right + 2;
		rcTabButton.right = rcLastTabButton.right + 100;
		rcTabButton.top = 2;
		rcTabButton.bottom = 29;
	}
	CTabButton* pTabButton = new CTabButton();
	pTabButton->Create(strText, WS_VISIBLE | WS_CHILD, rcTabButton, this, IDC_TAB_BUTTON);
	ASSERT(pTabButton->m_hWnd);
	pTabButton->SetImage(IDB_BITMAP_TAB_BUTTON);
	m_arrTabButton.Add(pTabButton);
	return nIndex;
}

BOOL CTabCtrlEx::OnCommand(WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);
	if(wNotifyCode == BN_CLICKED)
	{
		WORD wId = LOWORD(wParam);
		ASSERT(wId == IDC_TAB_BUTTON);
		HWND hWndButton = (HWND)lParam;
		ASSERT(hWndButton);
		int nCount = m_arrTabButton.GetSize();
		for(int i = 0; i < nCount; i++)
		{
			CTabButton *pTabButton = m_arrTabButton.GetAt(i);
			ASSERT(pTabButton);
			ASSERT(pTabButton->m_hWnd);
			if(pTabButton->m_hWnd == hWndButton)
			{
				pTabButton->SetSelected(TRUE);
			}
			else
			{
				pTabButton->SetSelected(FALSE);
			}
		}
	}
	return CPanel::OnCommand(wParam, lParam);
}
