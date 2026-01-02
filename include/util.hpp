#pragma once

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "lwip/sockets.h"
#include "lwip/pbuf.h"

#include "config.hpp"

struct __attribute__((packed)) Pack
{
    uint8_t throtle;
    uint8_t yaw;
    uint16_t cmd;
};

struct __attribute__((packed)) TlmPack
{
    uint16_t rawBattV;
    uint16_t cmd;
};

void adc_select_gpio(uint gpio);

void configNet(char* ip_s, char* nm_s, char* gw_s);

void cyw43Init();

#ifdef CAR

    void initGPIO();

    void setupConnection();

#endif
#ifdef PILOT

    void initGPIO();

    float rawToBattV(uint16_t x);

    void setupAP();

#endif