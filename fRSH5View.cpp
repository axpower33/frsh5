
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

#define Pprt(a) (*(Particle**)a)
int sortOfZ(const void* a, const void* b)
{
    if (Pprt(a)->Z > Pprt(b)->Z) return  1; else
        if (Pprt(a)->Z < Pprt(b)->Z) return -1; else
            return  0;
}

void CfRSH5View::OnDraw(CDC* pDC)
{
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));
	CfRSH5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc) return;
	CRect r;
	GetClientRect(&r);
	
	HDC hdc = pDC->m_hDC;

    FillRect(hdc, r, hbrush);
	
    int i;
    
    for (i = 0, pDoc->Pi = pDoc->FirstPat; (pDoc->Mp[i++] = pDoc->Pi, pDoc->Pi = pDoc->Pi->next); );
    qsort(pDoc->Mp, pDoc->N, sizeof(Particle*), &sortOfZ);
    
    for (i = 0; i < pDoc->N; i++)
    {
        if (FrModInCndDlg.m_rd==1)
        {  
            if (pDoc->Mp[i]->q == 0)
            {
                HPEN hNPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
                HPEN hOPen = (HPEN)SelectObject(hdc, hNPen);
                Arc(hdc, (int)(pDoc->Mp[i]->X), (int)(pDoc->Mp[i]->Y), (int)(pDoc->Mp[i]->X + 10000000 * pDoc->Mp[i]->R), (int)(pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R), (int)((pDoc->Mp[i]->X) / 2), (int)((pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R) / 2), (int)((pDoc->Mp[i]->X) / 2), (int)((pDoc->Mp[i]->Y+ 10000000 * pDoc->Mp[i]->R) / 2));
                DeleteObject(hNPen);
                DeleteObject(hOPen);
            }
            else
                if (pDoc->Mp[i]->q > 0)
                {
                    HPEN hNPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                    HPEN hOPen = (HPEN)SelectObject(hdc, hNPen);
                    Arc(hdc, (int)(pDoc->Mp[i]->X), (int)(pDoc->Mp[i]->Y), (int)(pDoc->Mp[i]->X + 10000000 * pDoc->Mp[i]->R), (int)(pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R), (int)((pDoc->Mp[i]->X) / 2), (int)((pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R) / 2), (int)((pDoc->Mp[i]->X) / 2), (int)((pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R) / 2));
                    DeleteObject(hNPen);
                    DeleteObject(hOPen);
                }
                else
                    if (pDoc->Mp[i]->q < 0)
                    {
                        HPEN hNPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
                        HPEN hOPen = (HPEN)SelectObject(hdc, hNPen);
                        Arc(hdc, (int)(pDoc->Mp[i]->X), (int)(pDoc->Mp[i]->Y), (int)(pDoc->Mp[i]->X + 10000000 * pDoc->Mp[i]->R), (int)(pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R), (int)((pDoc->Mp[i]->X) / 2), (int)((pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R) / 2), (int)((pDoc->Mp[i]->X) / 2), (int)((pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R) / 2));
                        DeleteObject(hNPen);
                        DeleteObject(hOPen);
                    }

        }
        else
        {
            HBRUSH hbrush, hbrushOld;
            if (pDoc->Mp[i]->q == 0)
            {
                hbrush = CreateSolidBrush(RGB(255, 0, 255));
                hbrushOld = (HBRUSH)SelectObject(hdc, hbrush);
                Ellipse(hdc, (int)(pDoc->Mp[i]->X), (int)(pDoc->Mp[i]->Y), (int)(pDoc->Mp[i]->X + 10000000 * pDoc->Mp[i]->R), (int)(pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R));
                DeleteObject(hbrush);
                DeleteObject(hbrushOld);
            }
            else
                if (pDoc->Mp[i]->q > 0)
                {
                    hbrush = CreateSolidBrush(RGB(255, 0, 0));
                    hbrushOld = (HBRUSH)SelectObject(hdc, hbrush);
                    Ellipse(hdc, (int)(pDoc->Mp[i]->X), (int)(pDoc->Mp[i]->Y), (int)(pDoc->Mp[i]->X + 10000000 * pDoc->Mp[i]->R), (int)(pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R));
                    DeleteObject(hbrush);
                    DeleteObject(hbrushOld);
                }
                else
                    if (pDoc->Mp[i]->q < 0)
                    {
                        hbrush = CreateSolidBrush(RGB(0, 0, 255));
                        hbrushOld = (HBRUSH)SelectObject(hdc, hbrush);
                        Ellipse(hdc, (int)(pDoc->Mp[i]->X), (int)(pDoc->Mp[i]->Y), (int)(pDoc->Mp[i]->X + 10000000 * pDoc->Mp[i]->R), (int)(pDoc->Mp[i]->Y + 10000000 * pDoc->Mp[i]->R));
                        DeleteObject(hbrush);
                        DeleteObject(hbrushOld);
                    }
            }

        }

	DeleteObject(r);
	DeleteObject(hbrush);
	DeleteObject(pDoc);
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
