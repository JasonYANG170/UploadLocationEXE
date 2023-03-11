
// windows-YANG-programDlg.h: 头文件
//

#pragma once


// CwindowsYANGprogramDlg 对话框
class CwindowsYANGprogramDlg : public CDialogEx
{
// 构造
public:

	CString UTF8ToUnicode2(char* UTF8);

	CwindowsYANGprogramDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWSYANGPROGRAM_DIALOG };
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

	CButton PowerBootButton;


	afx_msg void OnBnClickedPowerboot();
	afx_msg void OnBnClickedButton5();
};
