#pragma once
#include "afxdialogex.h"


// CZoomDlg dialog

class CZoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CZoomDlg)

public:
	CZoomDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CZoomDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP() 

public:
	double m_scale;
	double getScale() { return m_scale; }
};
