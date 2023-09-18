
// fRSH5.h: основной файл заголовка для приложения fRSH5
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#if !defined(AFX_DISPLAY_CRYSTALRPTDLG_H__19B1EC89_FCE0_42D0_898F_F64A299D20AF__INCLUDED_)
#define AFX_DISPLAY_CRYSTALRPTDLG_H__19B1EC89_FCE0_42D0_898F_F64A299D20AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDisplay_CrystalrptDlg dialog

class CDisplay_CrystalrptDlg : public CDialogEx
{
	// Construction
public:
	CDisplay_CrystalrptDlg() noexcept;
	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDisplay_CrystalrptDlg)
	enum { IDD = IDD_DIALOG4 };
	CString	m_StudentName;
	//}}AFX_DATA
	void OnCrystalDlg();
	afx_msg void OnDisplay1();
	//afx_msg void OnDisplay2();
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplay_CrystalrptDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDisplay_CrystalrptDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAY_CRYSTALRPTDLG_H__19B1EC89_FCE0_42D0_898F_F64A299D20AF__INCLUDED_)

class CFrModInCndDlg :public CDialogEx
{
public:
	int m_Npat;
	double m_dt;
	int m_rd;
	CFrModInCndDlg() noexcept;
	~CFrModInCndDlg();
	void OnFrMod_InCnd();
	BOOL OnInitDialog();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FrModInCnd };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	// Реализация
protected:

	void OnChangeEdit1();
	void OnChangeEdit2();
/*	void OnBnClickedRadio1();
	void OnBnClickedRadio2();
	*/
	void OnCancel();
	DECLARE_MESSAGE_MAP();
};

// CfRSH5App:
// Сведения о реализации этого класса: fRSH5.cpp
//
class CfRSH5App : public CWinAppEx
{
public:
	CfRSH5App() noexcept;
// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	
	BOOL CfRSH5App::OnIdle(LONG lCount);
	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDisplay_CrystalrptDlg CrystalrptDlg;
extern CfRSH5App theApp;
extern CFrModInCndDlg FrModInCndDlg;
