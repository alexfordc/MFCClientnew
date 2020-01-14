
// MFCClientnewDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ConnectSocket.h"

// CMFCClientnewDlg 对话框
class CMFCClientnewDlg : public CDialogEx
{
// 构造
public:
	CMFCClientnewDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENTNEW_DIALOG };
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
	UINT m_port;
	CButton m_connect;
	CButton m_close;
	CButton m_send;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSend();
	void AddMsg(CString msg);
	void MyEnableBtn();
	CListCtrl m_listCtrl;
	CString m_sendbuf;
	CConnectSocket m_socket;
	CIPAddressCtrl m_ip;
};
