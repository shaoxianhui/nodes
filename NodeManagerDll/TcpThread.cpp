#include "stdafx.h"
#include "common.h"
#include "TcpThread.h"
#include "uv.h"
#include "task.h"
#include "VerificationPackageReq.h"
#include "VerificationPackageAck.h"
#include "VeriCountThread.h"
#include "NodeQueryPackageReq.h"
#include "NodeQueryPackageAck.h"
#include "NodeQueryPackageAckOk.h"
#include "NodeQueryEndPackageAck.h"
#include "NodeQuickQueryPackageReq.h"
#include "NodeQuickQueryEndPackageAck.h"
#include "NodeQuickQueryPackageAckOk.h"
#include "OnOffPackageReq.h"
#include "AllNodes.h"
#include "CommandPackageAck.h"
#include "DisplayPackageReq.h"
#include "NodeInfoWithSocket.h"
extern int cmdPort;
extern void TCPDisplayNodeCmdSend(CDisplayPackageReq* req);
extern void TCPOnOffNodeCmdSend(COnOffPackageReq* req);
typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;
static uv_stream_t* client[100];
static int client_count = 0;
static uv_tcp_t tcp_server;
static uv_loop_t loop;
static uv_timer_t repeat;
static map<string, vector<CTcpTransaction>> allTcpTransactions;
static void echo_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	static char slab[65536];
	buf->base = slab;
	buf->len = sizeof(slab);
}
static void on_close(uv_handle_t* peer)
{
	free(peer);
}

static void after_shutdown(uv_shutdown_t* req, int status)
{
	uv_close((uv_handle_t*)req->handle, on_close);
	free(req);
}
static void after_write(uv_write_t* req, int status)
{
	write_req_t* wr;

	/* Free the read/write buffer and the request */
	wr = (write_req_t*)req;
	free(wr);
}

