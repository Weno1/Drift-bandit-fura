#include "networking.hpp"

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"

#include "config.hpp"

void wifiStaticConfig(char* ip_s, char* nm_s, char* gw_s)
{
    cyw43_arch_lwip_begin();

    // Parse string IPs into ip4_addr_t and pass pointers to netif_set_addr
    ip4_addr_t ip, nm, gw;
    ip4addr_aton(ip_s, &ip);
    ip4addr_aton(nm_s, &nm);
    ip4addr_aton(gw_s, &gw);

    netif_set_addr(netif_default, &ip, &nm, &gw);

    cyw43_arch_lwip_end();
}

void wifiInit()
{
    if (cyw43_arch_init_with_country(COUNTRY))
        panic("Wi-Fi init failed\n");
}

void connectToPilot()
{
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");

    if (cyw43_arch_wifi_connect_blocking(PILOT_AP_SSID, PILOT_AP_PASSWD, CYW43_AUTH_WPA2_AES_PSK))
        panic("failed to connect.\n");
    else
        printf("Connected.\n");
}

pbuf* allocBuffer()
{
    return pbuf_alloc(PBUF_TRANSPORT, sizeof(pack), PBUF_RAM);
}
    