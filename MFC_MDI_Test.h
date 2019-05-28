
// MFC_MDI_Test.h : main header file for the MFC_MDI_Test application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCMDITestApp:
// See MFC_MDI_Test.cpp for the implementation of this class
//

class CMFCMDITestApp : public CWinApp
{
public:
	CMFCMDITestApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCMDITestApp theApp;
