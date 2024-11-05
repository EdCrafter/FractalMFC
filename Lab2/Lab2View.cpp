
// Lab2View.cpp : implementation of the CLab2View class
//
#include <omp.h>

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab2.h"
#endif

#include "Lab2Doc.h"
#include "Lab2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CLab2View

IMPLEMENT_DYNCREATE(CLab2View, CView)

BEGIN_MESSAGE_MAP(CLab2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLab2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
    ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_FRACTAL_KOCH, &CLab2View::OnFractalKoch)
	ON_COMMAND(ID_FRACTAL_MALD, &CLab2View::OnFractalMald)
END_MESSAGE_MAP()

// CLab2View construction/destruction

CLab2View::CLab2View() noexcept
{
	// TODO: add construction code here

}

CLab2View::~CLab2View()
{
}



BOOL CLab2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	
	return CView::PreCreateWindow(cs);
}

// CLab2View drawing

void CLab2View::OnDraw(CDC* pDC)
{

	CLab2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->SetMapMode(MM_ISOTROPIC);
	CRect rect;
	GetClientRect(&rect);
	/*CRgn clipRgn;
	CreateRectRgn(-8000, -8000 * 1. / pDoc->zoomFactor, 8000 * 1. / pDoc->zoomFactor, 8000 * 1. / pDoc->zoomFactor);
	pDC->SelectClipRgn(&clipRgn);*/

	pDC->SetWindowExt(6000 * 1. / pDoc->zoomFactor, 6000 * 1. / pDoc->zoomFactor);
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(pDoc->centerX, pDoc->centerY);

	facade.Draw(pDC);
}





// CLab2View printing


void CLab2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLab2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLab2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab2View diagnostics

#ifdef _DEBUG
void CLab2View::AssertValid() const
{
	CView::AssertValid();
}

void CLab2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab2Doc* CLab2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab2Doc)));
	return (CLab2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab2View message handlers


void CLab2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CLab2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);

	double scale = 1.4;
	pDoc->zoomFactor *= scale;
	pDoc->centerX = (-point.x + pDoc->centerX) * scale + clientRect.Width() / 2;
	pDoc->centerY = (-point.y + pDoc->centerY) * scale + clientRect.Height() / 2;

	Invalidate();
}

bool CLab2View::IsVisible(CPoint a) {
	CLab2Doc* pDoc = GetDocument();
	CRect clientRect;
	GetClientRect(&clientRect);
	if (clientRect.Width() == 0 || clientRect.Height() == 0) {
		return false;
	}
	double offsetX = pDoc->centerX - clientRect.Width() / 2;
	double offsetY = pDoc->centerY - clientRect.Height() / 2;

	// Обновляем границы видимой области
	offsetX = offsetX / pDoc->zoomFactor;
	offsetY = offsetY / pDoc->zoomFactor;

	CRect visibleRect;
	visibleRect.SetRect(
		(-offsetX - clientRect.Width() * 2), // Левый край
		(offsetY - clientRect.Height() * 2), // Верхний край
		(-offsetX + clientRect.Width() * 2), // Правый край
		(offsetY + clientRect.Height() * 2)  // Нижний край
	);
	return visibleRect.PtInRect(a);
};







void CLab2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CLab2Doc* pDoc = GetDocument();
	if (pDoc) {
		CRect clientRect;
		GetClientRect(&clientRect);
		pDoc->centerX = clientRect.Width() / 2;
		pDoc->centerY = clientRect.Height() / 2;
	
	}
}


void CLab2View::OnFractalKoch()
{
	// TODO: Add your command handler code here
}


void CLab2View::OnFractalMald()
{
	// TODO: Add your command handler code here
}
