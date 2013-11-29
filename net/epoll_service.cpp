#include "epoll_service.h"

epoll_service::epoll_service()
{
    if ((m_fd = epoll_create(MAX_EVENTS)) == -1)
        fprintf(stderr, "Create epoll service faild! err:%s\n", strerror(errno));
}

epoll_service::~epoll_service()
{

}

int epoll_service::wait(int _fd, epoll_event* _events, int timeout)
{
    epoll_wait(epfd, events, m_max_events, timeout);
}

int epoll_service::register(int _fd, epoll_event& _events)
{
    return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, _fd, &_events);
}

int epoll_service::modify(int _fd, epoll_event& _events)
{
    return epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, _fd, &_events);
}

int epoll_service::delete(int _fd, epoll_event& _events)
{
    return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, _fd, &_events);
}