
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
#include "CZoomDlg.h"
#include "ColorDlg.h"

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
	ON_COMMAND(ID_EDIT_UNDO, &CLab2View::OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO1, &CLab2View::OnEditRedo)
	ON_COMMAND(ID_ZOOM_MORE, &CLab2View::OnZoomMore)
	ON_COMMAND(ID_ZOOM_LESS, &CLab2View::OnZoomLess)
	ON_COMMAND(ID_ZOOM_EDIT, &CLab2View::OnZoomEdit)
	ON_COMMAND(ID_ZOOM_RESET, &CLab2View::OnZoomReset)
	ON_COMMAND(ID_COLORD, &CLab2View::OnColorChange)
END_MESSAGE_MAP()

// CLab2View construction/destruction

CLab2View::CLab2View() noexcept : facade(this), commandManager()
{
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
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
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
	pDoc = GetDocument();
	commandManager.ExecuteCommand(std::make_unique<ZoomCommand>(facade, point.x, point.y, pDoc->zoomFactor));
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


void CLab2View::OnEditUndo()
{
	commandManager.Undo();
	Invalidate();
}

void CLab2View::OnEditRedo()
{
	commandManager.Redo();
	Invalidate();
}



void CLab2View::OnZoomMore()
{
	
	pDoc = GetDocument();
	commandManager.ExecuteCommand(std::make_unique<ZoomCommand>(facade, 0, 0, pDoc->zoomFactor,1));
	Invalidate();
}


void CLab2View::OnZoomLess()
{
	pDoc = GetDocument();
	commandManager.ExecuteCommand(std::make_unique<ZoomCommand>(facade, 0, 0, 1/ pDoc->zoomFactor,1));
	Invalidate();
}


void CLab2View::OnZoomEdit()
{
	pDoc = GetDocument();
	CZoomDlg zoomDialog;
	int result = zoomDialog.DoModal();
	if (result == IDOK) {
		CLab2Doc* pDoc = GetDocument();
		pDoc->zoomFactor = zoomDialog.getScale();
	}
}


void CLab2View::OnZoomReset()
{
	facade.Reset();
	commandManager.Clear();
	Invalidate();
}





void CLab2View::OnColorChange()
{
	CColorDlg colorDialog;
	if (colorDialog.DoModal() == IDOK) {
		commandManager.ExecuteCommand(std::make_unique<SetDecoratorCommand>(facade, FractalFacade::Color, colorDialog.m_color));
		Invalidate();
	}
}
