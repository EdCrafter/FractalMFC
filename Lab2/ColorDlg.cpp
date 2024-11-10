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

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON1, m_color);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialogEx)
END_MESSAGE_MAP()


// CColorDlg message handlers
