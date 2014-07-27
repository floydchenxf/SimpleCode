#include "tcp_socket.h"

tcp_socket::tcp_socket()
{
    m_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_fd == -1)
        fprintf(stderr, "Create socket faild!, err:%s", strerror(errno));
}

tcp_socket::tcp_socket()
{
    close();
}

int tcp_socket::read(char* _buf, int _size)
{
    return read(m_fd, _buf, _size);
}

int tcp_socket::write(char* _buf, int _size)
{
    return write(m_fd, _buf, _size);
}

int tcp_socket::set_nonblocking()
{
    int opts = 0;
	if ((opts = fcntl(m_fd, F_GETFL)) == -1)
    {
        fprintf(stderr, "fcntl faild!, err:%s", strerror(errno));
        return -1;
    }

	if (fcntl(sockfd, F_SETFL, (opts | O_NONBLOCK)) == -1)
    {
        fprintf(stderr, "fcntl faild!, err:%s", strerror(errno));
        return -1;
    }
    
    return 0;
}

int tcp_socket::set_blocking()
{
    int opts = 0;
	if ((opts = fcntl(m_fd, F_GETFL)) == -1)
    {
        fprintf(stderr, "fcntl faild!, err:%s", strerror(errno));
        return -1;
    }

	if (fcntl(sockfd, F_SETFL, (opts | O_BLOCK)) == -1)
    {
        fprintf(stderr, "fcntl faild!, err:%s", strerror(errno));
        return -1;
    }
    
    return 0;
}

void tcp_socket::close()
{
    if (m_fd != -1)
    {
        closesocket(m_fd);
        shutdown(m_fd);
    }
}