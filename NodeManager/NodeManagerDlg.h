
// NodeManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CNodeManagerDlg �Ի���
class CNodeManagerDlg : public CDialogEx
{
// ����
public:
	CNodeManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NODEMANAGER_DIALOG };
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
	CListCtrl m_list;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonNum();
	afx_msg void OnBnClickedButtonInfo();
	afx_msg void OnBnClickedButtonCommand();
	afx_msg void OnBnClickedButtonVeri();
	afx_msg void OnBnClickedButtonNum2();
	afx_msg void OnBnClickedButtonInfo2();
	afx_msg void OnBnClickedButtonCommand2();
	afx_msg void OnBnClickedButtonConn();
	afx_msg void OnBnClickedButtonQuick();
private:
	HANDLE hThead = NULL;
	DWORD  dwThreadID;
};
