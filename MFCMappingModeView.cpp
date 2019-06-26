
// MFCMappingModeView.cpp : implementation of the CMFCMappingModeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCMappingMode.h"
#endif

#include "MFCMappingModeDoc.h"
#include "MFCMappingModeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMappingModeView

IMPLEMENT_DYNCREATE(CMFCMappingModeView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCMappingModeView, CScrollView)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCMappingModeView construction/destruction

CMFCMappingModeView::CMFCMappingModeView() noexcept
{
	// TODO: add construction code here

}

CMFCMappingModeView::~CMFCMappingModeView()
{
}

BOOL CMFCMappingModeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CMFCMappingModeView drawing

void CMFCMappingModeView::OnDraw(CDC* pDC)
{
	CMFCMappingModeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for (int i = 0; i <= 1000 / 100; i++)
	{
		pDC->MoveTo(0, 100 * i);
		pDC->LineTo(1000, 100 * i);
	}
	for (int i = 0; i <= 1000 / 100; i++)
	{
		pDC->MoveTo(100 * i, 0);
		pDC->LineTo(100 * i, 1000);
	}
}

void CMFCMappingModeView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 1000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMFCMappingModeView diagnostics

#ifdef _DEBUG
void CMFCMappingModeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCMappingModeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCMappingModeDoc* CMFCMappingModeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMappingModeDoc)));
	return (CMFCMappingModeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCMappingModeView message handlers


void CMFCMappingModeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	//CScrollView::OnPrepareDC(pDC, pInfo);

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(1000, -1000);
	pDC->SetWindowOrg(0, 0);
	pDC->SetViewportExt(zoom_x, zoom_y);
	//CPoint pos = GetScrollPosition();
	CRect r;
	GetClientRect(&r);

	pDC->SetViewportOrg(r.Width() / 2, r.Height() / 2);
	CSize size = pDC->GetWindowExt();

}


void CMFCMappingModeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_PRIOR)
	{
		zoom_x += 200;
		zoom_y += 200;
		Invalidate();
	}
	if (nChar == VK_NEXT)
	{
		zoom_x -= 200;
		zoom_y -= 200;
		Invalidate();
	}
	if(nChar == VK_HOME)
	{
		zoom_x = zoom_y = 1000;
		Invalidate();
	}

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = zoom_x;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCMappingModeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CPoint new_pos;
	new_pos.x = ((point.x + 50) / 100) * 100;
	new_pos.y = ((point.y + 50) / 100) * 100;
	dc.Ellipse(new_pos.x - 50, new_pos.y - 50, new_pos.x + 50, new_pos.y + 50);

	
	
	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCMappingModeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CScrollView::OnMouseMove(nFlags, point);
}
