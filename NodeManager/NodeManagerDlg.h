
// NodeManagerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CNodeManagerDlg 对话框
class CNodeManagerDlg : public CDialogEx
{
// 构造
public:
	CNodeManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NODEMANAGER_DIALOG };
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
