// Display_Crystalrpt.h : main header file for the DISPLAY_CRYSTALRPT application
//

#if !defined(AFX_DISPLAY_CRYSTALRPT_H__83D19A4B_127E_42B4_A60B_FA23BF77309E__INCLUDED_)
#define AFX_DISPLAY_CRYSTALRPT_H__83D19A4B_127E_42B4_A60B_FA23BF77309E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDisplay_CrystalrptApp:
// See Display_Crystalrpt.cpp for the implementation of this class
//

class CDisplay_CrystalrptApp : public CWinApp
{
public:
	CDisplay_CrystalrptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplay_CrystalrptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDisplay_CrystalrptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAY_CRYSTALRPT_H__83D19A4B_127E_42B4_A60B_FA23BF77309E__INCLUDED_)
