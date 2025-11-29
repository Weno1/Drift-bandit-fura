#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"

#include "config.hpp"

struct pack
{
    uint8_t throtle;
    uint8_t yaw;
    uint16_t cmd;
};

void wifiStaticConfig(char* ip_s, char* nm_s, char* gw_s);

void wifiInit();

void connectToPilot();

class communication
{
    public:

    private:

    pbuf* buffer;
};
