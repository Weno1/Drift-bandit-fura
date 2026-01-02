#pragma once

#include <string>
#include <cstring>
#include <optional>
#include "pico/cyw43_arch.h"
#include "pico/util/queue.h"
#include "lwip/udp.h"

// T is the struct or data type you want to send/receive
template <typename T>
class UdpSocket {
public:
    explicit UdpSocket(uint queueDepth = 10) : m_pcb(nullptr) {
        queue_init(&m_queue, sizeof(T), queueDepth);
    }

    ~UdpSocket() {
        close();
        queue_free(&m_queue);
    }

    bool bind(uint16_t port)
    {
        if (m_pcb) close();

        cyw43_arch_lwip_begin();
        m_pcb = udp_new();
        
        if (m_pcb)
        {
            err_t err = udp_bind(m_pcb, IP_ADDR_ANY, port);
            if (err == ERR_OK)
            {
                udp_recv(m_pcb, UdpSocket::netCallback, this);
            }
            else
            {
                udp_remove(m_pcb);
                m_pcb = nullptr;
            }
        }
        cyw43_arch_lwip_end();
        return (m_pcb != nullptr);
    }

    void close()
    {
        if (m_pcb)
        {
            cyw43_arch_lwip_begin();
            udp_remove(m_pcb);
            m_pcb = nullptr;
            cyw43_arch_lwip_end();
        }
    }

    bool send(const std::string& targetIp, uint16_t targetPort, const void* data, size_t len)
    {
        if (!m_pcb) return false;

        ip_addr_t destAddr;
        if (!ipaddr_aton(targetIp.c_str(), &destAddr)) return false;

        // Allocate PBUF_RAM for TX
        struct pbuf* p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
        if (!p) return false;

        // Copy data to pbuf
        memcpy(p->payload, data, len);

        cyw43_arch_lwip_begin();
        err_t err = udp_sendto(m_pcb, p, &destAddr, targetPort);
        pbuf_free(p);
        cyw43_arch_lwip_end();

        return (err == ERR_OK);
    }

    template <typename U>
    bool send(const std::string& targetIp, uint16_t targetPort, const U& data)
    {
        return send(targetIp, targetPort, &data, sizeof(U));
    }

    std::optional<T> getPacket()
    {
        if (queue_is_empty(&m_queue))
            return std::nullopt;
        
        T item;

        if (queue_try_remove(&m_queue, &item))
            return item;

        return std::nullopt;
    }

private:
    struct udp_pcb* m_pcb;
    queue_t m_queue;

    static void netCallback(void* arg, struct udp_pcb* pcb, struct pbuf* p, const ip_addr_t* addr, u16_t port)
    {
        if (!p) return;

        auto* self = static_cast<UdpSocket<T>*>(arg);

        if (p->tot_len == sizeof(T))
        {
            T tempItem;

            pbuf_copy_partial(p, &tempItem, sizeof(T), 0);

            queue_try_add(&self->m_queue, &tempItem);
        }

        pbuf_free(p);
    }
};