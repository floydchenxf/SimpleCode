all: server

server : server_test.o tcp_server.o epoll_service.o tcp_acceptor.o tcp_socket.o
	g++ server_test.o tcp_server.o epoll_service.o tcp_acceptor.o tcp_socket.o  -o server

server_test.o: server_test.cpp tcp_server.h
	g++ -c server_test.cpp

tcp_server.o: tcp_server.cpp tcp_server.h tcp_acceptor.h epoll_service.h peer_addr.h
	g++ -c tcp_server.cpp

epoll_service.o : epoll_service.cpp epoll_service.h
	g++ -c epoll_service.cpp

tcp_acceptor.o : tcp_acceptor.cpp tcp_acceptor.h tcp_socket.h
	g++ -c tcp_acceptor.cpp
	
tcp_socket.o : tcp_socket.cpp tcp_socket.h
	g++ -c tcp_socket.cpp

clean:
	rm -rf *.o server
