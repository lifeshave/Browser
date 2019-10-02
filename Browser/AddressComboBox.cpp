// AddressComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "Browser.h"
#include "AddressComboBox.h"


// CAddressComboBox

IMPLEMENT_DYNAMIC(CAddressComboBox, CComboBox)

CAddressComboBox::CAddressComboBox()
{
	m_bIsThumpHover = FALSE;
	m_bIsThumpDown = FALSE;
}

CAddressComboBox::~CAddressComboBox()
{
}


BEGIN_MESSAGE_MAP(CAddressComboBox, CComboBox)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CAddressComboBox 消息处理程序




void CAddressComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	HDC hDc = lpDrawItemStruct->hDC;
	int nItem = lpDrawItemStruct->itemID;
	CRect rcItem = lpDrawItemStruct->rcItem;
	HICON hIcon = (HICON)lpDrawItemStruct->itemData;
	if(hIcon)
	{
		DrawIconEx(hDc, rcItem.left, rcItem.top, hIcon, 16, 16, 0, 0, DI_NORMAL);
	}
	CString strItem;
	GetLBText(nItem, strItem);
	if(!strItem.IsEmpty())
	{
		CRect rcText = rcItem;
		rcText.left = 20;
		DrawText(hDc, strItem, strItem.GetLength(), rcText, DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
	}
}


void CAddressComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	
}


int CAddressComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetItemHeight(-1, 22);
	if(!m_imgComboBox.IsNull())
		return 0;
	if(!m_imgComboBoxThump.IsNull())
		return 0;

	m_imgComboBox.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_COMBOBOX);
	m_imgComboBoxThump.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_COMBOBOX_THUMP);
	return 0;
}


void CAddressComboBox::OnPaint()
{
	CPaintDC dc(this); 
	if(m_imgComboBox.IsNull())
		return ;
	if(m_imgComboBoxThump.IsNull())
		return ;
	CRect rcComboBox;
	GetClientRect(rcComboBox);
	// 左边
	CRect rcComboLeft = rcComboBox;
	rcComboLeft.right = 10;
	rcComboLeft.bottom = 28;
	m_imgComboBox.Draw(dc.m_hDC, rcComboLeft, CRect(0, 0, 10, 28));

	// 上边
	CRect rcComboTop = rcComboBox;
	rcComboTop.left = 10;
	rcComboTop.top = 0;
	rcComboTop.bottom = 5;
	m_imgComboBox.Draw(dc.m_hDC, rcComboTop, CRect(10, 0, 20, 5));

	// 下边
	CRect rcComboBottom = rcComboBox;
	rcComboBottom.left = 10;
	rcComboBottom.right = rcComboBox.right;
	rcComboBottom.top = 23;
	rcComboBottom.bottom = 28;
	m_imgComboBox.Draw(dc.m_hDC, rcComboBottom, CRect(10, 23, 20, 28));

	// 绘制右边箭头
	COMBOBOXINFO comboBoxInfo;
	comboBoxInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&comboBoxInfo);
	CRect rcEdit;
	::GetClientRect(comboBoxInfo.hwndItem, &rcEdit);
	CRect rcComboBoxThump = rcComboBox;
	rcComboBoxThump.left = 10 + rcEdit.Width();
	rcComboBoxThump.right = rcComboBox.right;
	rcComboBoxThump.top = 5;
	rcComboBoxThump.bottom = 23;
	if(m_bIsThumpHover)
	{
		if(m_bIsThumpDown)
		{
			m_imgComboBoxThump.Draw(dc.m_hDC, rcComboBoxThump, CRect(42, 0, 63, 21));
		}
		else
		{
			m_imgComboBoxThump.Draw(dc.m_hDC, rcComboBoxThump, CRect(21, 0, 42, 21));
		}
	}
	else
	{
		m_imgComboBoxThump.Draw(dc.m_hDC, rcComboBoxThump, CRect(0, 0, 21, 21));
	}
	
}


void CAddressComboBox::OnSize(UINT nType, int cx, int cy)
{
	CComboBox::OnSize(nType, cx, cy);
	COMBOBOXINFO comboBoxInfo;
	comboBoxInfo.cbSize = sizeof(COMBOBOXINFO);
	GetComboBoxInfo(&comboBoxInfo);
	CRect rcEdit;
	rcEdit.left = 10;
	rcEdit.right = comboBoxInfo.rcButton.left;
	rcEdit.top = 5;
	rcEdit.bottom = 23;
	::MoveWindow(comboBoxInfo.hwndItem, rcEdit.left, rcEdit.top, rcEdit.Width(), rcEdit.Height(), TRUE);
}


void CAddressComboBox::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = 1; // HOVER_DEFAULT改为1, 解决Win10上停留较长时间才切换图片的问题
	TrackMouseEvent(&tme);
	CComboBox::OnMouseMove(nFlags, point);
}

LRESULT CAddressComboBox::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	CPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	if(!m_bIsThumpHover)
	{
		CRect rcComboBox;
		GetClientRect(rcComboBox);
		COMBOBOXINFO comboBoxInfo;
		comboBoxInfo.cbSize = sizeof(COMBOBOXINFO);
		GetComboBoxInfo(&comboBoxInfo);
		CRect rcEdit;
		::GetClientRect(comboBoxInfo.hwndItem, &rcEdit);
		CRect rcComboBoxThump = rcComboBox;
		rcComboBoxThump.left = 10 + rcEdit.Width();
		rcComboBoxThump.right = rcComboBox.right;
		rcComboBoxThump.top = 5;
		rcComboBoxThump.bottom = 23;
		if(rcComboBoxThump.PtInRect(pt))
		{
			if(wParam == MK_LBUTTON)
			{
				m_bIsThumpDown = TRUE;
			}
			else
			{
				m_bIsThumpDown = FALSE; 
			}
			m_bIsThumpHover = TRUE;
			Invalidate();
		}
	}

	return TRUE;
}

LRESULT CAddressComboBox::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if(m_bIsThumpHover)
	{
		m_bIsThumpHover = FALSE;
		m_bIsThumpDown = FALSE; 
		Invalidate();
	}
	return TRUE;
}

int CAddressComboBox::AddString(LPCTSTR lpszString, HICON hIcon)
{
	int nItem = CComboBox::AddString(lpszString);
	SetItemData(nItem, (DWORD)hIcon);
	return nItem;
}