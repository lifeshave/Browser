#pragma once
#include "afxwin.h"
typedef struct _MENUITEM
{
	HICON hIcon;
	CString strText;
}MENUITEM, *PMENUITEM;
class CMenuEx : public CMenu
{
public:
	CMenuEx(void);
	~CMenuEx(void);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
};

