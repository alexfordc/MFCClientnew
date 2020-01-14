// ConnSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCClientnewDlg.h"
#include "MFCClientnew.h"
#include "ConnectSocket.h"

// CConnSocket

CConnectSocket::CConnectSocket(CMFCClientnewDlg* dlg)
{
	m_dlg = dlg;
}

CConnectSocket::~CConnectSocket()
{
}

BOOL CConnectSocket::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	m_ip = lpszHostAddress;
	m_port = nHostPort;
	return CAsyncSocket::Connect(lpszHostAddress, nHostPort);
}


// CConnSocket ��Ա����

// ���ӷ������ɹ����ú����ᱻ����
void CConnectSocket::OnConnect(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ���׽������Ӳ����Ѿ���ɣ�����˵�������ǳɹ�����ʧ���ˡ�

	CSocket::OnConnect(nErrorCode);
}


void CConnectSocket::OnClose(int nErrorCode)
{
	// �ɿ�ܵ���֪ͨ���׽��֣��������ϵĶ�Ӧ�׽����Ѿ�����ؽ�����ֹ��
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: already close!"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port);
	m_dlg->AddMsg(msg);
	m_dlg->MyEnableBtn();

	this->Close();
	CSocket::OnClose(nErrorCode);
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	// �������ɿ�ܵ��ã�֪ͨ�׽��ֻ����������ݣ����Ե���Receive��Ա����ȡ��
	char recvBuf[512] = { 0 };
	int recvLen = this->Receive(recvBuf, sizeof(recvBuf));
	CString msg;
	SYSTEMTIME t;
	GetLocalTime(&t);
	msg.Format(_T("[%d:%d:%d] %s:%d: %s"), t.wHour, t.wMinute, t.wSecond, m_ip, m_port, CString(recvBuf));
	m_dlg->AddMsg(msg);

	CSocket::OnReceive(nErrorCode);
}
