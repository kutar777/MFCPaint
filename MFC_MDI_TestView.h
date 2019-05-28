
// MFC_MDI_TestView.h : interface of the CMFCMDITestView class
//

#pragma once


class CMFCMDITestView : public CView
{
public:
	int t_int1, t_int2, t_int3;
protected: // create from serialization only
	CMFCMDITestView() noexcept;
	DECLARE_DYNCREATE(CMFCMDITestView)

// Attributes
public:
	CMFCMDITestDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCMDITestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateLineBtn(CCmdUI *pCmdUI);
	afx_msg void OnLineBtn();
};

#ifndef _DEBUG  // debug version in MFC_MDI_TestView.cpp
inline CMFCMDITestDoc* CMFCMDITestView::GetDocument() const
   { return reinterpret_cast<CMFCMDITestDoc*>(m_pDocument); }
#endif

