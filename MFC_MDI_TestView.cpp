
// MFC_MDI_TestView.cpp : implementation of the CMFCMDITestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_MDI_Test.h"
#endif

#include "MFC_MDI_TestDoc.h"
#include "MFC_MDI_TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCMDITestView

IMPLEMENT_DYNCREATE(CMFCMDITestView, CView)

BEGIN_MESSAGE_MAP(CMFCMDITestView, CView)
	ON_WM_CHAR()
	ON_UPDATE_COMMAND_UI(ID_LINE_BTN, &CMFCMDITestView::OnUpdateLineBtn)
	ON_COMMAND(ID_LINE_BTN, &CMFCMDITestView::OnLineBtn)
END_MESSAGE_MAP()

// CMFCMDITestView construction/destruction

CMFCMDITestView::CMFCMDITestView() noexcept
{
	// TODO: add construction code here
	t_int1 = 0;
	t_int2 = 0;
	t_int3 = 0;

}

CMFCMDITestView::~CMFCMDITestView()
{
}

BOOL CMFCMDITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCMDITestView drawing

void CMFCMDITestView::OnDraw(CDC* pDC)
{
	CMFCMDITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect r;
	GetClientRect(&r);
	pDC->DrawText(pDoc->t_str, &r, DT_LEFT);


	// TODO: add draw code for native data here
}


// CMFCMDITestView diagnostics

#ifdef _DEBUG
void CMFCMDITestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCMDITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCMDITestDoc* CMFCMDITestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMDITestDoc)));
	return (CMFCMDITestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCMDITestView message handlers


void CMFCMDITestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMFCMDITestDoc *pDoc = GetDocument();
	pDoc->t_str += TCHAR(nChar);
	pDoc->SetModifiedFlag(); // when you close the window, it notify to save or..close without saving
	pDoc->UpdateAllViews(NULL);

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CMFCMDITestView::OnUpdateLineBtn(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here


}



void CMFCMDITestView::OnLineBtn()
{
	MessageBox(L"HELLO");
	CMFCMDITestDoc *pDoc = GetDocument();
	pDoc->t_str += L"HELLO";
	pDoc->UpdateAllViews(NULL);
}

