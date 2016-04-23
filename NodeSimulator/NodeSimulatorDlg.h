
// NodeSimulatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CNodeSimulatorDlg �Ի���
class CNodeSimulatorDlg : public CDialogEx
{
// ����
public:
	CNodeSimulatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NODESIMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	HANDLE hThread = NULL;
	DWORD  dwThreadID;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SendHartPackage();
	afx_msg LRESULT OnUpdateMyData(WPARAM wParam, LPARAM lParam);
	int m_valUid;
	int m_valCount;
};
