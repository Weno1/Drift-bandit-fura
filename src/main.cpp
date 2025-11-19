#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

#include "config.hpp"

void wifi_static_config() {
    cyw43_arch_lwip_begin();

    // Parse string IPs into ip4_addr_t and pass pointers to netif_set_addr
    ip4_addr_t ip, nm, gw;
    ip4addr_aton(CAR_IP, &ip);
    ip4addr_aton(NETMASK, &nm);
    ip4addr_aton(GATEWAY, &gw);

    netif_set_addr(
        netif_default,
        &ip,
        &nm,
        &gw);

    cyw43_arch_lwip_end();
}

int main()
{
    stdio_init_all();
    sleep_ms(8000);
    printf("Program staring...\n");

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(PILOT_AP_SSID, PILOT_AP_PASSWD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("failed to connect.\n");
        return 1;
    }
    else
    {
        printf("Connected.\n");
    }

    int pap = 2137;

    struct udp_pcb* pcb = udp_new();
    ip_addr_t host;
    ipaddr_aton(PILOT_IP, &host);

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, sizeof(int), PBUF_RAM);
    int* req = (int *)p->payload;
    *req = pap;
    err_t er = udp_sendto(pcb, p, &host, PILOT_LISTEN_PORT);
    pbuf_free(p);

    if (er != ERR_OK)
    {
        printf("Failed to send UDP packet! error=%d", er);
    }

    while(true)
    {
        cyw43_arch_poll();
        sleep_ms(1000);
    }
    
    cyw43_arch_deinit();
    return 0;
}