static void after_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{ 
	uv_shutdown_t* sreq;

	if (nread < 0) {
		sreq = (uv_shutdown_t*)malloc(sizeof* sreq);
		uv_shutdown(sreq, handle, after_shutdown);
		//�������������ӻ���
		for (int i = 0; i < client_count; i++)
		{
			vector<CTcpTransaction>* ts = (vector<CTcpTransaction>*)client[i]->data;
			delete ts;
		}
		client_count = 0;
		return;
	}

	if (nread == 0) {
		//free(buf->base);
		return;
	}

	switch ((uchar)buf->base[2])
	{
		case 0x01:
		{
			uchar r = 0;
			if (CVeriCountThread::GetInstance()->up())
			{
				r = 1;
			}
			CVerificationPackageReq req;
			req.fromBuf(buf->base);
			if (req.valid())
			{
				CVerificationPackageAck ack;
				ack.cert = r;
				write_req_t *wr;
				wr = (write_req_t*)malloc(sizeof *wr);
				wr->buf = uv_buf_init(ack.toBuf(), ack.getSize());

				if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
				{
					FATAL("uv_write failed");
				}
			}
			break;
		}
		case 0x02:
		{
			CNodeQueryPackageReq req;
			req.fromBuf(buf->base);
			if (req.valid())
			{
				CNodeQueryPackageAck acks[36];
				int len = 36;
				int count = 0;
				count = CAllNodes::GetInstance()->getNodeQueryPackageAck(acks, &len);
				for (int i = 0; i < len; i++)
				{
					int buf_len;
					char buf[1024];
					acks[i].toBuf(0, NULL, 0, buf, &buf_len);

					write_req_t *wr;
					wr = (write_req_t*)malloc(sizeof *wr);
					wr->buf = uv_buf_init(buf, acks[i].getSize());
					vector<CTcpTransaction>* ts = (vector<CTcpTransaction>*)handle->data;
					CTcpTransaction t;
					t.type = 0x12;
					t.numFrame = acks[i].numFrame;
					memcpy(t.buffer, buf, acks[i].getSize());
					t.len = acks[i].getSize();
					ts->push_back(t);
					if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
					{
						FATAL("uv_write failed");
					}
				}
				CNodeQueryEndPackageAck ack;
				ack.totalNodeNum = 0;
				write_req_t *wr;
				wr = (write_req_t*)malloc(sizeof *wr);
				wr->buf = uv_buf_init(ack.toBuf(), ack.getSize());

				if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
				{
					FATAL("uv_write failed");
				}
			}
			break;
		}
		case 0x03:
		{
			CNodeQuickQueryPackageReq req;
			req.fromBuf(buf->base);
			if (req.valid())
			{
				CNodeQuickQueryPackageAck acks[4];
				int len = 4;
				int count = 0;
				count = CAllNodes::GetInstance()->getNodeQucikQueryPackageAck(acks, &len);
				if (count > 0)
				{
					for (int i = 0; i < len; i++)
					{
						int buf_len;
						char buf[1024];
						acks[i].toBuf(0, NULL, 0, buf, &buf_len);

						write_req_t *wr;
						wr = (write_req_t*)malloc(sizeof *wr);
						wr->buf = uv_buf_init(buf, acks[i].getSize());
						vector<CTcpTransaction>* ts = (vector<CTcpTransaction>*)handle->data;
						CTcpTransaction t;
						t.type = 0x13;
						t.numFrame = acks[i].numFrame;
						memcpy(t.buffer, buf, acks[i].getSize());
						t.len = acks[i].getSize();
						ts->push_back(t);
						if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
						{
							FATAL("uv_write failed");
						}
					}
				}
				CNodeQuickQueryEndPackageAck ack;
				ack.totalNodeNum = count;
				write_req_t *wr;
				wr = (write_req_t*)malloc(sizeof *wr);
				wr->buf = uv_buf_init(ack.toBuf(), ack.getSize());

				if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
				{
					FATAL("uv_write failed");
				}
			}
			break;
		}
		case 0x04:
		{
			switch ((uchar)buf->base[5])
			{
			case 0x01:
			{
				COnOffPackageReq req;
				req.fromBuf(buf->base);
				if (req.valid())
				{
					CCommandPackageAck ack;
					ack.data = 1;
					write_req_t *wr;
					wr = (write_req_t*)malloc(sizeof *wr);
					wr->buf = uv_buf_init(ack.toBuf(), ack.getSize());

					if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
					{
						FATAL("uv_write failed");
					}
					TCPOnOffNodeCmdSend(&req);
				}
				break;
			}
			case 0x02:
			{
				CDisplayPackageReq req;
				req.fromBuf(buf->base);
				if (req.valid())
				{
					CCommandPackageAck ack;
					ack.data = 1;
					write_req_t *wr;
					wr = (write_req_t*)malloc(sizeof *wr);
					wr->buf = uv_buf_init(ack.toBuf(), ack.getSize());

					if (uv_write(&wr->req, handle, &wr->buf, 1, after_write))
					{
						FATAL("uv_write failed");
					}
					TCPDisplayNodeCmdSend(&req);
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		case 0x12:
		{
			CNodeQueryPackageAckOk req;
			req.fromBuf(buf->base);
			if (req.valid())
			{
				vector<CTcpTransaction>* ts = (vector<CTcpTransaction>*)handle->data;
				vector<CTcpTransaction>::iterator it;
				for (it = ts->begin();it != ts->end();it++) {
					if (it->type == 0x12)
					{
						it->count = 10;
					}
				}
			}
			break;
		}
		case 0x13:
		{
			CNodeQuickQueryPackageAckOk req;
			req.fromBuf(buf->base);
			if (req.valid())
			{
				vector<CTcpTransaction>* ts = (vector<CTcpTransaction>*)handle->data;
				vector<CTcpTransaction>::iterator it;
				for (it = ts->begin();it != ts->end();it++) {
					if (it->type == 0x13)
					{
						it->count = 10;
					}
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

static void on_connection(uv_stream_t* server, int status)
{
	uv_stream_t* stream;
	stream = (uv_stream_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(&loop, (uv_tcp_t*)stream);
	client[client_count++] = stream;
	stream->data = new vector<CTcpTransaction>();
	uv_accept(server, stream);
	uv_read_start(stream, echo_alloc, after_read);
}

static void repeat_cb(uv_timer_t* handle)
{
	for (int i = 0; i < client_count; i++)
	{
		vector<CTcpTransaction>* ts = (vector<CTcpTransaction>*)client[i]->data;
		vector<CTcpTransaction>::iterator it;
		for (it = ts->begin();it != ts->end();) 
		{
			if (it->count < 3)
			{
				write_req_t *wr;
				wr = (write_req_t*)malloc(sizeof *wr);
				wr->buf = uv_buf_init(it->buffer, it->len);

				if (uv_write(&wr->req, client[i], &wr->buf, 1, after_write))
				{
					FATAL("uv_write failed");
				}
				it->count++;
				it++;
			}
			else
			{
				it = ts->erase(it);
			}
		}
	}
}

DWORD WINAPI TcpThreadProc(LPVOID lpParam)
{
	uv_loop_init(&loop);
	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", cmdPort, &addr);
	uv_tcp_init(&loop, &tcp_server);
	uv_tcp_bind(&tcp_server, (const struct sockaddr*)&addr, 0);
	uv_listen((uv_stream_t*)&tcp_server, SOMAXCONN, on_connection);

	uv_timer_init(&loop, &repeat);
	uv_timer_start(&repeat, repeat_cb, 10000, 10000);
	uv_run(&loop, UV_RUN_DEFAULT);
	return 0;
}

CTcpThread::CTcpThread()
{
	hThread = CreateThread(NULL, 0, TcpThreadProc, NULL, 0, &dwThreadID);
}

CTcpThread::~CTcpThread()
{
}
