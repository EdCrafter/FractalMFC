// ColorDlg.cpp : implementation file
//

#include "pch.h"
#include "Lab2.h"
#include "afxdialogex.h"
#include "ColorDlg.h"


// CColorDlg dialog

IMPLEMENT_DYNAMIC(CColorDlg, CDialogEx)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_color = RGB(0, 0, 0);
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_colorButton);
}



BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CColorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CColorDlg message handlers


void CColorDlg::OnBnClickedOk()
{
	m_color = m_colorButton.GetColor();
	CDialogEx::OnOK();
}
