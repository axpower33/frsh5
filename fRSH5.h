
// fRSH5.h: основной файл заголовка для приложения fRSH5
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
#include "CACTIVEXREPORTVIEWER1.h"
#include "COCX1.h"
#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <CrystalDecisions.CrystalReports.Engine.dll>
#using <CrystalDecisions.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Xml.dll>
#import <craxddrt.dll> no_namespace
using namespace System::Data::SqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace CrystalDecisions::CrystalReports::Engine;
using namespace System::Data::SqlTypes;
using namespace CrystalDecisions::Windows::Forms;
#define CACTIVEXREPORTVIEWER1_CLASSNAME _T("COCX1")
#define CACTIVEXREPORTVIEWER2_CLASSNAME _T("CACTIVEXREPORTVIEWER1")

//#define CACTIVEXREPORTVIEWER1_CLASSNAME _T("CReportDlg")

class CReportDlg2 : public CDialogEx
{
	// Construction
public:
	DECLARE_DYNAMIC(CReportDlg2);
	CReportDlg2() noexcept;
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/);
	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif
	void OnCrystalDlg2();
	//afx_msg void OnDisplay1();
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL RegisterWindowClass();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDlg2)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
// Implementation
protected:
	//	HICON m_hIcon;

		// Generated message map functions
		//{{AFX_MSG(CReportDlg2)
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	CACTIVEXREPORTVIEWER1 mCRView1;
	afx_msg void OnBnClickedOk();
	IApplicationPtr m_pApp;
	IReportPtr m_pReport;

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CACTIVEXREPORTVIEWER1 mCRView1;
};

class CReportDlg : public CDialogEx
{
	// Construction
public:
	DECLARE_DYNAMIC(CReportDlg);
	CReportDlg() noexcept;
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/);
	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif
	void OnCrystalDlg1();
	//afx_msg void OnDisplay1();
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL RegisterWindowClass();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
// Implementation
protected:
	//	HICON m_hIcon;

		// Generated message map functions
		//{{AFX_MSG(CReportDlg)
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	CACTIVEXREPORTVIEWER1  mCRView1;
	COCX1 pRepDlg2;
};

/////////////////////////////////////////////////////////////////////////////
// CDisplay_CrystalrptDlg dialog

class CDisplay_CrystalrptDlg : public CDialogEx
{
	// Construction
public:
	DECLARE_DYNAMIC(CDisplay_CrystalrptDlg);
	CDisplay_CrystalrptDlg() noexcept;
	BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/);
	// standard constructor

// Dialog Data
	
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif
	void OnCrystalDlg();
	//afx_msg void OnDisplay1();
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL RegisterWindowClass();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplay_CrystalrptDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void PreSubclassWindow();
														//}}AFX_VIRTUAL
// Implementation
protected:
//	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CDisplay_CrystalrptDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	CListBox pList;
	CListBox pList2;
	CListBox pList3;
};

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

extern CReportDlg2 cRepDlg2;
extern CReportDlg cRepDlg;
extern CDisplay_CrystalrptDlg CrystalrptDlg;
extern CfRSH5App theApp;
extern CFrModInCndDlg FrModInCndDlg;
