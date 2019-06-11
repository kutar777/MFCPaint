
// MFCTimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCTimer.h"
#include "MFCTimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTimerDlg dialog
CMFCTimerDlg::CMFCTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTimerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCTimerDlg message handlers

BOOL CMFCTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect r;
	GetClientRect(r);
	//m_width = r.Width();
	//m_height = r.Height();

	m_mem_dc.Create(this, r.Width(), r.Height());
	//CClientDC dc(this);
	//m_mem_dc.CreateCompatibleDC(&dc);
	//m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
	//m_mem_dc.SelectObject(&m_mem_bmp);

	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAX_COUNT; i++)
	{
		m_list[i].x = rand() % m_mem_dc.GetWidth();		// 0 ~ w-1
		m_list[i].y = rand() % m_mem_dc.GetHeight();	// 0 ~ h-1
		m_list[i].r = rand() % 40 + 10;					// 10~49
		m_list[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 50, NULL); // WM_TIMER

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCTimerDlg::OnPaint()
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
		m_mem_dc.Draw(&dc, 0, 0);
		//dc.BitBlt(0, 0, m_mem_dc.GetWidth(), m_mem_dc.GetHeight(), m_mem_dc.GetDC(), 0, 0, SRCCOPY);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		//CRect r;
		//GetClientRect(r);
		//int w = r.Width(), h = r.Height();
		CDC *p_dc = m_mem_dc.GetDC();

		CircleData *p = m_list;
		CBrush fill_brush, *p_old_brush = p_dc->GetCurrentBrush();
		p_dc->FillSolidRect(0, 0, m_mem_dc.GetWidth(), m_mem_dc.GetHeight(), RGB(220, 220, 220));

		for (int i = 0; i < MAX_COUNT; i++)
		{
			p->r--;
			if (p->r == 0)
			{
				p->x = rand() % m_mem_dc.GetWidth();	// 0 ~ w-1
				p->y = rand() % m_mem_dc.GetHeight();	// 0 ~ h-1
				p->r = rand() % 40 + 10;	// 10~49
				p->color = RGB(rand() % 256, rand() % 256, rand() % 256);

			}
			fill_brush.CreateSolidBrush(p->color);
			p_dc->SelectObject(&fill_brush);
			//p_old_brush = dc.SelectObject(&fill_brush);
			p_dc->Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			fill_brush.DeleteObject();
			p++;
		}
		p_dc->SelectObject(p_old_brush);
		//BITMAP bmp_info;
		Invalidate(FALSE);
	}
	else
	{
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMFCTimerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(1);
	// TODO: Add your message handler code here
}


void CMFCTimerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_mem_dc.Resize(this, cx, cy);

	//if (cx != m_mem_dc.GetWidth() || cy != m_mem_dc.GetHeight())
	//{
		//if (m_mem_dc.GetWidth() && m_mem_dc.GetHeight())
		//{
			//m_mem_dc.Resize(this, cx, cy);
			//m_width = cx;
			//m_height = cy;

			//m_mem_bmp.DeleteObject();
		
			//CClientDC dc(this);
			//m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
			//m_mem_dc.SelectObject(&m_mem_bmp);
			//m_mem_dc.FillSolidRect(0, 0, m_width, m_height, RGB(220, 220, 220));
			// re-draw
		//}
	//}
}
