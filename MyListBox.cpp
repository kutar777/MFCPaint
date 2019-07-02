// MyListBox.cpp : implementation file
//

#include "stdafx.h"
#include "MyListBox.h"


// MyListBox

IMPLEMENT_DYNAMIC(MyListBox, CListBox)

MyListBox::MyListBox() : m_my_list_bk_brush(RGB(0, 0, 128))
{

}

MyListBox::~MyListBox()
{
}


BEGIN_MESSAGE_MAP(MyListBox, CListBox)
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// MyListBox message handlers
void MyListBox::SetItemColor(COLORREF a_select_color, COLORREF a_focus_color, COLORREF a_bk_color)
{
	m_select_color = a_select_color;
	m_focus_color = a_focus_color;
	m_bk_color = a_bk_color;

	m_my_list_bk_brush.DeleteObject();
	m_my_list_bk_brush.CreateSolidBrush(m_bk_color);

}

void MyListBox::DrawUserItem(CDC *ap_dc, RECT *ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
{
	if (a_select_flag) ap_dc->SetTextColor(RGB(240, 240, 0));
	else ap_dc->SetTextColor(RGB(128, 128, 0));

	CString str;
	GetText(a_index, str);
	ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, str);
}
void MyListBox::DrawListItem(CDC *ap_dc, RECT *ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
{
	if (a_select_flag)
	{
		if (a_focus_flag)
			ap_dc->FillSolidRect(ap_rect, m_focus_color);
		else
			ap_dc->FillSolidRect(ap_rect, m_select_color);
	}
	else
		ap_dc->FillSolidRect(ap_rect, m_bk_color);

	DrawUserItem(ap_dc, ap_rect, a_index, ap_data, a_select_flag, a_focus_flag);
}

void MyListBox::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	if (lpds->itemID != 0xFFFFFFFF && lpds->itemID < GetCount())
	{
		if ((lpds->itemAction & ODA_DRAWENTIRE) ||
			(lpds->itemAction & ODA_FOCUS) ||
			(lpds->itemAction & ODA_SELECT))
		{
			//CDC *p_dc = CDC::FromHandle(lpds->hDC);

			DrawListItem(CDC::FromHandle(lpds->hDC), &lpds->rcItem, lpds->itemID, (void *)lpds->itemData,
				lpds->itemState & ODS_SELECTED, lpds->itemState & ODS_FOCUS);
		}
	}
}
HBRUSH MyListBox::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	
	return m_my_list_bk_brush;
}
