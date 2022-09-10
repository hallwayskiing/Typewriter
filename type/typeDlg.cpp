
// typeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "type.h"
#include "typeDlg.h"
#include "afxdialogex.h"
#include "Add.h"
#include <fstream>
#include <string>
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	virtual void OnCancel();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	this->Create(IDD_ABOUTBOX);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::OnCancel()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CTypeDlg 对话框



CTypeDlg::CTypeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TYPE_DIALOG, pParent)
	, m_sType(_T(""))
	, m_sShow()
	, hAccTable()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON);
}

void CTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TYPE, m_sType);
	DDX_Text(pDX, IDC_SHOW1, m_sShow[0]);
	DDX_Text(pDX, IDC_SHOW2, m_sShow[1]);
	DDX_Text(pDX, IDC_SHOW3, m_sShow[2]);
	DDX_Text(pDX, IDC_SHOW4, m_sShow[3]);
	DDX_Text(pDX, IDC_SHOW5, m_sShow[4]);
}

BEGIN_MESSAGE_MAP(CTypeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_CLEAR, &CTypeDlg::OnClear)
	ON_COMMAND(ID_SAVE, &CTypeDlg::OnSave)
	ON_COMMAND(ID_ABOUT, &CTypeDlg::OnAbout)
	ON_COMMAND(ID_AUTO, &CTypeDlg::OnAuto)
	ON_COMMAND(ID_ADD, &CTypeDlg::OnAdd)
END_MESSAGE_MAP()


// CTypeDlg 消息处理程序

BOOL CTypeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	setlocale(LC_CTYPE, "chs");
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);
	hAccTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTypeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTypeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTypeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CTypeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_TYPE)
		{
			UpdateData(TRUE);
			Bonus();
			for (int i = 4; i > 0; i--)
				m_sShow[i] = m_sShow[i - 1];
			m_sShow[0] = m_sType;
			m_sType.Empty();
			UpdateData(FALSE);
		}
		return true;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return true;
	}

	if (TranslateAccelerator(GetSafeHwnd(), hAccTable, pMsg))
	{
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTypeDlg::OnClear()
{
	// TODO: 在此添加命令处理程序代码
	for (int i = 0; i < 5; i++)
		m_sShow[i].Empty();
	m_sType.Empty();
	UpdateData(FALSE);
}


void CTypeDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CDialog *pMyAbout=new CAboutDlg;
	pMyAbout->ShowWindow(SW_SHOW);
}

void CTypeDlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	using namespace std;
	string str;
	ifstream inFile("D:\\YourPoem.txt");
	fstream tmp("D:\\Temp\\type_temp.dat", ios::out | ios::ate);
	tmp << inFile.rdbuf();
	inFile.close();
	tmp.close();
	tmp.open("D:\\Temp\\type_temp.dat", ios::in);
	ofstream outFile("D:\\YourPoem.txt", ios::ate);
	bool isEmpty = true;
	for (int i = 4; i >= 0; i--)
	{
		str = CStringA(m_sShow[i]);
		if (!str.empty())
		{
			outFile << str.c_str() << endl;
			isEmpty = false;
		}
	}
	if (!isEmpty)
		outFile << endl;
	outFile << tmp.rdbuf();
	outFile.close();
	tmp.close();
	ShellExecute(NULL, NULL, L"D:\\YourPoem.txt", NULL, NULL, SW_SHOWNORMAL);
	DeleteFile(L"D:\\Temp\\type_temp.dat");
	OnClear();
}
void CTypeDlg::Bonus()
{
	using namespace std;
	map<string, int>match =
	{
		{"close",1},
		{"secret",2},
		{"suicide",3},
		{"happy",4}
	};
	string tmp = CStringA(m_sType);
	switch (match[tmp])
	{
	case 1:
		SendMessage(WM_CLOSE);
		break;
	case 2:
		MessageBox(L"I LOVE YOU", L"Bonus");
		break;
	case 3:
		MessageBox(L"CALL ME IF YOU GET LOST", L"Bonus");
		break;
	case 4:
		MessageBox(L"HAVE A GOOD DAY!", L"Bonus");
		break;
	}
}


void CTypeDlg::OnAuto()
{
	// TODO: 在此添加命令处理程序代码
	using namespace std;

    OnClear();
	CStdioFile inFile;
	CString fileLocation = L"D:\\Auto.txt";
	inFile.Open(fileLocation, CFile::modeRead);
	CString tmp;
	int fileLineNum = 0;
	while (inFile.ReadString(tmp))
		fileLineNum++;
	for (int i = 0; i < 5; i++)
	{	
		while(1)
		{
			inFile.SeekToBegin();
			srand(clock()+rand());
			int rndLine = rand()%fileLineNum + 1;
			for (int j = 0; j <rndLine; j++)
				inFile.ReadString(tmp);
			if (tmp != m_sShow[0] && tmp != m_sShow[1] && tmp != m_sShow[2] && tmp != m_sShow[3] && tmp != m_sShow[4])
			{
				m_sShow[i] = tmp;
				break;
			}
		}
	}
	UpdateData(false);
}


void CTypeDlg::OnAdd()
{
	// TODO: 在此添加命令处理程序代码
	AddDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		UpdateData(true);
		if (!dlg.m_sAddLine.IsEmpty())
		{
			std::ofstream outFile("D:\\Auto.txt", std::ios::app);
			outFile << '\n' << CStringA(dlg.m_sAddLine);
			outFile.close();
			MessageBox(L"Success!");
		}
	}
	else
	{
		
	}
}
