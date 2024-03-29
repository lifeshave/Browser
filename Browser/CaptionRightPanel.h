#pragma once
#include "panel.h"
#include "ImageButton.h"

class CCaptionRightPanel : public CPanel
{
public:
	CImageButton m_imgMinBtn;
	CImageButton m_imgMaxBtn;
	CImageButton m_imgCloseBtn;
public:
	CCaptionRightPanel(void);
	~CCaptionRightPanel(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClickedMinBtn();
	afx_msg void OnClickedMaxBtn();
	afx_msg void OnClickedCloseBtn();
};

