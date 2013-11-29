#ifndef _XSOCKET_H_
#define _XSOCKET_H_

class xsocket
{
public:
    xsocket();
    ~xsocket();

    int read(xbuffer& _buffer);
    int write(xbuffer& _buffer);
    int setoption();
    int setnonblocking();
private:
    int m_socketFd;
};

#endif