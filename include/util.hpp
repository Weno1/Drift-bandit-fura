#ifndef UTIL_HPP
#define UTIL_HPP

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "lwip/sockets.h"
#include "lwip/pbuf.h"

#include "config.hpp"

struct pack
{
    uint8_t throtle;
    uint8_t yaw;
    uint16_t cmd;
};

struct tlmPack
{
    uint16_t cmd;
    uint16_t rawBattV;
};

void adc_select_gpio(uint gpio);

void configNet(char* ip_s, char* nm_s, char* gw_s);

void cyw43Init();

#ifdef CAR

    void initGPIO();

    uint16_t readBattRaw();

    void setupConnection();

#endif
#ifdef PILOT

    void initGPIO();

    float rawToBattV(uint16_t x);

    void setupAP();

#endif

#endif /* UTIL_HPP */