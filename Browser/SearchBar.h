#pragma once
#include "panel.h"
#include "ImageButton.h"
#include "IconButton.h"

class CSearchBar : public CPanel
{
public:
	CSearchBar(void);
	~CSearchBar(void);
private:
	CImage m_imgTool;
	CImage m_imgBand;
	CImageButton m_btnSearch;
	CEdit m_editSearch;
	CIconButton m_btnIcon;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSelIconButton();
};

