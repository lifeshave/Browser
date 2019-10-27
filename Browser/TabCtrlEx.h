#pragma once
#include "panel.h"
#include "TabButton.h"
using namespace std;

class CTabCtrlEx :public CPanel
{
private:
	CImage m_imgTabPanel;
	CArray<CTabButton*> m_arrTabButton;
public:
	int AddItem(CString strText);
public:
	CTabCtrlEx(void);
	~CTabCtrlEx(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

