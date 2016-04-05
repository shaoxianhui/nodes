
// NodeManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NodeManager.h"
#include "NodeManagerDlg.h"
#include "afxdialogex.h"
#include <common.h>
#include <NodeInfo.h>
#include <NodeInfoList.h>
#include <HartPackageAck.h>
#include <NodeQuickQueryPackageAck.h>
#include <Util.h>

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


// CNodeManagerDlg 对话框



CNodeManagerDlg::CNodeManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NODEMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNodeManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CNodeManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNodeManagerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_START, &CNodeManagerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CNodeManagerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_NUM, &CNodeManagerDlg::OnBnClickedButtonNum)
	ON_BN_CLICKED(IDC_BUTTON_INFO, &CNodeManagerDlg::OnBnClickedButtonInfo)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND, &CNodeManagerDlg::OnBnClickedButtonCommand)
END_MESSAGE_MAP()


// CNodeManagerDlg 消息处理程序

BOOL CNodeManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	CRect rect;
	m_list.GetClientRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("UID"), LVCFMT_CENTER, rect.Width() / 38 * 24, 0);
	m_list.InsertColumn(1, _T("手机号"), LVCFMT_CENTER, rect.Width() / 38 * 11, 1);
	m_list.InsertColumn(2, _T("SN"), LVCFMT_CENTER, rect.Width() / 38 * 3, 2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNodeManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNodeManagerDlg::OnPaint()
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
HCURSOR CNodeManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNodeManagerDlg::OnBnClickedOk()
{
	int GPRSPort = 9123;
	int cmdPort = 9124;
	int maxNode = 500;
	uchar sec[128] = { 0x00 };
	InitGPRS(GPRSPort, cmdPort, maxNode, sec);
}


void CNodeManagerDlg::OnBnClickedButtonNum()
{
	uint num;
	NodeNumRequest(&num);
	CString str;
	str.Format("%d", num);
	MessageBox(str);
}


void CNodeManagerDlg::OnBnClickedButtonInfo()
{
	m_list.DeleteAllItems();
	uint num;
	NodeNumRequest(&num);
	if (num > 0)
	{
		CNodeInfoList list;
		list.nodeNum = num;
		list.nodeInfoList = new CNodeInfo[num];
		NodeInfoRequest(&list);
		if (list.nodeNum > 0)
		{
			for (int i = 0; i < list.nodeNum; i++)
			{
				int item = m_list.InsertItem(m_list.GetItemCount(), CUtil::UIDtoString((char*)list.nodeInfoList[i].UID).c_str());
				char temp[12] = { 0x00 };
				memcpy(temp, list.nodeInfoList[i].phoneNum, 11);
				m_list.SetItemText(item, 1, temp);
				memset(temp, 0x00, 12);
				sprintf_s(temp, "%d", list.nodeInfoList[i].SN);
				m_list.SetItemText(item, 2, temp);
			}
		}
	}
}


void CNodeManagerDlg::OnBnClickedButtonStart()
{
	StartGPRS();
}

void CNodeManagerDlg::OnBnClickedButtonStop()
{
	//StopGPRS();
	char buf[1024] = { 0x00 };
	int len = 0;
	CNodeInfo ns[4];
	//CNodeQueryPackageAck ack;
	//ack.newPackage(1, ns, 4, buf, &len);
	//int t = sizeof(MyUnion);
	//CString str;
	//str.Format("%d", len);
	//MessageBox(str);
}


void CNodeManagerDlg::OnBnClickedButtonCommand()
{
	CString str;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			str = m_list.GetItemText(i, 0);
			CNodeInfo node;
			CUtil::StringtoUID(str.GetBuffer(), (char*)node.UID);

			uchar data[1];
			data[0] = 0;
			NodeCmdSend(&node, 1, 1, data);
			AfxMessageBox(str);
		}
	}
}
