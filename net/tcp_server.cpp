#include "tcp_server.h"

tcp_server::tcp_server(peer_addr& _addr, int _max_listen)
    : m_epoll(MAX_EVENTS)
    , m_acceptor(_addr, _max_listen)
{
}

tcp_server::~tcp_server()
{

}

int tcp_server::server_run()
{
    int nepfd = 0;
    while(1)
    {
        nepfd = m_epoll.wait(m_events, )
    }

    return 0;
}