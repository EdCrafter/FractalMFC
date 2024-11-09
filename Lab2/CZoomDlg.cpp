// CZoomDlg.cpp : implementation file
//

#include "pch.h"
#include "Lab2.h"
#include "afxdialogex.h"
#include "CZoomDlg.h"


// CZoomDlg dialog

IMPLEMENT_DYNAMIC(CZoomDlg, CDialogEx)

CZoomDlg::CZoomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOOMDIALOG, pParent)
	, m_scale(0)
{

}

CZoomDlg::~CZoomDlg()
{
}

void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_scale);
}

BEGIN_MESSAGE_MAP(CZoomDlg, CDialogEx)
END_MESSAGE_MAP()

