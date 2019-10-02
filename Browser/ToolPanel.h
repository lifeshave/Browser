#pragma once
#include "panel.h"
#include "MainToolBar.h"
#include "AddressBar.h"
class CToolPanel : public CPanel
{
public:
	CToolPanel(void);
	~CToolPanel(void);
private:
	CImage m_imgTool;
	CMainToolBar m_mainToolBar;
	CAddressBar m_addressBar;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

