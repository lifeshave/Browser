#include "StdAfx.h"
#include "CaptionCenterPanel.h"
#include "resource.h"
#include "MainFrame.h"

CCaptionCenterPanel::CCaptionCenterPanel(void)
{
}


CCaptionCenterPanel::~CCaptionCenterPanel(void)
{
}
BEGIN_MESSAGE_MAP(CCaptionCenterPanel, CPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


int CCaptionCenterPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_imgCaption.IsNull())
		return 0;
	m_imgCaption.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_CAPTION);
	return 0;
}


void CCaptionCenterPanel::OnPaint()
{
	if(m_imgCaption.IsNull())
		return ;
	CRect rcClient;
	GetClientRect(rcClient);
	CPaintDC dc(this); 
	m_imgCaption.Draw(dc.m_hDC, rcClient);
}


void CCaptionCenterPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}
	CPanel::OnLButtonDown(nFlags, point);
}


void CCaptionCenterPanel::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_NCLBUTTONDBLCLK, HTCAPTION, 0);
	}

	CPanel::OnLButtonDblClk(nFlags, point);
}
