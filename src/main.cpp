#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"  

#define WIFI_SSID       "name"
#define WIFI_PASSWORD   "password"
#define SERVER_IP       "255.255.255.255"
#define SERVER_PORT     3404

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
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("failed to connect.\n");
        return 1;
    }
    else
    {
        printf("Connected.\n");
        uint8_t* ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
        printf("IP address %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    }

    int pap = 2137;

    struct udp_pcb* pcb = udp_new();
    ip_addr_t host;
    ipaddr_aton(SERVER_IP, &host);

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, sizeof(int), PBUF_RAM);
    int* req = (int *)p->payload;
    *req = pap;
    err_t er = udp_sendto(pcb, p, &host, SERVER_PORT);
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
