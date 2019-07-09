
// MFCScrollBarImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCScrollBarImage.h"
#include "MFCScrollBarImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCScrollBarImageDlg dialog



CMFCScrollBarImageDlg::CMFCScrollBarImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSCROLLBARIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCScrollBarImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCScrollBarImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCScrollBarImageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCScrollBarImageDlg message handlers

BOOL CMFCScrollBarImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_rect.left = 0;
	m_rect.top = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCScrollBarImageDlg::OnPaint()
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
		if (!m_image.IsNull())
		{
			//dc.SetStretchBltMode(COLORONCOLOR);
			int scroll_x_pos = GetScrollPos(SB_HORZ);
			int scroll_y_pos = GetScrollPos(SB_VERT);

			m_image.Draw(dc, -scroll_x_pos, -scroll_y_pos);
			m_image.Draw(dc, 0, 0, m_rect.Width(), m_rect.Height(),
				scroll_x_pos, scroll_y_pos, m_rect.Width(), m_rect.Height());
		}

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCScrollBarImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCScrollBarImageDlg::OnBnClickedButton1()
{
	wchar_t name_filter[] = L"All Files (*.*)|*.*|Jpeg (*.jpg)|*.jpg||";
	CFileDialog ins_dlg(TRUE, L"jpg", L"*.jpg", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 1;

	if (IDOK == ins_dlg.DoModal())
	{
		if (!m_image.IsNull()) m_image.Destroy();

		m_image.Load(ins_dlg.GetPathName());
		SetScrollRange(SB_HORZ, 0, m_image.GetWidth() - m_rect.Width(), 0);
		SetScrollRange(SB_VERT, 0, m_image.GetHeight() - m_rect.Height(), 0);

		Invalidate(FALSE);
	}
}


void CMFCScrollBarImageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_rect.right = cx;
	m_rect.bottom = cy;
	
	if (!m_image.IsNull())
	{
		SetScrollRange(SB_HORZ, 0, m_image.GetWidth() - m_rect.Width(), 0);
		SetScrollRange(SB_VERT, 0, m_image.GetHeight() - m_rect.Height(), 0);
	}
	Invalidate(FALSE);


	// TODO: Add your message handler code here
}

void CMFCScrollBarImageDlg::ProcessScroll(UINT nSBCode, UINT nPos, int a_scroll_type)
{
	int scroll_pos = GetScrollPos(a_scroll_type), min = 0, max = 0;
	GetScrollRange(a_scroll_type, &min, &max);
	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (scroll_pos < max) SetScrollPos(a_scroll_type, ++scroll_pos);
		break;
	case SB_LINEUP:
		if (scroll_pos > min) SetScrollPos(a_scroll_type, --scroll_pos);
		break;
	case SB_PAGEDOWN:
		if (scroll_pos + 24 < max) SetScrollPos(a_scroll_type, scroll_pos + 24);
		break;
	case SB_PAGEUP:
		if (scroll_pos - 24 > min) SetScrollPos(a_scroll_type, scroll_pos - 24);
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		SetScrollPos(a_scroll_type, nPos);
	}
	Invalidate(FALSE);
}

void CMFCScrollBarImageDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL)
	{
		ProcessScroll(nSBCode, nPos, SB_VERT);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMFCScrollBarImageDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL)
	{
		ProcessScroll(nSBCode, nPos, SB_HORZ);

	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



