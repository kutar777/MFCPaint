
// MFCApplication5Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication5Dlg dialog



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONUP()
	ON_COMMAND(20000, OnMyCommand)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SELECT_COL_BTN, &CMFCApplication5Dlg::OnBnClickedSelectColBtn)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CMFCApplication5Dlg message handlers

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication5Dlg::OnPaint()
{
	if (IsIconic())
	{

		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication5Dlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	CMenu menu;
	
	menu.CreatePopupMenu();

	CString str;
	for (int i = 0; i < 5; i++)
	{
		str.Format(L"%d Menu", i);
		menu.AppendMenu(MF_STRING, 20000 + i, str); // is not Message ID, WM_COMMAND, wParam
	}
		
	CPoint pos;
	GetCursorPos(&pos);

	menu.TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
	menu.DestroyMenu();

	CDialogEx::OnRButtonUp(nFlags, point);
}


BOOL CMFCApplication5Dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int cmd_id = LOWORD(wParam);

	if (cmd_id > 20000 && cmd_id < 20005)
	{
		CString str;
		str.Format(L"%d is Selected", cmd_id - 20000);
		AfxMessageBox(str);
		return 1;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

void CMFCApplication5Dlg::OnMyCommand()
{
	AfxMessageBox(L"First MENU");

}

void CMFCApplication5Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*CRect r(10, 10, 100, 100);
	if (r.PtInRect(point))
	{
		CColorDialog ins_dlg;
		ins_dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
		ins_dlg.m_cc.rgbResult = m_user_color;

		if (IDOK == ins_dlg.DoModal())
		{
			m_user_color = ins_dlg.GetColor();
			InvalidateRect(r);
		}
	}
*/
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication5Dlg::OnBnClickedSelectColBtn()
{
	CColorDialog ins_dlg;
	ins_dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	ins_dlg.m_cc.rgbResult = m_user_color;

	if (IDOK == ins_dlg.DoModal())
	{
		m_user_color = ins_dlg.GetColor();
		GetDlgItem(IDC_SELECT_COL_BTN)->Invalidate();
		CRect r(10, 10, 110, 110);
		//InvalidateRect(r);
	}
}


void CMFCApplication5Dlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpds)
{
	if (nIDCtl == IDC_SELECT_COL_BTN)
	{
		CDC *p_dc = CDC::FromHandle(lpds->hDC);
		p_dc->FillSolidRect(&lpds->rcItem, RGB(228, 228, 228));
		CString str;
		GetDlgItemText(IDC_SELECT_COL_BTN, str);

		CRect r(lpds->rcItem);
		CRect color_rect(lpds->rcItem.left + 3, lpds->rcItem.top + 3, lpds->rcItem.right -3, lpds->rcItem.bottom - 3);
		if (lpds->itemState & ODS_SELECTED)
		{
			r -= CPoint(1, 1);
			color_rect -= CPoint(1, 1);
			p_dc->Draw3dRect(r, RGB(210, 210, 210), RGB(238, 238, 238));
			//p_dc->FillSolidRect(&lpds->rcItem, RGB(245, 245, 245));
		}
		else
		{
			p_dc->Draw3dRect(&lpds->rcItem, RGB(248, 248, 248), RGB(168, 168, 168));
		}

		p_dc->SetBkMode(TRANSPARENT);
		p_dc->SetTextColor(m_user_color);
		p_dc->DrawText(str, color_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		p_dc->Draw3dRect(color_rect, m_user_color, m_user_color);
	}

	CDialogEx::OnDrawItem(nIDCtl, lpds);
}
