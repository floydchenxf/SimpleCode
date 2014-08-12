#include "epoll_service.h"

epoll_service::epoll_service()
{
    if ((m_epoll_fd = epoll_create(MAX_EVENTS)) == -1)
        fprintf(stderr, "Create epoll service faild! err:%s\n", strerror(errno));
}

epoll_service::~epoll_service()
{

}

int epoll_service::epoll_wait(epoll_event* _events, int timeout)
{
    return ::epoll_wait(m_epoll_fd, _events, MAX_EVENTS, timeout);
}

int epoll_service::epoll_register(int _fd, epoll_event& _events)
{
    return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, _fd, &_events);
}

int epoll_service::epoll_modify(int _fd, epoll_event& _events)
{
    return epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, _fd, &_events);
}

int epoll_service::epoll_delete(int _fd, epoll_event& _events)
{
    return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, _fd, &_events);
}
