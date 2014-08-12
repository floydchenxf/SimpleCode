#ifndef _EPOLL_SERVICE_H_
#define _EPOLL_SERVICE_H_

#define MAX_EVENTS 1000

#include "compact.h"

class epoll_service
{
public:
    epoll_service();
    ~epoll_service();
    
    int epoll_wait(epoll_event* _events, int timeout);
    int epoll_register(int _fd, epoll_event& _events);
    int epoll_modify(int _fd, epoll_event& _events);
    int epoll_delete(int _fd, epoll_event& _events);
private:
    int m_epoll_fd;
    int m_epoll_events[MAX_EVENTS];
};

#endif
