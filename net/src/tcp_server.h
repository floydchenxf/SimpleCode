#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#define MAX_EVENTS 1000

#include "compact.h"
#include "peer_addr.h"
#include "epoll_service.h"
#include "tcp_acceptor.h"

class tcp_server
{
public:
    tcp_server(peer_addr& _addr, int _max_listen);
    ~tcp_server();

    int server_run();
    virtual void on_connection() {}
    virtual void on_recv() {}
    virtual void on_send() {}
    virtual void on_close() {}

private:
    epoll_service m_epoll;
    tcp_acceptor m_acceptor;
    epoll_event m_events[MAX_EVENTS];
};

#endif
