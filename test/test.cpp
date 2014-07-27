#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EVENTS 10
#define PORT 8080

void setnonblocking(int sockfd)
{
	int opts = fcntl(sockfd, F_GETFL);
	if (opts == -1)
	{
		printf("fcntl : %s\n", strerror(errno));
		exit(1);
	}

	opts = (opts | O_NONBLOCK);
	if (fcntl(sockfd, F_SETFL, opts) == -1)
	{
		printf("fcntl : %s\n", strerror(errno));
		exit(1);
	}
}

int  main()
{
	struct epoll_event ev, events[MAX_EVENTS];
	int addrlen, listenfd, conn_sock, nfds, epfd, fd, i, nread, n;
	struct sockaddr_in local, remote;
	char buf[BUFSIZ];

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("sockfd : %s\n", strerror(errno));
		exit(1);
	}

	setnonblocking(listenfd);
	bzero(&local, sizeof(local));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_port = htons(PORT);

	if (bind(listenfd, (struct sockaddr *)&local, sizeof(local)) == -1)
	{
		printf("bind : %s\n", strerror(errno));
		exit(1);
	}

	listen(listenfd, 20);

	epfd = epoll_create(MAX_EVENTS);
	if (epfd == -1)
	{
		printf("epoll_create : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	ev.events = EPOLLIN;
	ev.data.fd = listenfd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
		printf("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			printf("epoll_pwait");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < nfds; ++i) {
			fd = events[i].data.fd;
			if (fd == listenfd) {
				while ((conn_sock = accept(listenfd,(struct sockaddr *) &remote, 
								(socklen_t *)&addrlen)) > 0) {
					setnonblocking(conn_sock);
					ev.events = EPOLLIN | EPOLLET;
					ev.data.fd = conn_sock;
					if (epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock,
								&ev) == -1) {
						printf("epoll_ctl: add");
						exit(EXIT_FAILURE);
					}
				}
				if (conn_sock == -1) {
					if (errno != EAGAIN && errno != ECONNABORTED 
							&& errno != EPROTO && errno != EINTR) 
						printf("accept");
				}
				continue;
			}  
			if (events[i].events & EPOLLIN) {
				n = 0;
				while ((nread = read(fd, buf + n, BUFSIZ-1)) > 0) {
					n += nread;
				}
				if (nread == -1 && errno != EAGAIN) {
					printf("read error");
				}
				ev.data.fd = fd;
				ev.events = events[i].events | EPOLLOUT;
				if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
					printf("epoll_ctl: mod");
				}
			}
			if (events[i].events & EPOLLOUT) {
				sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);
				int nwrite, data_size = strlen(buf);
				n = data_size;
				while (n > 0) {
					nwrite = write(fd, buf + data_size - n, n);
					if (nwrite < n) {
						if (nwrite == -1 && errno != EAGAIN) {
							printf("write error");
						}
						break;
					}
					n -= nwrite;
				}
				close(fd);
			}
		}
	}

	return 0;
}
