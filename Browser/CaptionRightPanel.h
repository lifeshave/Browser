#pragma once
#include "panel.h"
class CCaptionRightPanel : public CPanel
{
public:
	CCaptionRightPanel(void);
	~CCaptionRightPanel(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

