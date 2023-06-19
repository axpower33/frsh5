
// fRSH5.h: основной файл заголовка для приложения fRSH5
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы

class CFrModInCndDlg :public CDialogEx
{
public:
	int m_Npat;
	float m_dt;
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
	*/void OnCancel();
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

extern CfRSH5App theApp;
extern CFrModInCndDlg FrModInCndDlg;
