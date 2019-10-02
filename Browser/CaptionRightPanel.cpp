#include "StdAfx.h"
#include "CaptionRightPanel.h"
#include "resource.h"
#include "MainFrame.h"
#define IDC_MIN_BTN 10001
#define IDC_MAX_BTN 10002
#define IDC_CLOSE_BTN 10003

CCaptionRightPanel::CCaptionRightPanel(void)
{
	m_imgMinBtn.m_hWnd = NULL;
	m_imgMaxBtn.m_hWnd = NULL;
	m_imgCloseBtn.m_hWnd = NULL;
}


CCaptionRightPanel::~CCaptionRightPanel(void)
{
}
BEGIN_MESSAGE_MAP(CCaptionRightPanel, CPanel)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MIN_BTN, OnClickedMinBtn)
	ON_BN_CLICKED(IDC_MAX_BTN, OnClickedMaxBtn)
	ON_BN_CLICKED(IDC_CLOSE_BTN, OnClickedCloseBtn)
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
	if(m_imgMinBtn.m_hWnd)
		return 0;
	if(m_imgMaxBtn.m_hWnd)
		return 0;
	if(m_imgCloseBtn.m_hWnd)
		return 0;

	m_imgCaption.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_CAPTION);
	m_imgMinBtn.Create(_T(""), WS_CHILD | WS_VISIBLE, CRect(0, 0, 31, 27), this, IDC_MIN_BTN);
	m_imgMinBtn.SetImage(IDB_BITMAP_MIN_BTN);
	m_imgMaxBtn.Create(_T(""), WS_CHILD | WS_VISIBLE, CRect(31, 0, 63, 27), this, IDC_MAX_BTN);
	m_imgMaxBtn.SetImage(IDB_BITMAP_MAX_BTN);
	m_imgCloseBtn.Create(_T(""), WS_CHILD | WS_VISIBLE, CRect(63, 0, 103, 27), this, IDC_CLOSE_BTN);
	m_imgCloseBtn.SetImage(IDB_BITMAP_CLOSE_BTN);
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

void CCaptionRightPanel::OnClickedMinBtn()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
}

void CCaptionRightPanel::OnClickedMaxBtn()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if(pMainFrame)
	{
		if(pMainFrame->IsZoomed())
		{
			pMainFrame->SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else
		{
			pMainFrame->SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		
	}
}

void CCaptionRightPanel::OnClickedCloseBtn()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if(pMainFrame)
	{
		pMainFrame->SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
	}
}