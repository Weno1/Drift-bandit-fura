#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"

#include "config.hpp"
#include "util.hpp"
#include "udpSocket.hpp"
#include "Servo.hpp"

int main()
{
#ifdef CAR
    set_sys_clock_khz(CAR_CLOCK_KHZ, true); // change frequency for audio pwm clock division
#endif

    stdio_init_all();
    printf("Program staring...\n");

    // Initialise the Wi-Fi chip
    cyw43Init();

#ifdef CAR          // ----------------- CAR main function ---------------------

    initGPIO();

    setupConnection();

    Servo motor(MOTOR_SIG);
    Servo ster(STER_SIG);

    motor.write(0);
    ster.write(127);

    motor.enable();
    ster.enable();

    UdpSocket<Pack> sock;

    sock.bind(CAR_LISTEN_PORT);

    absolute_time_t lastTlm = get_absolute_time();

    while (true)
    {
        cyw43_arch_poll();

        auto packOpt = sock.getPacket();

        if (packOpt.has_value())
        {
            motor.write(packOpt->throtle);

            ster.write(packOpt->yaw);

            packOpt.reset();
        }

        if (absolute_time_diff_us(lastTlm, get_absolute_time()) >= TELEMETRY_EVERY_US)
        {
            TlmPack tlm;

            adc_select_gpio(BATT_V);
            tlm.rawBattV = adc_read();

            tlm.cmd = 0;    // Update required

            sock.send<TlmPack>(PILOT_IP, PILOT_LISTEN_PORT, tlm);
        }
    }

#endif              // ------------------------- end ---------------------------
#ifdef PILOT        // ----------------- PILOT main function -------------------
    
    initGPIO();

    setupAP();

    UdpSocket<TlmPack> sock;

    sock.bind(PILOT_LISTEN_PORT);

    while (true)
    {
        cyw43_arch_poll();

        Pack pack;

        adc_select_gpio(THROTLE_INPUT);
        pack.throtle = (uint8_t) map(adc_read(), 0, 4095, 0, 255);

        adc_select_gpio(STER_INPUT);
        pack.yaw = (uint8_t) map(adc_read(), 0, 4095, 0, 255);

        pack.cmd = 0;   //update required

        bool err = sock.send<Pack>(CAR_IP, CAR_LISTEN_PORT, pack);
    }

#endif              // ------------------------- end ---------------------------

    cyw43_arch_deinit();
    return 0;
}