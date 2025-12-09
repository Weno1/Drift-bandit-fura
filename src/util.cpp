#include "util.hpp"

#include "pico/cyw43_arch.h"
#include "lwip/inet.h"
#include "lwip/netif.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"

#include "config.hpp"

void adc_select_gpio(uint gpio)
{
    if (gpio >= 26 && gpio <= 29)
        adc_select_input(gpio - 26);
}

void configNet(char* ip_s, char* nm_s, char* gw_s)
{
    cyw43_arch_lwip_begin();

    // Parse string IPs into ip4_addr_t and pass pointers to netif_set_addr
    ip4_addr_t ip, nm, gw;
    ip4addr_aton(ip_s, &ip);
    ip4addr_aton(nm_s, &nm);
    ip4addr_aton(gw_s, &gw);

    netif_set_addr(netif_default, &ip, &nm, &gw);
    netif_set_up(netif_default);

    cyw43_arch_lwip_end();
}

void cyw43Init()
{
    if (cyw43_arch_init_with_country(COUNTRY))
        panic("Wi-Fi init failed\n");
}

#ifdef CAR

void initGPIO()
{
    // init adc
    adc_init();
    adc_gpio_init(BATT_V);
    adc_select_gpio(BATT_V);

    //init io
    gpio_init(HEADLIGHTS);
    gpio_set_dir(HEADLIGHTS, GPIO_OUT);
    gpio_init(BRAKELIGHTS);
    gpio_set_dir(BRAKELIGHTS, GPIO_OUT);
    gpio_init(UNDERGLOW_R);
    gpio_set_dir(UNDERGLOW_R, GPIO_OUT);
    gpio_init(UNDERGLOW_G);
    gpio_set_dir(UNDERGLOW_G, GPIO_OUT);
    gpio_init(UNDERGLOW_B);
    gpio_set_dir(UNDERGLOW_B, GPIO_OUT);

    //init pwm outputs
    gpio_set_function(MOTOR_SIG, GPIO_FUNC_PWM);
    gpio_set_function(STER_SIG, GPIO_FUNC_PWM);
    gpio_set_function(AUDIO_SIG, GPIO_FUNC_PWM);

    //init spi
    spi_init(SD_SPI, SD_SPI_SPEED);

    gpio_set_function(SD_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SC_SCK, GPIO_FUNC_SPI);
    gpio_set_function(SD_MOSI, GPIO_FUNC_SPI);

    gpio_init(SD_CS);
    gpio_set_dir(SD_CS, GPIO_OUT);
    gpio_put(SD_CS, 1);
}

uint16_t readBattRaw()
{
    return adc_read();
}

void setupConnection()
{
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");

    if (cyw43_arch_wifi_connect_blocking(PILOT_AP_SSID, PILOT_AP_PASSWD, CYW43_AUTH_WPA2_AES_PSK))
        panic("failed to connect.\n");
    else
        printf("Connected.\n");

    configNet(CAR_IP, NETMASK, GATEWAY);
}

#endif
#ifdef PILOT

void initGPIO()
{
    adc_init();
    adc_gpio_init(THROTLE_INPUT);
    adc_gpio_init(STER_INPUT);

    gpio_init(SW1);
    gpio_set_dir(SW1, GPIO_IN);
    gpio_pull_down(SW1);

    gpio_init(SW2);
    gpio_set_dir(SW2, GPIO_IN);
    gpio_pull_down(SW2);

    gpio_init(SW3);
    gpio_set_dir(SW3, GPIO_IN);
    gpio_pull_down(SW3);

    gpio_init(SW4);
    gpio_set_dir(SW4, GPIO_IN);
    gpio_pull_down(SW4);

    i2c_init(OLED_I2C, OLCD_I2C_SPEED);
    gpio_set_function(OLED_SCL, GPIO_FUNC_I2C);
    gpio_set_function(OLED_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(OLED_SCL);
    gpio_pull_up(OLED_SDA);
}

float rawToBattV(uint16_t x)
{
    return x * (3.3f / 4096.0f) * ((BATT_V_R1 + BATT_V_R2) / BATT_V_R2);
}

void setupAP()
{
    cyw43_arch_enable_ap_mode(PILOT_AP_SSID, PILOT_AP_PASSWD, CYW43_AUTH_WPA2_AES_PSK);

    configNet(PILOT_IP, NETMASK, GATEWAY);
}

#endif