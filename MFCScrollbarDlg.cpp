
// MFCScrollbarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCScrollbar.h"
#include "MFCScrollbarDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCScrollbarDlg dialog



CMFCScrollbarDlg::CMFCScrollbarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSCROLLBAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCScrollbarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCScrollbarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCScrollbarDlg message handlers

BOOL CMFCScrollbarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CRect r;
	GetClientRect(r);

	SetScrollRange(SB_VERT, 0, 8*9*24 - r.Height(), 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCScrollbarDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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
		CString str;
		int count = 0;
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0, 0, 200));
		int scroll_pos = GetScrollPos(SB_VERT);

		for (int dan = 2; dan <= 9; dan++)
		{
			for (int i = 1; i <= 9; i++)
			{
				str.Format(L"%d * %d = %d", dan, i, dan * i);
				dc.TextOut(10, 5 + 25 * count - scroll_pos, str);
				count++;
			}
		}

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCScrollbarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCScrollbarDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL)
	{
		int scroll_pos = GetScrollPos(SB_VERT), min = 0, max = 0;
		GetScrollRange(SB_VERT, &min, &max);
		switch (nSBCode)
		{
			case SB_LINEDOWN :
				if(scroll_pos < max) SetScrollPos(SB_VERT, ++scroll_pos);
				break;
			case SB_LINEUP:
				if(scroll_pos > min) SetScrollPos(SB_VERT, --scroll_pos);
				break;
			case SB_PAGEDOWN:
				if (scroll_pos + 24 < max) SetScrollPos(SB_VERT, scroll_pos + 24);
				break;
			case SB_PAGEUP:
				if (scroll_pos - 24 > min) SetScrollPos(SB_VERT, scroll_pos - 24);
				break;
			case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
				SetScrollPos(SB_VERT, nPos);
		}
		Invalidate();
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMFCScrollbarDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(r);

	SetScrollRange(SB_VERT, 0, 8 * 9 * 24 - r.Height(), 0);
}
