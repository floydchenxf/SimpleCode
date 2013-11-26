#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "compact.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>


class Connection 
{
public:
    Connection(const char* _ip, ushort _port)
        : m_Port(_port)
    {
        strcpy(m_Ip, _ip);

        m_Scoket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_Scoket == -1)
            std::cerr << "create socket faild!" << std::endl;
    }

    void Run()
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = ::inet_addr(m_Ip);
        addr.sin_port = ntohs(m_Port);
        if (-1 == ::connect(m_Scoket, (const sockaddr*)&addr, sizeof(sockaddr)))
            std::cerr << "connnect error : " << strerror(errno) << std::endl;

        while(true)
        {
			::memset(m_Buf, 0, sizeof(m_Buf));
			std::cin >> m_Buf;
			Send(m_Buf, strlen(m_Buf));

            ::memset(m_Buf, 0, sizeof(m_Buf));
            int rv = ::recv(m_Scoket, m_Buf, sizeof(m_Buf), 0);
            if (rv == -1)
            {
                std::cerr << "recv error : " << strerror(errno) << std::endl;
                break;
            }
            
            if (rv > 0)
                std::cout << "recv content : " << m_Buf << std::endl;
        }
    }

    bool Send(const char* _buf, int _len)
    {
        if (::send(m_Scoket, _buf, _len, 0) == -1)
        {
            std::cerr << "send error : " << strerror(errno) << std::endl;
            return false;
        }

        return true;
    }

private:
    char m_Ip[16];
    ushort m_Port;
    int  m_Scoket;
    char m_Buf[512];
};

#endif
