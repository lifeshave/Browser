#include "StdAfx.h"
#include "MenuEx.h"


CMenuEx::CMenuEx(void)
{
}


CMenuEx::~CMenuEx(void)
{
}


void CMenuEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	PMENUITEM pMi = (PMENUITEM)lpDrawItemStruct->itemData;
	ASSERT(pMi);
	HDC hDc = lpDrawItemStruct->hDC;
	CRect rcItem = lpDrawItemStruct->rcItem;
	UINT nItemState = lpDrawItemStruct->itemState;
	CDC dc;
	dc.Attach(hDc);
	int nBkMode = dc.SetBkMode(TRANSPARENT);
	CRect rcIcon = rcItem;
	rcIcon.right = rcItem.left + rcItem.Height();
	rcIcon.DeflateRect(2, 2, 2, 2);
	DrawIconEx(hDc, rcIcon.left, rcIcon.top, pMi->hIcon, rcIcon.Width(), rcIcon.Height(), 0, NULL, DI_NORMAL);
	
	CRect rcText = rcItem;
	rcText.left = rcItem.Height();
	if(nItemState & ODS_SELECTED)
	{
		dc.FillRect(rcText, &CBrush(0xFF0000));
	}
	else
	{
		dc.FillRect(rcText, &CBrush(0xFFFFFF));
	}
	dc.DrawText(pMi->strText, rcText, DT_LEFT | DT_SINGLELINE);
	dc.SetBkMode(nBkMode);
	dc.Detach();
}


void CMenuEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 20;
	lpMeasureItemStruct->itemWidth = 50;
}
