#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#define MAX_EVENTS 1000

class tcp_server
{
public:
    tcp_server(peer_addr* _addr, int _max_listen);
    ~tcp_server();

    int server_run();

private:
    epoll_service m_epoll;
    tcp_acceptor  m_acceptor;
    epoll_events  m_events[MAX_EVENTS]
};

#endif