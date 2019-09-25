#include "StdAfx.h"
#include "CaptionRightPanel.h"
#include "resource.h"
#include "MainFrame.h"

CCaptionRightPanel::CCaptionRightPanel(void)
{
}


CCaptionRightPanel::~CCaptionRightPanel(void)
{
}
BEGIN_MESSAGE_MAP(CCaptionRightPanel, CPanel)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CCaptionRightPanel::OnPaint()
{
	if(m_imgCaption.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	CPaintDC dc(this); 
	m_imgCaption.Draw(dc.m_hDC, rcClient);
}


int CCaptionRightPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_imgCaption.IsNull())
		return 0;
	m_imgCaption.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_CAPTION);
	return 0;
}


void CCaptionRightPanel::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}

	CPanel::OnLButtonDblClk(nFlags, point);
}


void CCaptionRightPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_NCLBUTTONDBLCLK, HTCAPTION, 0);
	}
	CPanel::OnLButtonDown(nFlags, point);
}
