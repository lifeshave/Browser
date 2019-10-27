#pragma once

class CTabButton : public CWnd
{
	DECLARE_DYNAMIC(CTabButton)

public:
	CTabButton();
	virtual ~CTabButton();
public:
	void SetImage(UINT uIDResource);
	void SetSelected(BOOL bIsSelected);
private:
	CImage m_imgButton;
	BOOL m_bIsSelected;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnPaint();
	afx_msg void CTabButton::OnMouseMove(UINT nFlag, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


