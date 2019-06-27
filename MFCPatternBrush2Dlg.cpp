
// MFCPatternBrush2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCPatternBrush2.h"
#include "MFCPatternBrush2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPatternBrush2Dlg dialog



CMFCPatternBrush2Dlg::CMFCPatternBrush2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPATTERNBRUSH2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPatternBrush2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCPatternBrush2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CMFCPatternBrush2Dlg message handlers

BOOL CMFCPatternBrush2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_normal_image.Load(L"s_normal.png");
	m_small_image.Load(L"s_small.png");

	CRect win_rect, client_rect;
	GetWindowRect(&win_rect);
	GetClientRect(&client_rect);

	CBitmap *p_bmp = CBitmap::FromHandle((HBITMAP)m_normal_image);
	m_normal_brush.CreatePatternBrush(p_bmp);

	p_bmp = CBitmap::FromHandle((HBITMAP)m_small_image);
	m_small_brush.CreatePatternBrush(p_bmp);

	int w_fix = win_rect.Width() - client_rect.Width();
	int h_fix = win_rect.Height() - client_rect.Height();

	SetWindowPos(NULL, 0, 0, m_small_image.GetWidth() + w_fix, m_small_image.GetHeight() + h_fix, SWP_NOMOVE);

	SetBackgroundColor(RGB(0, 0, 0));

	m_mem_view.Create(m_small_image.GetWidth(), m_small_image.GetHeight(), 32);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCPatternBrush2Dlg::OnPaint()
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
		// m_small_image.Draw(dc, 0, 0);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCPatternBrush2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCPatternBrush2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	CDC *p_dc = CDC::FromHandle(m_mem_view.GetDC());

	CGdiObject *p_old_pen = p_dc->SelectStockObject(NULL_PEN);
	p_dc->FillSolidRect(0, 0, m_small_image.GetWidth(), m_small_image.GetHeight(), RGB(0, 0, 0));
	m_small_image.AlphaBlend(*p_dc, 0, 0, m_alpha);
	CBrush *p_old_brush;
	if (m_is_clicked)
	{
		p_dc->SetBrushOrg(point.x *(-1), point.y *(-1));
		p_old_brush = p_dc->SelectObject(&m_normal_brush);
	}
	else
	{
		p_dc->SetBrushOrg(0, 0);
		p_old_brush = p_dc->SelectObject(&m_small_brush);

	}
	p_dc->Ellipse(point.x - m_radius, point.y - m_radius, point.x + m_radius, point.y + m_radius);
	p_dc->SelectObject(p_old_brush);
	p_dc->SelectObject(p_old_pen);

	if (m_is_clicked)
	{
		CPen grid_pen(PS_DOT, 1, RGB(160, 160, 160));
		CPen *p_old_pen = p_dc->SelectObject(&grid_pen);
		p_dc->SetBkMode(TRANSPARENT);
		p_dc->MoveTo(point.x, point.y - m_radius);
		p_dc->LineTo(point.x, point.y + m_radius);
		p_dc->MoveTo(point.x - m_radius, point.y);
		p_dc->LineTo(point.x + m_radius, point.y);
		p_dc->SelectObject(p_old_pen);
	}

	m_mem_view.ReleaseDC();
	m_mem_view.Draw(dc, 0, 0);
	
	//CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCPatternBrush2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_is_clicked = 1;
	SetCapture();
	OnMouseMove(nFlags, point);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCPatternBrush2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_is_clicked = 0;
	ReleaseCapture();
	OnMouseMove(nFlags, point);

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CMFCPatternBrush2Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int old_radius = m_radius;
	if (zDelta > 0)
	{
		if (nFlags & MK_CONTROL)
		{
			m_alpha -= 10;
			if (m_alpha < 0) m_alpha = 0;
		}
		else
			if(m_radius >= 20) m_radius -= 5;
	}
	else
	{
		if (nFlags & MK_CONTROL)
		{
			m_alpha += 10;
			if (m_alpha > 255) m_alpha = 255;
		}
		else
			if (m_radius < 60) m_radius += 5;
	}
	if (old_radius != m_radius)
	{
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(&pos);

		OnMouseMove(0, pos);
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
