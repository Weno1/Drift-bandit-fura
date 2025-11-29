#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

#include "config.hpp"
#include "networking.hpp"


int main()
{
    stdio_init_all();
    printf("Program staring...\n");

    #ifdef CAR      // ----------------- CAR main function -------------------

    // Initialise the Wi-Fi chip
    wifiInit();

    connectToPilot();

    // int pap = 2137;

    // struct udp_pcb* pcb = udp_new();
    // ip_addr_t host;
    // ipaddr_aton(PILOT_IP, &host);

    // struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, sizeof(int), PBUF_RAM);
    // int* req = (int *)p->payload;
    // *req = pap;
    // err_t er = udp_sendto(pcb, p, &host, PILOT_LISTEN_PORT);
    // pbuf_free(p);

    // if (er != ERR_OK)
    // {
    //     printf("Failed to send UDP packet! error=%d", er);
    // }

    while(true)
    {
        cyw43_arch_poll();
    }

    #endif              // ----------------- end -------------------
    #ifdef PILOT        // ----------------- PILOT main function -------------------
    
    while(true)
    {
        cyw43_arch_poll();
    }

    #endif              // ----------------- end -------------------

    cyw43_arch_deinit();
    return 0;
}