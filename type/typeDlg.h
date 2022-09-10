
// typeDlg.h: 头文件
//

#pragma once


// CTypeDlg 对话框
class CTypeDlg : public CDialogEx
{
// 构造
public:
	CTypeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TYPE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDialog dlg;
	CString m_sType;
	CString m_sShow[5];
	HACCEL hAccTable;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClear();
	afx_msg void OnSave();
	afx_msg void OnAbout();
	afx_msg void Bonus();
	afx_msg void OnAuto();
	afx_msg void OnAdd();
	
};
