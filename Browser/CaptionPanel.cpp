#include "StdAfx.h"
#include "CaptionPanel.h"


CCaptionPanel::CCaptionPanel(void)
{
	m_captionLeftPanel.m_hWnd		= NULL;
	m_captionCenterPanel.m_hWnd		= NULL;
	m_captionRightPanel.m_hWnd		= NULL;
}


CCaptionPanel::~CCaptionPanel(void)
{
}
BEGIN_MESSAGE_MAP(CCaptionPanel, CPanel)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CCaptionPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPanel::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(m_captionLeftPanel.m_hWnd)
		return 0;
	if(m_captionCenterPanel.m_hWnd)
		return 0;
	if(m_captionRightPanel.m_hWnd)
		return 0;
	m_captionLeftPanel.Create(_T("CaptionLeftPanel"), WS_CHILD | WS_VISIBLE, CRect(0, 0, lpCreateStruct->cx - 290, lpCreateStruct->cy), this, 10001);
	m_captionCenterPanel.Create(_T("CaptionCenterPanel"), WS_CHILD | WS_VISIBLE, CRect(lpCreateStruct->cx - 290, 0, lpCreateStruct->cx - 50, lpCreateStruct->cy), this, 10002);
	m_captionRightPanel.Create(_T("CaptionRightPanel"), WS_CHILD | WS_VISIBLE, CRect(lpCreateStruct->cx - 50, 0, lpCreateStruct->cx, lpCreateStruct->cy), this, 10003);
	return 0;
}


void CCaptionPanel::OnSize(UINT nType, int cx, int cy)
{
	CPanel::OnSize(nType, cx, cy);
	if(m_captionLeftPanel.m_hWnd == NULL)
		return ;
	if(m_captionCenterPanel.m_hWnd == NULL)
		return ;
	if(m_captionRightPanel.m_hWnd == NULL)
		return ;
	CRect rcClient;
	GetWindowRect(rcClient);
	m_captionLeftPanel.MoveWindow(CRect(0, 0, rcClient.Width() - 290, rcClient.Height()));
	m_captionCenterPanel.MoveWindow(CRect(rcClient.Width() - 290, 0, rcClient.Width() - 50, rcClient.Height()));
	m_captionRightPanel.MoveWindow(CRect(rcClient.Width() - 50, 0, rcClient.Width(), rcClient.Height()));
}
