#include "ComsClient.hpp"

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "lwip/sockets.h"
#include "lwip/pbuf.h"

#include "config.hpp"

template <typename T>
ComsClient<T>::ComsClient(ip_addr_t ip)
{
    pcb = udp_new();
    host = ip;

    sendBuffer = pbuf_alloc(PBUF_TRANSPORT, sizeof(T), PBUF_RAM);

    udp_bind(pcb, IPADDR_ANY, CAR_LISTEN_PORT);

    udp_recv(pcb, ComsClient<T>::staticRecvCallback, this);
}

template <typename T>
ComsClient<T>::~ComsClient()
{
    udp_remove(pcb);
    pbuf_free(sendBuffer);
}

template <typename T>
void ComsClient<T>::send(T data)
{
    T* p = (T *)sendBuffer->payload;
    *p = data;

    err_t er = udp_sendto(pcb, p, &host, PILOT_LISTEN_PORT);

    if (er != ERR_OK)
        error_count++;
}

template <typename T>
uint16_t ComsClient<T>::getErrorCount()
{
    return error_count;
}

template <typename T>
void ComsClient<T>::staticRecvCallback(void *arg, udp_pcb *pcb, pbuf *p, const ip_addr_t *addr, u16_t port)
{
    ComsClient<T>* self = static_cast<ComsClient<T>*>(arg);
    
    if (self && p)
    {
        self->handlePacket(p, addr, port);
    }
    else if (p)
    {
        // If object is dead but packet arrived, free it immediately
        pbuf_free(p);
    }  
}

template <typename T>
void ComsClient<T>::handlePacket(struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    // pbuf payload might not be contiguous, copy_partial is safest
    if (p->tot_len >= sizeof(T))
    {
        pbuf_copy_partial(p, &lastReceivedData, sizeof(T), 0);
        dataAvailable = true;
    }

    // CRITICAL: Free the pbuf, or lwIP memory will fill up and freeze
    pbuf_free(p);
}
