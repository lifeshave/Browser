
// Browser.cpp : 定义应用程序的类行为。
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


// CBrowserApp 构造

CBrowserApp::CBrowserApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBrowserApp 对象

CBrowserApp theApp;


// CBrowserApp 初始化

BOOL CBrowserApp::InitInstance()
{
	CWinApp::InitInstance();
	CMainFrame* pMainFrame = new CMainFrame();
	pMainFrame->CreateEx(0, _T("MAINFRAME"), _T("皮皮武浏览器"), WS_POPUPWINDOW | 
		WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
	m_pMainWnd = pMainFrame;
	pMainFrame->CenterWindow();
	pMainFrame->ShowWindow(TRUE);
	pMainFrame->UpdateWindow();
	return TRUE;
}