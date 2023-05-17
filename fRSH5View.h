
// fRSH5View.h: интерфейс класса CfRSH5View
//

#pragma once


class CfRSH5View : public CView
{
protected:
	CfRSH5View() noexcept;
	DECLARE_DYNCREATE(CfRSH5View);

// Атрибуты
public:
	//CfRSH5Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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

//#ifndef _DEBUG  // версия отладки в fRSH5View.cpp
//inline CfRSH5Doc* CfRSH5View::GetDocument() const
//   { return reinterpret_cast<CfRSH5Doc*>(m_pDocument); }
//#endif

