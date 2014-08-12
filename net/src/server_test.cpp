#include "compact.h"
#include "tcp_server.h"

int main(int argc, char* argv[])
{
    peer_addr addr("127.0.0.1", 5000);
    tcp_server server(addr, 1000);
    server.server_run();

    return 0;
}
