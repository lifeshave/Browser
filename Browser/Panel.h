#pragma once


// CPanel

class CPanel : public CWnd
{
	DECLARE_DYNAMIC(CPanel)

public:
	CPanel();
	virtual ~CPanel();
public:
	CImage m_imgCaption;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


