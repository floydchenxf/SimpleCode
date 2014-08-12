#ifndef _TCP_ACCEPTOR_H_
#define _TCP_ACCEPTOR_H_

#include "tcp_socket.h"

class tcp_acceptor
{
public:
    tcp_acceptor(peer_addr& _addr, int _max_listen);
    ~tcp_acceptor();

    int accept();
    
    tcp_socket& get_socket() { return m_socket; }

private:
    int _init(peer_addr& _addr, int _max_listen);
private:
    tcp_socket m_socket;
};

#endif
