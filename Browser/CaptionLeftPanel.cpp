#include "StdAfx.h"
#include "CaptionLeftPanel.h"
#include "resource.h"
#include "MainFrame.h"

CCaptionLeftPanel::CCaptionLeftPanel(void)
{
}


CCaptionLeftPanel::~CCaptionLeftPanel(void)
{
}
BEGIN_MESSAGE_MAP(CCaptionLeftPanel, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


int CCaptionLeftPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_imgCaption.IsNull())
		return 0;
	m_imgCaption.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_CAPTION);
	return 0;
}


void CCaptionLeftPanel::OnPaint()
{
	if(m_imgCaption.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	CPaintDC dc(this); 
	m_imgCaption.Draw(dc.m_hDC, rcClient);
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		HICON hIcon = (HICON)GetClassLong(pMainFrame->m_hWnd, GCL_HICON);
		if(hIcon)
		{
			DrawIconEx(dc.m_hDC, 4, 4, hIcon, 16, 16, 0, 0, DI_NORMAL);
		}
		CString strText;
		pMainFrame->GetWindowText(strText);
		if(strText.IsEmpty())
			return ;
		CRect rcText = rcClient;
		rcText.left = 27;
		int nOldBkMode = dc.SetBkMode(TRANSPARENT);
		dc.DrawText(strText, rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
		dc.SetBkMode(nOldBkMode);
	}
}


void CCaptionLeftPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}
	CPanel::OnLButtonDown(nFlags, point);
}


void CCaptionLeftPanel::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_NCLBUTTONDBLCLK, HTCAPTION, 0);
	}
	CPanel::OnLButtonDblClk(nFlags, point);
}


void CCaptionLeftPanel::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		CMenu *pSysMenu = pMainFrame->GetSystemMenu(0);
		if(pSysMenu)
		{
			UpdateSystemMenu(pSysMenu);
			int nID = pSysMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, point.x, point.y, pMainFrame);
			if(nID > 0)
			{
				pMainFrame->SendMessage(WM_SYSCOMMAND, nID, 0);
			}
		}
	}
}

void CCaptionLeftPanel::UpdateSystemMenu(CMenu *pMenu)
{
	if(AfxGetMainWnd()->IsIconic())
		return ;
	CString strMenuText;
	if(AfxGetMainWnd()->IsZoomed())
	{
		pMenu->GetMenuString(SC_RESTORE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_RESTORE, MF_STRING | MF_ENABLED, SC_RESTORE, strMenuText);
		pMenu->GetMenuString(SC_MINIMIZE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_MINIMIZE, MF_STRING | MF_ENABLED, SC_MINIMIZE, strMenuText);
		pMenu->GetMenuString(SC_MAXIMIZE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_MAXIMIZE, MF_STRING | MF_GRAYED, SC_MAXIMIZE, strMenuText);
		pMenu->GetMenuString(SC_SIZE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_SIZE, MF_STRING | MF_GRAYED, SC_SIZE, strMenuText);
		pMenu->GetMenuString(SC_MOVE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_MOVE, MF_STRING | MF_GRAYED, SC_MOVE, strMenuText);
	}
	else
	{
		pMenu->GetMenuString(SC_RESTORE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_RESTORE, MF_STRING | MF_GRAYED, SC_RESTORE, strMenuText);
		pMenu->GetMenuString(SC_MINIMIZE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_MINIMIZE, MF_STRING | MF_ENABLED, SC_MINIMIZE, strMenuText);
		pMenu->GetMenuString(SC_MAXIMIZE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_MAXIMIZE, MF_STRING | MF_ENABLED, SC_MAXIMIZE, strMenuText);
		pMenu->GetMenuString(SC_SIZE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_SIZE, MF_STRING | MF_GRAYED, SC_SIZE, strMenuText);
		pMenu->GetMenuString(SC_MOVE, strMenuText, MF_BYCOMMAND);
		pMenu->ModifyMenu(SC_MOVE, MF_STRING | MF_ENABLED, SC_MOVE, strMenuText);
	}
}