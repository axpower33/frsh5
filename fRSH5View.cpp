
// fRSH5View.cpp: реализация класса CfRSH5View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "fRSH5.h"
#endif

#include "fRSH5Doc.h"
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

// Рисование CfRSH5View
#define Pprt(a) (*(Particle**)a)
double Dza, Dzb, Ra, Rb;
int sortOfZ(const void* a, const void* b)
{
    /*   Dza = Pprt(a)->Z * (Pprt(a)->Z - CMass[Pprt(a)->agr].Z) / (2 * Zmax);
       Dzb = Pprt(b)->Z * (Pprt(b)->Z - CMass[Pprt(b)->agr].Z) / (2 * Zmax);
       if (Pprt(a)->Z + Dza > Pprt(b)->Z + Dzb) return  1; else
           if (Pprt(a)->Z + Dza < Pprt(b)->Z + Dzb) return -1; else
               return  0;
    */
    if (Pprt(a)->Z > Pprt(b)->Z) return  1; else
        if (Pprt(a)->Z < Pprt(b)->Z) return -1; else
            return  0;
}

Particle** Mp = NULL;
Particle* FirstPat;
Particle* Pi;
Agregat CMass[150];
int Zmax = 640;
int N = 50;
// Рисование CfRSH7View
int ShowPicture(CDC* pDc)
{
    //char st[100];
    double Dzx, Dzy;
    //if (WorkShow) return 1;
    //WorkShow = true;
    //for (El = FirstEl; El != NULL; El = El->Next)
    //{
    //    SetPixel(hdc, El->X , El->Y , RGB(255, 255, 255));
    //}
    int i;
    for (i = 0, Pi = FirstPat; (Mp[i++] = Pi, Pi = Pi->next); );
    qsort(Mp, N, sizeof(Particle*), &sortOfZ);

    for (i = 0; i < N; i++)
    {
        if (Mp[i]->agr != 0)
        {
            Dzx = Mp[i]->Z * (Mp[i]->X - CMass[Mp[i]->agr].X) / (2 * Zmax);
            Dzy = Mp[i]->Z * (Mp[i]->Y - CMass[Mp[i]->agr].Y) / (2 * Zmax);
        }
        else Dzx = Dzy = 0;


        if (Mp[i]->q == 0)
        {
            HPEN hNPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
            HPEN hOPen = (HPEN)pDc->SelectObject(hNPen);
            pDc->Arc((int)(Mp[i]->X + Dzx), (int)(Mp[i]->Y + Dzy), (int)(Mp[i]->X + Dzx + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax), (int)(Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax), (int)((Mp[i]->X + Dzx) / 2), (int)((Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax) / 2), (int)((Mp[i]->X + Dzx) / 2), (int)((Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax) / 2));
            DeleteObject(hNPen);
            DeleteObject(hOPen);
        }
        else
            if (Mp[i]->q > 0)
            {
                HPEN hNPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
                HPEN hOPen = (HPEN)pDc->SelectObject(hNPen);
                pDc->Arc((int)(Mp[i]->X + Dzx), (int)(Mp[i]->Y + Dzy), (int)(Mp[i]->X + Dzx + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax), (int)(Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax), (int)((Mp[i]->X + Dzx) / 2), (int)((Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax) / 2), (int)((Mp[i]->X + Dzx) / 2), (int)((Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax) / 2));
                DeleteObject(hNPen);
                DeleteObject(hOPen);
            }
            else
                if (Mp[i]->q < 0)
                {
                    HPEN hNPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
                    HPEN hOPen = (HPEN)pDc->SelectObject(hNPen);
                    pDc->Arc((int)(Mp[i]->X + Dzx), (int)(Mp[i]->Y + Dzy), (int)(Mp[i]->X + Dzx + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax), (int)(Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax), (int)((Mp[i]->X + Dzx) / 2), (int)((Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax) / 2), (int)((Mp[i]->X + Dzx) / 2), (int)((Mp[i]->Y + Dzy + 5000000 * Mp[i]->R + Mp[i]->Z * Mp[i]->R / Zmax) / 2));
                    DeleteObject(hNPen);
                    DeleteObject(hOPen);
                }

    }

    //WorkShow = false;
    return 1;
}
int xx = 0;

void CfRSH5View::OnDraw(CDC* pDC)
{
	//CfRSH5Doc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;
    xx += 10;
    pDC->Ellipse(100+xx,100,125+xx,125);
    //ShowPicture(pDC);
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

//CfRSH5Doc* CfRSH5View::GetDocument() const // встроена неотлаженная версия
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CfRSH5Doc)));
//	return (CfRSH5Doc*)m_pDocument;
//}
#endif //_DEBUG


// Обработчики сообщений CfRSH5View
