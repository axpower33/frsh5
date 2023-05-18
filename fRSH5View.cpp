
// fRSH5View.cpp: реализация класса CfRSH5View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "fRSH5.h"
#endif

//#include "fRSH5Doc.h"
#include "fRSH5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CfRSH5View

IMPLEMENT_DYNCREATE(CfRSH5View, CView)

BEGIN_MESSAGE_MAP(CfRSH5View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CfRSH5View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CfRSH5View

CfRSH5View::CfRSH5View() noexcept
{
	// TODO: добавьте код создания

}

CfRSH5View::~CfRSH5View()
{
}

BOOL CfRSH5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CfRSH5View::Circle(float x, float y, float r, CDC* pDC, CfRSH5Doc* pDoc)
{
	pDC->Ellipse(round((x - r - pDoc->GetminX) * pDoc->rangeX),
		round((pDoc->GetScY - (y - r) + pDoc->GetminY) * pDoc->rangeY),
		round((x + r - pDoc->GetminX) * pDoc->rangeX),
		round((pDoc->GetScY - (y + r) + pDoc->GetminY) * pDoc->rangeY));
}

void CfRSH5View::Line(float x1, float y1, float x2, float y2, CDC* pDC, CfRSH5Doc* pDoc)
{
	pDC->MoveTo(round((x1 - pDoc->GetminX) * pDoc->rangeX), round((pDoc->GetScY - y1 + pDoc->GetminY) * pDoc->rangeY));
	pDC->LineTo(round((x2 - pDoc->GetminX) * pDoc->rangeX), round((pDoc->GetScY - y2 + pDoc->GetminY) * pDoc->rangeY));
}

void CfRSH5View::OnDraw(CDC* pDC)
{
	CfRSH5View* pSender=new CfRSH5View();
	HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HPEN redPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN magPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));

	//CBrush  redBrush = CBrush(RGB(255, 0, 0));
    //CBrush 	blackBrush = CBrush(RGB(0, 0, 0));
	HBRUSH 	blueBrush = HBRUSH(RGB(0, 0, 255));
	//CBrush magBrush = CBrush(RGB(255, 0, 255));


	CfRSH5Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

	if (!pDoc)
		return;
	CRect r;
	GetClientRect(&r);

	pDC->FillRect(r, &CBrush(RGB(0, 0, 0)));
	for (pDoc->Pi = pDoc->FirstPat; pDoc->Pi != NULL; pDoc->Pi = pDoc->Pi->next)
	{
		if (pDoc->Pi->q>0)
			pDC->SelectObject(redPen);
		else
			pDC->SelectObject(bluePen);

		pDC->Ellipse((int)(pDoc->Pi->X - 5000000*pDoc->Pi->R),
			(int)(pDoc->Pi->Y - 5000000 * pDoc->Pi->R),
			(int)(pDoc->Pi->X + 5000000 * pDoc->Pi->R ),
			(int)(pDoc->Pi->Y + 5000000 * pDoc->Pi->R));

	}
	//pDoc->UpdateAllViews(pSender,0L,NULL);

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CfRSH5View


void CfRSH5View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CfRSH5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CfRSH5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CfRSH5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CfRSH5View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CfRSH5View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CfRSH5View

#ifdef _DEBUG
void CfRSH5View::AssertValid() const
{
	CView::AssertValid();
}

void CfRSH5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CfRSH5Doc* CfRSH5View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CfRSH5Doc)));
	return (CfRSH5Doc*)m_pDocument;
}
#endif _DEBUG


// Обработчики сообщений CfRSH5View
