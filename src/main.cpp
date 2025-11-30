#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

#include "config.hpp"
#include "util.hpp"


int main()
{
    stdio_init_all();
    printf("Program staring...\n");

    #ifdef CAR      // ----------------- CAR main function -------------------

    // Initialise the Wi-Fi chip
    cyw43Init();

    connectToPilot();

    // ipaddr_aton(PILOT_IP, &host);

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