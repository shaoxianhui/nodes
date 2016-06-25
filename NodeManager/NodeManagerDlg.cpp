
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
#include <NodeQueryPackageAck.h>
#include <NodeQueryPackageAckOk.h>
#include <NodeQueryEndPackageAck.h>
#include <NodeQueryPackageReq.h>
#include <Util.h>
#include <CommandPackageReqData.h>
#include <VerificationPackageReq.h>
#include <VerificationPackageAck.h>
#include <uv.h>
#include <task.h>
#include <NodeQuickQueryPackageReq.h>
#include <NodeQuickQueryEndPackageAck.h>
#include <NodeQuickQueryPackageAckOk.h>
#include <OnOffPackageReq.h>
#include <CommandPackageAck.h>
#include <DisplayPackageReq.h>
#include <SwitchPackageReq.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CListCtrl* g_list;
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
	ON_BN_CLICKED(IDC_BUTTON_VERI, &CNodeManagerDlg::OnBnClickedButtonVeri)
	ON_BN_CLICKED(IDC_BUTTON_NUM2, &CNodeManagerDlg::OnBnClickedButtonNum2)
	ON_BN_CLICKED(IDC_BUTTON_INFO2, &CNodeManagerDlg::OnBnClickedButtonInfo2)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND2, &CNodeManagerDlg::OnBnClickedButtonCommand2)
	ON_BN_CLICKED(IDC_BUTTON_CONN, &CNodeManagerDlg::OnBnClickedButtonConn)
	ON_BN_CLICKED(IDC_BUTTON_QUICK, &CNodeManagerDlg::OnBnClickedButtonQuick)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND3, &CNodeManagerDlg::OnBnClickedButtonCommand3)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND4, &CNodeManagerDlg::OnBnClickedButtonCommand4)
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
	m_list.InsertColumn(0, _T("UID"), LVCFMT_CENTER, rect.Width() / 44 * 21, 0);
	m_list.InsertColumn(1, _T("手机号"), LVCFMT_CENTER, rect.Width() / 44 * 11, 1);
	m_list.InsertColumn(2, _T("SN"), LVCFMT_CENTER, rect.Width() / 44 * 4, 2);
	m_list.InsertColumn(3, _T("在线"), LVCFMT_CENTER, rect.Width() / 44 * 4, 3);
	m_list.InsertColumn(4, _T("通信"), LVCFMT_CENTER, rect.Width() / 44 * 4, 4);
	g_list = &m_list;
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
				sprintf_s(temp, "%d", list.nodeInfoList[i].isOnline());
				m_list.SetItemText(item, 3, temp);
				sprintf_s(temp, "%d", list.nodeInfoList[i].isSuccess());
				m_list.SetItemText(item, 4, temp);
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
	StopGPRS();
}
int sw = 0;
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
			CSwitchPackageReq data;
			data.sw = (sw++)%2;
			NodeCmdSend(&node, 1, sizeof(data.sw), (uchar*)&data.sw);
			AfxMessageBox(str);
		}
	}
}

static uv_tcp_t tcp_handle;
static uv_connect_t connect_req;
typedef struct {
  uv_write_t req;
  uv_buf_t buf;
} write_req_t;

static void write_cb(uv_write_t* req, int status) {
	//write_req_t* wr;

	/* Free the read/write buffer and the request */
	//wr = (write_req_t*)req;
	//free(wr->buf.base);
	//free(wr);

	free(req);
}

void CNodeManagerDlg::OnBnClickedButtonVeri()
{
	CVerificationPackageReq req;
	uv_write_t* write_req;
	uv_buf_t buf;

	buf = uv_buf_init(req.toBuf(), req.getSize());
	
	write_req = (uv_write_t*)malloc(sizeof *write_req);
	uv_write(write_req, (uv_stream_t*)&tcp_handle, &buf, 1, write_cb);
}

