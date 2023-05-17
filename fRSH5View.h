
// fRSH5View.h: интерфейс класса CfRSH5View
//
#include "fRSH5Doc.h"
#pragma once

class CfRSH5View : public CView
{
public:
	CfRSH5Doc* GetDocument() const;
protected:
	CfRSH5View() noexcept;
	DECLARE_DYNCREATE(CfRSH5View);
// Атрибуты

// Операции
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void Circle(float x, float y, float r, CDC* pDC, CfRSH5Doc* pDoc);
	virtual void Line(float x1, float y1, float x2, float y2, CDC* pDC, CfRSH5Doc* pDoc);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
// Реализация
public:
	virtual ~CfRSH5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в fRSH5View.cpp
inline CfRSH5Doc* CfRSH5View::GetDocument() const
   { return reinterpret_cast<CfRSH5Doc*>(m_pDocument); }
#endif


