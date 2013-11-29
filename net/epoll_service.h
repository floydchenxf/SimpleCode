#ifndef _EPOLL_SERVICE_H_
#define _EPOLL_SERVICE_H_

#define MAX_EVENTS 1000

class epoll_service
{
public:
    epoll_service();
    ~epoll_service();
    
    int wait(int _fd, epoll_event& _events, int timeout);
    int register(int _fd, epoll_event& _events);    
    int modify(int _fd, epoll_event& _events);
    int delete(int _fd, epoll_event& _events);
private:
    int m_epoll_fd;
    int m_epoll_events[MAX_EVENTS];
};

#endif