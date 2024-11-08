
// Lab2View.cpp : implementation of the CLab2View class
//


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
	ON_COMMAND(ID_FRACTAL_Mand, &CLab2View::OnFractalMand)
END_MESSAGE_MAP()

// CLab2View construction/destruction

CLab2View::CLab2View() noexcept : facade(this)
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
	
	/*CRgn clipRgn;
	CreateRectRgn(0, 0, rect.Width(), rect.Height());
	pDC->SelectClipRgn(&clipRgn);*/

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
	commandManager.ExecuteCommand(std::make_unique<ZoomCommand>(facade, 4));
	commandManager.ExecuteCommand(std::make_unique<MoveCommand>(facade,point.x, point.y,4));
	Invalidate();
}


void CLab2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
}


void CLab2View::OnFractalKoch()
{
	facade.SetFractalType(FractalFactory::Koch);
	Invalidate();
}

void CLab2View::OnFractalMand()
{
	facade.SetFractalType(FractalFactory::Mandelbrot);
	Invalidate();
}
