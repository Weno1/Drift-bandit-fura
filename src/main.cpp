#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

#include "config.hpp"
#include "util.hpp"
#include "udpSocket.hpp"
#include "Servo.hpp"

int main()
{
    stdio_init_all();
    printf("Program staring...\n");

    // Initialise the Wi-Fi chip
    cyw43Init();

#ifdef CAR          // ----------------- CAR main function ---------------------

    set_sys_clock_khz(CAR_CLOCK_KHZ, true); // change frequency for audio pwm clock division

    initGPIO()

    setupConnection();

    while(true)
    {
        cyw43_arch_poll();

        
    }

#endif              // ------------------------- end ---------------------------
#ifdef PILOT        // ----------------- PILOT main function -------------------
    
    initGPIO();

    setupAP();

    UdpSocket sock;

    sock.bind(PILOT_LISTEN_PORT);

    while(true)
    {
        cyw43_arch_poll();


    }

#endif              // ------------------------- end ---------------------------

    cyw43_arch_deinit();
    return 0;
}