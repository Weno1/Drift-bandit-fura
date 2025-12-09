#ifndef COMSCLIENT_HPP
#define COMSCLIENT_HPP

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "lwip/sockets.h"
#include "lwip/pbuf.h"

#include "config.hpp"

template <typename T>
class ComsClient
{
public:

    ComsClient(ip_addr_t ip);
    ~ComsClient();

    void send(T data);
    uint16_t getErrorCount();
    void recvCallback();

    bool hasData() { return dataAvailable; }
    T getData() { dataAvailable = false; return lastReceivedData; }

private:
    void staticRecvCallback(void* arg, udp_pcb* pcb, pbuf* p, ip_addr_t* addr, u16_t port);

    void handlePacket(pbuf *p, const ip_addr_t *addr, u16_t port);

    ip_addr_t lastRecivedFrom;
    T lastReceivedData;
    bool dataAvailable = false;

    udp_pcb* pcb;

    ip_addr_t host;

    pbuf* sendBuffer = nullptr;

    uint16_t error_count = 0;
};

#endif /* COMSCLIENT_HPP */