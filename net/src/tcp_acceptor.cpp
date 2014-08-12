#include "tcp_acceptor.h"

tcp_acceptor::tcp_acceptor(peer_addr& _addr, int _max_listen)
{
    _init(_addr, _max_listen);
}

tcp_acceptor::~tcp_acceptor()
{
    m_socket.close();
}

int tcp_acceptor::accept()
{
    struct sockaddr_in addr = {0};
    socklen_t addr_len = 0;
    return ::accept(m_socket.get_fd(), (sockaddr*)&addr, &addr_len);
}

int tcp_acceptor::_init(peer_addr& _addr, int _max_listen)
{
    if (bind(m_socket.get_fd(), _addr(), sizeof(_addr)) == -1)
    {
        fprintf(stderr, "Acceptor bind address faild! err:%s", strerror(errno));
        return -1;
    }

    if (listen(m_socket.get_fd(), _max_listen) == -1)
    {
        fprintf(stderr, "Acceptor listen faild! err:%s", strerror(errno));
        return -1;
    }
    
    return 0;
}
