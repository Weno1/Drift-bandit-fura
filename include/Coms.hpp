#ifndef COMS_HPP
#define COMS_HPP

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "lwip/sockets.h"
#include "lwip/pbuf.h"

#include "config.hpp"

template <typename T>
class Coms
{
    public:

    Coms(ip_addr_t ip);
    Coms(const Coms&) = delete;
	Coms& operator=(const Coms&) = delete;
    ~Coms();

    void send(T data);
    uint16_t getErrorCount();

    private:
    udp_pcb* pcb;

    ip_addr_t targetIp;

    pbuf* sendBuffer = nullptr;
    pbuf* recvBuffer = nullptr;

    uint16_t error_count = 0;
};

#endif /* COMS_HPP */