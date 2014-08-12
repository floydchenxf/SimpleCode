#ifndef _TCP_CONNECTOR_H_
#define _TCP_CONNECTOR_H_

class tcp_connector
{
public:
    tcp_connector();
    ~tcp_connector();

    void connect(peer_addr& addr);
    virtual void on_connected() {}
    virtual void on_read() {}
    virtual void on_recv() {}

private:
    
};

#endif
