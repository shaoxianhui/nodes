
// NodeSimulatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NodeSimulator.h"
#include "NodeSimulatorDlg.h"
#include "afxdialogex.h"
#include "uv.h"
#include "task.h"
#include <HartPackageReq.h>
#include <HartPackageAck.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CNodeSimulatorDlg* dlg = NULL;
#define WM_MYUPDATEDATA WM_USER+100  
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CNodeSimulatorDlg �Ի���



CNodeSimulatorDlg::CNodeSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NODESIMULATOR_DIALOG, pParent)
	, m_valUid(0)
	, m_valCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNodeSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UID, m_valUid);
	DDX_Text(pDX, IDC_STATIC_COUNT, m_valCount);
}

BEGIN_MESSAGE_MAP(CNodeSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNodeSimulatorDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MYUPDATEDATA, OnUpdateMyData)
END_MESSAGE_MAP()


// CNodeSimulatorDlg ��Ϣ�������

BOOL CNodeSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	dlg = this;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CNodeSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNodeSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNodeSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//////////////////////////////////////////////////////////////////////////////////////
static uv_udp_t client;
static int hart_count = 0;

static void alloc_cb(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) 
{
	static char slab[65536];
	buf->base = slab;
	buf->len = sizeof(slab);
}

static void cl_recv_cb(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags) 
{
	if (nread <= 0)
		return;
	switch (rcvbuf->base[2])
	{
	case 0x2D:
	{
		CHartPackageAck ack;
		memcpy(&ack, rcvbuf->base, ack.getSize());
		if (ack.valid())
		{
			dlg->m_valCount = hart_count++;
			PostMessage(dlg->m_hWnd, WM_MYUPDATEDATA, NULL, NULL);
		}
		break;
	}
	default:
	{
		break;
	}
	}
}

static void cl_send_cb(uv_udp_send_t* req, int status)
{
	uv_udp_recv_start(req->handle, alloc_cb, cl_recv_cb);
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	CHartPackageReq req1;
	req1.data.UID[0] = ((CNodeSimulatorDlg*)lpParam)->m_valUid;
	req1.fillCheck();
	if (req1.valid() == true)
	{
		struct sockaddr_in addr;
		uv_udp_send_t req;
		uv_buf_t buf;
		uv_ip4_addr("127.0.0.1", TEST_PORT, &addr);
		uv_udp_init(uv_default_loop(), &client);	
		buf = uv_buf_init((char*)&req1, req1.getSize());
		uv_udp_send(&req, &client, &buf, 1, (const struct sockaddr*) &addr, cl_send_cb);
		uv_run(uv_default_loop(), UV_RUN_DEFAULT);
		AfxMessageBox("�߳̽���");
	}
	else
	{
		AfxMessageBox("У�����");
	}
	return 0;
}
void CNodeSimulatorDlg::OnBnClickedOk()
{
	this->UpdateData(TRUE);
	if (hThead == NULL)
	{
		hThead = CreateThread(NULL, 0, ThreadProc, this, 0, &dwThreadID);
		SetTimer(1, 5000, NULL);
	}
	else
	{
		MessageBox("�ڵ��Ѿ�������");
	}
}

void CNodeSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	this->SendHartPackage();
	CDialogEx::OnTimer(nIDEvent);
}

void CNodeSimulatorDlg::SendHartPackage()
{
	this->UpdateData(TRUE);

	struct sockaddr_in addr;
#ifdef _DEBUG
	uv_ip4_addr("118.26.131.14", TEST_PORT, &addr);
#else
	uv_ip4_addr("118.26.131.14", TEST_PORT, &addr);
#endif // _DEBUG
	CHartPackageReq req;
	uv_buf_t buf;
	req.data.UID[0] = m_valUid;
	req.fillCheck();
	buf = uv_buf_init((char*)&req, req.getSize());

	uv_udp_send_t send_req;
	uv_udp_send(&send_req, &client, &buf, 1, (const struct sockaddr*) &addr, cl_send_cb);

	uv_run(uv_default_loop(), UV_RUN_NOWAIT);
}

LRESULT CNodeSimulatorDlg::OnUpdateMyData(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	return 1;
}