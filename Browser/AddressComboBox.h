#pragma once


// CAddressComboBox

class CAddressComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CAddressComboBox)

public:
	CAddressComboBox();
	virtual ~CAddressComboBox();
private:
	CImage m_imgComboBox;
	CImage m_imgComboBoxThump;
	BOOL m_bIsThumpHover;
	BOOL m_bIsThumpDown;
public:
	int AddString(LPCTSTR lpszString, HICON hIcon);
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
};


