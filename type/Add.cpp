// AddDlg.cpp: 实现文件
//

#include "pch.h"
#include "type.h"
#include "afxdialogex.h"
#include "Add.h"
#include <fstream>


// AddDlg 对话框

IMPLEMENT_DYNAMIC(AddDlg, CDialogEx)

AddDlg::AddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD, pParent)
	, m_sAddLine(_T(""))
{
}

AddDlg::~AddDlg()
{
}

void AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sAddLine);
}


BEGIN_MESSAGE_MAP(AddDlg, CDialogEx)
END_MESSAGE_MAP()

