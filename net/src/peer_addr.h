#ifndef _PEER_ADDR_H_
#define _PEER_ADDR_H_

#include "compact.h"

class peer_addr
{
public:
    peer_addr()
    {

    }
    peer_addr(const char* _ip, ushort _port, ushort _family = AF_INET)
    {
        m_addr.sin_family = _family;
        m_addr.sin_addr.s_addr = ::inet_addr(_ip);
        m_addr.sin_port = ::htons(_port);
    }

    peer_addr(const struct sockaddr_in& _sock_addr)
    {
        m_addr = _sock_addr;
    }

    sockaddr* operator()()
    {
        return (sockaddr*)&m_addr;
    }

    const char* Ip() 
    {
        return inet_ntoa(m_addr.sin_addr);
    }

    const ushort Port()
    {
        return ::ntohs(m_addr.sin_port);
    }
private:
    struct sockaddr_in m_addr;
};

#endif