void CNodeManagerDlg::OnBnClickedButtonNum2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CNodeManagerDlg::OnBnClickedButtonInfo2()
{
	CNodeQueryPackageReq req;
	uv_write_t* write_req;
	uv_buf_t buf;

	buf = uv_buf_init(req.toBuf(), req.getSize());

	write_req = (uv_write_t*)malloc(sizeof *write_req);
	uv_write(write_req, (uv_stream_t*)&tcp_handle, &buf, 1, write_cb);
}

void CNodeManagerDlg::OnBnClickedButtonCommand2()
{
	CString str;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			str = m_list.GetItemText(i, 0);
			COnOffPackageReq req;
			COnOffPackageData nodes[1];
			char buf[1024];
			CUtil::StringtoUID(str.GetBuffer(), (char*)nodes[0].UID);
			nodes[0].sw = (sw++) % 2;
			int len = 0;
			uv_write_t* write_req;
			uv_buf_t write_buf;
			req.toBuf(nodes, 1, buf, &len);
			write_buf = uv_buf_init(buf, len);

			write_req = (uv_write_t*)malloc(sizeof *write_req);
			uv_write(write_req, (uv_stream_t*)&tcp_handle, &write_buf, 1, write_cb);
			AfxMessageBox(str);
		}
	}
}

static void echo_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	static char slab[65536];
	buf->base = slab;
	buf->len = sizeof(slab);
}

