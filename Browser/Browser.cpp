
// Browser.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Browser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrowserApp

BEGIN_MESSAGE_MAP(CBrowserApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBrowserApp ����

CBrowserApp::CBrowserApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBrowserApp ����

CBrowserApp theApp;


// CBrowserApp ��ʼ��

BOOL CBrowserApp::InitInstance()
{
	CWinApp::InitInstance();
	CMainFrame* pMainFrame = new CMainFrame();
	pMainFrame->CreateEx(0, _T("MAINFRAME"), _T("ƤƤ�������"), WS_POPUPWINDOW | 
		WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
	m_pMainWnd = pMainFrame;
	pMainFrame->CenterWindow();
	pMainFrame->ShowWindow(TRUE);
	pMainFrame->UpdateWindow();
	return TRUE;
}