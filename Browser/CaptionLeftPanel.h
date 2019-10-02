#pragma once
#include "panel.h"
class CCaptionLeftPanel : public CPanel
{
public:
	void UpdateSystemMenu(CMenu *pMenu);
public:
	CCaptionLeftPanel(void);
	~CCaptionLeftPanel(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

