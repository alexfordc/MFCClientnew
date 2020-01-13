
// MFCClientnewDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCClientnew.h"
#include "MFCClientnewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCClientnewDlg 对话框



CMFCClientnewDlg::CMFCClientnewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENTNEW_DIALOG, pParent)
	, m_ip(_T(""))
	, m_port(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientnewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_connect);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_close);
	DDX_Control(pDX, IDC_BUTTON_Send, m_send);
}

BEGIN_MESSAGE_MAP(CMFCClientnewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCClientnewDlg::OnBnClickedButtonConnect)
END_MESSAGE_MAP()


// CMFCClientnewDlg 消息处理程序

BOOL CMFCClientnewDlg::OnInitDialog()
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
	SetDlgItemText(IDC_EDIT_IP, _T("127.0.0.1"));//如何解决未定义，设置默认IP地址
	SetDlgItemText(IDC_EDIT_PORT, _T("8080"));//设置默认客户端端口
	UpdateData(FALSE);
	m_close.EnableWindow(FALSE);
	m_send.EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCClientnewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCClientnewDlg::OnPaint()
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
HCURSOR CMFCClientnewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 断开连接
void CMy02_TCPClientDlg::OnBnClickedButton2()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
	m_sendBtn.EnableWindow(FALSE);

	m_connSocket.Close();
}

// 向服务器发送消息
void CMy02_TCPClientDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	USES_CONVERSION;
	//函数T2A和W2A均支持ATL和MFC中的字符
	char * send = T2A(m_sendBuf);
	m_connSocket.Send(send, strlen(send));
}

// 清空消息列表
void CMy02_TCPClientDlg::OnBnClickedButton4()
{
	m_listCtrl.DeleteAllItems();
}

void CMy02_TCPClientDlg::AddMsg(CString msg)
{
	m_listCtrl.InsertItem(0, msg);
}

void CMy02_TCPClientDlg::MyEnableBtn()
{
	m_connBtn.EnableWindow(TRUE);
	m_disConnBtn.EnableWindow(FALSE);
}


void CMFCClientnewDlg::OnBnClickedButtonConnect()//连接TCP服务器
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	BYTE a, b, c, d;
	m_ip.GetAddress(a, b, c, d);
	CString ip;
	ip.Format(_T("%d.%d.%d.%d"), a, b, c, d);
	BOOL ret = m_connSocket.Create();
	if (ret)
	{
		ret = m_connSocket.Connect(ip, m_port);
		if (ret)
		{
			m_connect.EnableWindow(FALSE);
			m_close.EnableWindow(TRUE);
			m_send.EnableWindow(TRUE);
		}
		else
		{
			AfxMessageBox(_T("连接服务器失败"));
			m_connSocket.Close();
		}
	}
	else
	{
		MessageBox(_T("创建套接字失败"));
	}

}
