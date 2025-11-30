#include "Coms.hpp"

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "lwip/sockets.h"
#include "lwip/pbuf.h"

#include "config.hpp"

template <typename T>
inline Coms<T>::Coms(ip_addr_t ip)
{
    pcb = udp_new();
    targetIp = ip;

    sendBuffer = pbuf_alloc(PBUF_TRANSPORT, sizeof(T), PBUF_RAM);
}

template <typename T>
Coms<T>::~Coms()
{
    pbuf_free(sendBuffer);
}

template <typename T>
void Coms<T>::send(T data)
{
    T* p = (T *)sendBuffer->payload;
    *p = data;

    err_t er = udp_sendto(pcb, p, &targetIp, PILOT_LISTEN_PORT);

    if (er != ERR_OK)
        error_count++;
}

template <typename T>
uint16_t Coms<T>::getErrorCount()
{
    return error_count;
}
