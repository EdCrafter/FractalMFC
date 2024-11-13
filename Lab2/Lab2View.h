
// Lab2View.h : interface of the CLab2View class

#pragma once

#include "Lab2Doc.h"
#include "Command.h"
#include "FractalFacade.h"



class CLab2View : public CView //, public CScrollView
{

protected: // create from serialization only
	CLab2View() noexcept;
	DECLARE_DYNCREATE(CLab2View); 
	CLab2Doc* pDoc;
	FractalFacade facade;
	CommandManager commandManager;

// Attributes
public:
	//FractalFacade fractalFacade;
	CLab2Doc* GetDocument() const;


// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	afx_msg void OnFractalKoch();
	afx_msg void OnFractalMand();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnZoomMore();
	afx_msg void OnZoomLess();
	afx_msg void OnZoomEdit();
	afx_msg void OnZoomReset();
	afx_msg void OnColorChange();
};

#ifndef _DEBUG  // debug version in Lab2View.cpp
inline CLab2Doc* CLab2View::GetDocument() const
   { return reinterpret_cast<CLab2Doc*>(m_pDocument); }
#endif

