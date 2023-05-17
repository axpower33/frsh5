
// fRSH5.h: основной файл заголовка для приложения fRSH5
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


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

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CfRSH5App theApp;
