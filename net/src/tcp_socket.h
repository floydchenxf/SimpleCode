#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#include "peer_addr.h"

class tcp_socket
{
public:
    tcp_socket();
    ~tcp_socket();

    int read(char* _buf, int _size);
    int write(char* _buf, int _size);    
    int set_nonblocking();
    void close();

    int get_fd(){ return m_fd; }
    void set_addr(peer_addr& _addr) { m_addr = _addr; }
    peer_addr& get_peer_addr(){ return m_addr; }

private:
    int  m_fd;
    peer_addr m_addr;
};

#endif
