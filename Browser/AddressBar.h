#pragma once
#include "panel.h"
#include "ImageButton.h"
#include "AddressComboBox.h"
class CAddressBar : public CPanel
{
private:
	CImage m_imgTool;
	CImageButton m_btnGo;
	CAddressComboBox m_addressComboBox;
public:
	CAddressBar(void);
	~CAddressBar(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