static void after_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{
	int offset = 0;
	while (nread - offset > 0)
	{
		switch ((uchar)buf->base[offset + 2])
		{
		case 0xF1:
		{
			CVerificationPackageAck ack;
			ack.fromBuf(buf->base + offset);
			if (ack.valid())
			{
				CString str;
				str.Format("%d", ack.cert);
				AfxMessageBox(str);
			}
			offset += ack.getSize();
			break;
		}
		case 0xF2:
		{
			if (((uchar)buf->base[offset + 5]) == 0xFF && ((uchar)buf->base[offset + 6]) == 0xFF)
			{
				CNodeQueryEndPackageAck ack;
				ack.fromBuf(buf->base + offset);
				if (ack.valid())
				{
					CString str;
					str.Format("%d", ack.getSize());
					//AfxMessageBox(str);
				}
				offset += ack.getSize();
			}
			else
			{
				CNodeQueryPackageAck ack;
				ack.fromBuf(buf->base + offset);
				if (ack.valid())
				{
					uint num = ack.getCount();
					g_list->DeleteAllItems();
					if (num > 0)
					{
						for (int i = 0; i < num; i++)
						{
							int item = g_list->InsertItem(g_list->GetItemCount(), CUtil::UIDtoString((char*)ack.data[i].UID).c_str());
							char temp[12] = { 0x00 };
							memcpy(temp, ack.data[i].phoneNum, 11);
							g_list->SetItemText(item, 1, temp);
							memset(temp, 0x00, 12);
							sprintf_s(temp, "%d", ack.data[i].SN);
							g_list->SetItemText(item, 2, temp);
							sprintf_s(temp, "%d", ack.data[i].isOnline());
							g_list->SetItemText(item, 3, temp);
							sprintf_s(temp, "%d", ack.data[i].isSuccess());
							g_list->SetItemText(item, 4, temp);
						}
					}
					CString str;
					str.Format("%d", ack.getSize());
					//AfxMessageBox(str);
					CNodeQueryPackageAckOk ok;
					ok.numFrame = ack.numFrame;
					uv_write_t* write_req;
					uv_buf_t buf;

					buf = uv_buf_init(ok.toBuf(), ok.getSize());

					write_req = (uv_write_t*)malloc(sizeof *write_req);
					uv_write(write_req, (uv_stream_t*)&tcp_handle, &buf, 1, write_cb);
				}
				offset += ack.getSize();
			}
			break;
		}
		case 0xF3:
		{
			if (((uchar)buf->base[offset + 5]) == 0xFF && ((uchar)buf->base[offset + 6]) == 0xFF)
			{
				CNodeQuickQueryEndPackageAck ack;
				ack.fromBuf(buf->base + offset);
				if (ack.valid())
				{
					CString str;
					str.Format("%d", ack.totalNodeNum);
					AfxMessageBox(str);
				}
				offset += ack.getSize();
			}
			else
			{
				CNodeQuickQueryPackageAck ack;
				ack.fromBuf(buf->base + offset);
				if (ack.valid())
				{
					CString str;
					str.Format("%d", ack.getSize());
					AfxMessageBox(str);
					CNodeQuickQueryPackageAckOk ok;
					ok.numFrame = ack.numFrame;
					uv_write_t* write_req;
					uv_buf_t buf;

					buf = uv_buf_init(ok.toBuf(), ok.getSize());

					write_req = (uv_write_t*)malloc(sizeof *write_req);
					uv_write(write_req, (uv_stream_t*)&tcp_handle, &buf, 1, write_cb);
				}
				offset += ack.getSize();
			}
			break;
		}
		case 0xF4:
		{
			CCommandPackageAck ack;
			ack.fromBuf(buf->base + offset);
			if (ack.valid())
			{
				CString str;
				str.Format("%d", ack.data);
				AfxMessageBox(str);
			}
			offset += ack.getSize();
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

static void connect_cb(uv_connect_t* conn_req, int status)
{
	uv_read_start((uv_stream_t*)&tcp_handle, echo_alloc, after_read);
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	struct sockaddr_in addr;
	uv_ip4_addr("127.0.0.1", TEST_PORT + 1, &addr);

	uv_tcp_init(uv_default_loop(), &tcp_handle);
	uv_tcp_connect(&connect_req, &tcp_handle, (const struct sockaddr*) &addr, connect_cb);
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);

	AfxMessageBox("线程结束");
	return 0;
}
void CNodeManagerDlg::OnBnClickedButtonConn()
{
	hThread = CreateThread(NULL, 0, ThreadProc, this, 0, &dwThreadID);
}

void CNodeManagerDlg::OnBnClickedButtonQuick()
{
	CNodeQuickQueryPackageReq req;
	uv_write_t* write_req;
	uv_buf_t buf;

	buf = uv_buf_init(req.toBuf(), req.getSize());

	write_req = (uv_write_t*)malloc(sizeof *write_req);
	uv_write(write_req, (uv_stream_t*)&tcp_handle, &buf, 1, write_cb);
}


void CNodeManagerDlg::OnBnClickedButtonCommand3()
{
	CString str;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			str = m_list.GetItemText(i, 0);
			CNodeInfo node;
			CUtil::StringtoUID(str.GetBuffer(), (char*)node.UID);
			CCommandPackageReqData data;
			data.dispNum = sw;
			data.validNum = 3;
			NodeCmdSend(&node, 2, sizeof(data), (uchar*)&data);
			AfxMessageBox(str);
		}
	}
}


void CNodeManagerDlg::OnBnClickedButtonCommand4()
{
	CString str;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			str = m_list.GetItemText(i, 0);
			CDisplayPackageReq req;
			int len = 0;
			uv_write_t* write_req;
			uv_buf_t write_buf;
			char buf[1024];
			CDisplayPackageReqData nodes[1];
			//memset(nodes[0].UID, 0, 12);
			CUtil::StringtoUID(str.GetBuffer(), (char*)nodes[0].UID);
			nodes[0].disp.dispNum = sw;
			nodes[0].disp.validNum = 3;
			req.toBuf(nodes, 1, buf, &len);
			write_buf = uv_buf_init(buf, len);

			write_req = (uv_write_t*)malloc(sizeof *write_req);
			uv_write(write_req, (uv_stream_t*)&tcp_handle, &write_buf, 1, write_cb);
			AfxMessageBox(str);
		}
	}
}
