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

#include "logging.hpp"

int main()
{
#ifdef CAR
    set_sys_clock_khz(CAR_CLOCK_KHZ, true); // change frequency for audio pwm clock division
#endif

    stdio_init_all();

    #if CURRENT_LOG_LEVEL == LOG_LEVEL_DEBUG
        while (!stdio_usb_connected())
            sleep_ms(100);
    #endif

    LOG_INFO("Program staring...");

#ifdef CAR          // ----------------- CAR main function ---------------------

    LOG_INFO("Role: CAR");

    setupConnection();

    initGPIO();

    Servo motor(MOTOR_SIG);
    Servo ster(STER_SIG);

    motor.write(0);
    ster.write(127);

    motor.enable();
    ster.enable();

    UdpSocket<Pack> sock;

    sock.bind(CAR_LISTEN_PORT);

    uint32_t errCount = 0;

    absolute_time_t lastTlm = get_absolute_time();

    while (true)
    {
        cyw43_arch_poll();

        std::optional<Pack> packOpt = sock.getPacket();

        if (packOpt.has_value())
        {
            motor.write(packOpt->throtle);

            ster.write(packOpt->yaw);

            packOpt.reset();
        }

        if (absolute_time_diff_us(lastTlm, get_absolute_time()) >= TELEMETRY_EVERY_MS)
        {
            TlmPack tlm;

            adcSelectGpio(BATT_V);
            tlm.rawBattV = adc_read();

            tlm.cmd = 0;    // Update required

            bool err = sock.send<TlmPack>(PILOT_IP, PILOT_LISTEN_PORT, tlm);

            errCount += err;

            lastTlm = get_absolute_time();

            LOG_INFO("Telemetry sent");

            if (errCount > 0)
                LOG_WARN("Error count: %lu", errCount);
        }
    }

    sock.close();

#endif              // ------------------------- end ---------------------------
#ifdef PILOT        // ----------------- PILOT main function -------------------
    
    LOG_INFO("Role: PILOT");

    setupAP();

    initGPIO();

    UdpSocket<TlmPack> sock;

    sock.bind(PILOT_LISTEN_PORT);

    float carBatteryVoltage = 0;
    uint32_t errCount = 0;

    absolute_time_t dt = get_absolute_time();

    while (true)
    {
        cyw43_arch_poll();

        Pack pack;

        adcSelectGpio(THROTLE_INPUT);
        pack.throtle = (uint8_t) map(adc_read(), 0, 4095, 0, 255);

        adcSelectGpio(STER_INPUT);
        pack.yaw = (uint8_t) map(adc_read(), 0, 4095, 0, 255);

        pack.cmd = 0;   //update required

        bool err = sock.send<Pack>(CAR_IP, CAR_LISTEN_PORT, pack);
        errCount += err;

        std::optional<TlmPack> TlmPackOpt = sock.getPacket();

        if (TlmPackOpt.has_value())
        {
            carBatteryVoltage = rawToBattV(TlmPackOpt->rawBattV);

            TlmPackOpt.reset();

            LOG_INFO("Car battery voltage: %0.2f", carBatteryVoltage);
        }

        #if CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG
            if (absolute_time_diff_us(dt, get_absolute_time()) >= 1000000 && errCount > 0)
            {
                LOG_ERROR("Send error count: %lu", errCount);

                dt = get_absolute_time();
            }

        #endif

        sleep_ms(1);
    }

    sock.close();

#endif              // ------------------------- end ---------------------------

    cyw43_arch_deinit();
    return 0;
}