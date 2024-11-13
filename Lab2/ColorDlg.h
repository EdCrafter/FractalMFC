#pragma once
#include "afxdialogex.h"


// CColorDlg dialog

class CColorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CColorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CMFCColorButton m_colorButton;
public:
	COLORREF m_color;
	afx_msg void OnBnClickedOk();
};
