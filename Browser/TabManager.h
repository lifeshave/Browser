#pragma once
#include "panel.h"
#include "ImageButton.h"

class CTabManager :public CPanel
{
private:
	CImage m_imgTabPanel;
	CImageButton m_imgTabButtonNew;
	CImageButton m_imgTabButtonFullScreen;
	CImageButton m_imgTabButtonLeft;
	CImageButton m_imgTabButtonRight;
	CImageButton m_imgTabButtonClose;
public:
	CTabManager(void);
	~CTabManager(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};

