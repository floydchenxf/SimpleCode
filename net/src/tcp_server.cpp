#include "tcp_server.h"

tcp_server::tcp_server(peer_addr& _addr, int _max_listen)
    : m_epoll()
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
        nepfd = m_epoll.epoll_wait(m_events, -1);
        if (nepfd == -1)
        {
            fprintf(stdout, "epoll wait fail, error %d", errno);
            break;
        }

        for (int i = 0; i < nepfd; ++ i)
        {
            if (m_events[i].data.fd == m_acceptor.get_socket().get_fd())
            {
                on_connection();
                //new connection
            }
            else if (m_events[i].events & EPOLLIN)
            {
                on_recv();
                //read data
            }
            else if (m_events[i].events & EPOLLOUT)
            {
                on_send();
                //write data
            }
            else
            {
                fprintf(stdout, "epoll event error!");
                continue;
            }
        }
    }

    return 0;
}
