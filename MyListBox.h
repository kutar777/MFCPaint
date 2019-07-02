#pragma once

/*
void MyListBox::DrawUserItem(CDC *ap_dc, RECT *ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
{
	if (a_select_flag)
		ap_dc->SetTextColor(RGB(240, 240, 0));
	else
		ap_dc->SetTextColor(RGB(128, 128, 0));

	CString str;
	GetText(a_index, str);
	ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, str);
}
*/

class MyListBox : public CListBox
{
	DECLARE_DYNAMIC(MyListBox)
private:
	CBrush m_my_list_bk_brush;
	COLORREF m_select_color, m_focus_color, m_bk_color;
public:
	MyListBox();
	virtual ~MyListBox();

	void SetItemColor(COLORREF a_select_color, COLORREF a_focus_color, COLORREF a_bk_color);
	virtual void DrawListItem(CDC *ap_dc, RECT *ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);
	virtual void DrawUserItem(CDC *ap_dc, RECT *ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpds*/);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


