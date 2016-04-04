#include "stdafx.h"
#include "common.h"
#include "TcpThread.h"
#include "uv.h"
#include "task.h"
typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

static uv_tcp_t tcp_server;
static void echo_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf)
{
	buf->base = (char*)malloc(suggested_size);
	buf->len = (ULONG)suggested_size;

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
	free(wr->buf.base);
	free(wr);
}

static void after_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf)
{ 
	write_req_t *wr;
	uv_shutdown_t* sreq;

	if (nread < 0) {
		free(buf->base);
		sreq = (uv_shutdown_t*)malloc(sizeof* sreq);
		uv_shutdown(sreq, handle, after_shutdown);
		return;
	}

	if (nread == 0) {
		free(buf->base);
		return;
	}

	wr = (write_req_t*)malloc(sizeof *wr);
	wr->buf = uv_buf_init(buf->base, (uint)nread);

	if (uv_write(&wr->req, handle, &wr->buf, 1, after_write)) 
	{
		FATAL("uv_write failed");
	}
}

static void on_connection(uv_stream_t* server, int status)
{
	uv_stream_t* stream;
	stream = (uv_stream_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(uv_default_loop(), (uv_tcp_t*)stream);

	stream->data = server;

	uv_accept(server, stream);
	uv_read_start(stream, echo_alloc, after_read);
}

DWORD WINAPI TcpThreadProc(LPVOID lpParam)
{
	struct sockaddr_in addr;
	uv_ip4_addr("0.0.0.0", TEST_PORT + 1, &addr);
	uv_tcp_init(uv_default_loop(), &tcp_server);
	uv_tcp_bind(&tcp_server, (const struct sockaddr*) &addr, 0);
	uv_listen((uv_stream_t*)&tcp_server, SOMAXCONN, on_connection);
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	return 0;
}

CTcpThread::CTcpThread()
{
	hThead = CreateThread(NULL, 0, TcpThreadProc, NULL, 0, &dwThreadID);
}

CTcpThread::~CTcpThread()
{
}
