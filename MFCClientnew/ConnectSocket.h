#pragma once
#include"afxsock.h"
class CMFCClientnewDlg;
// CConnSocket ÃüÁîÄ¿±ê

class CConnectSocket : public CSocket
{
public:
	CConnectSocket(CMFCClientnewDlg* dlg = NULL);
	virtual ~CConnectSocket();
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CMFCClientnewDlg* m_dlg;
	CString m_ip;
	UINT m_port;
};

