
// MFCTimerDlg.h : header file
//

#pragma once

#define MAX_COUNT	200

struct CircleData
{
	int x, y;
	int r;
	COLORREF color;
};
class TW_MemDC
{
private:
	CDC m_mem_dc;
	CBitmap m_mem_bmp;
	int m_width = 0, m_height = 0;

public:
	TW_MemDC()
	{

	}
	~TW_MemDC()
	{
		if (m_mem_dc.m_hDC != NULL)
		{
			m_mem_bmp.DeleteObject();
			m_mem_dc.DeleteDC();
		}
	}
	void Create(CWnd *ap_wnd, int a_width, int a_height)
	{
		CClientDC dc(ap_wnd);

		m_width = a_width;
		m_height = a_height;
		m_mem_dc.CreateCompatibleDC(&dc);
		m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
		m_mem_dc.SelectObject(&m_mem_bmp);
	}
	void Resize(CWnd *ap_wnd, int a_width, int a_height)
	{

		if (a_width != m_width || a_height != m_height)
		{
			if (m_width && m_height)
			{
				m_mem_bmp.DeleteObject();
				m_width = a_width;
				m_height = a_height;

				CClientDC dc(ap_wnd);
				m_mem_bmp.CreateCompatibleBitmap(&dc, m_width, m_height);
				m_mem_dc.SelectObject(&m_mem_bmp);
			}
		}
	}

	inline CDC* GetDC()
	{
		return &m_mem_dc;
	}

	inline int GetWidth()
	{
		return m_width;

	}
	inline int GetHeight()
	{
		return m_height;
	}

	void Draw(CDC *ap_dc, int a_x, int a_y)
	{
		ap_dc->BitBlt(0, 0, m_width, m_height, &m_mem_dc, 0, 0, SRCCOPY);
	}
};


// CMFCTimerDlg dialog
class CMFCTimerDlg : public CDialogEx
{
private:
	CircleData m_list[MAX_COUNT];
	TW_MemDC m_mem_dc;
	

// Construction
public:
	CMFCTimerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTIMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
