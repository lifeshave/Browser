#pragma once
#include "panel.h"
#include "TabCtrlEx.h"
#include "TabManager.h"
class CTabPanel : public CPanel
{
private:
	CImage m_imgTabPanel;
	CTabCtrlEx m_wndTabCtrl;
	CTabManager m_tabManager;
public:
	CTabPanel(void);
	~CTabPanel(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

