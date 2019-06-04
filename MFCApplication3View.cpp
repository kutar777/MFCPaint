
// MFCApplication3View.cpp : implementation of the CMFCApplication3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CMFCApplication3View construction/destruction

CMFCApplication3View::CMFCApplication3View() noexcept
{
	// TODO: add construction code here
	//m_points = new CArray<CPoint, CPoint&>;
	m_points.SetSize(0);
}

CMFCApplication3View::~CMFCApplication3View()
{
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View drawing

void CMFCApplication3View::OnDraw(CDC* pDC)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	// TODO: add draw code for native data here
}


// CMFCApplication3View diagnostics

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View message handlers


void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (is_drawing)
	{
		m_point = point;
		m_points.Add(m_point);
	}
	else
	{
		is_drawing = TRUE;
		m_point = point;
		m_prev_point = m_point;
		m_points.Add(m_point);
	}

	

	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication3View::OnMouseMove(UINT nFlags, CPoint point)
{
	if (is_drawing)
	{
		if (m_points.GetCount() > 1)
		{
			CClientDC dc(this);
			for (int i = 1; i < m_points.GetCount(); i++)
			{
				dc.MoveTo(m_points.GetAt(i-1));
				dc.LineTo(m_points.GetAt(i));
			}
		}

		CClientDC dc(this);
		if (m_prev_point != point)
		{
			SetROP2(dc, R2_NOTXORPEN);
			dc.MoveTo(m_point);
			dc.LineTo(m_prev_point);
		}

		dc.MoveTo(m_point);
		dc.LineTo(point);
		
		m_prev_point = point;
	}
	else {}

	CView::OnMouseMove(nFlags, point);
}


void CMFCApplication3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (is_drawing)
	{
		int index = m_points.GetCount();
		if (index > 1)
		{

			m_point = m_points.GetAt(index - 1);
			m_points.RemoveAt(index);
		}
			

	}


	CView::OnRButtonDown(nFlags, point);
}


void CMFCApplication3View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (is_drawing)
	{
		is_drawing = FALSE;

	}

	CView::OnLButtonDblClk(nFlags, point);
}
