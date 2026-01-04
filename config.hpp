#pragma once

/*****************************

DEVICE SELECTION

*****************************/

#define PILOT
//#define CAR

/*****************************

CAR PIN CONFIGURATION

*****************************/

#define MOTOR_SIG                   0
#define STER_SIG                    1

#define HEADLIGHTS                  2
#define BRAKELIGHTS                 3
#define UNDERGLOW_R                 20
#define UNDERGLOW_G                 21
#define UNDERGLOW_B                 22

#define SD_SPI                      spi0
#define SD_MISO                     16
#define SD_CS                       17
#define SC_SCK                      18
#define SD_MOSI                     19

#define AUDIO_SIG                   15

#define BATT_V                      26

/*****************************

PILOT PIN CONFIGURATION

*****************************/

#define THROTLE_INPUT               26
#define STER_INPUT                  27

#define SW1                         0
#define SW2                         1
#define SW3                         2
#define SW4                         3

#define OLED_I2C                    i2c0
#define OLED_SDA                    16
#define OLED_SCL                    17

/*****************************

WIRELESS CONNECTION CONFIG

*****************************/

#define COUNTRY                     CYW43_COUNTRY_POLAND

#define PILOT_AP_SSID               "Drift-Bandit-Fura"
#define PILOT_AP_PASSWD             "N6znW5<x@D,0ki(tkWR£'4_!&0TK{(w'[4p1s8A+pBID.g9CpL" //Random generated password, you can set your own.

#define PILOT_LISTEN_PORT           3404
#define CAR_LISTEN_PORT             59000

#define PILOT_IP                    (char*) "192.168.4.1"
#define CAR_IP                      (char*) "192.168.4.2"

#define NETMASK                     (char*) "255.255.255.0"
#define GATEWAY                     PILOT_IP

/*****************************

ADVANCED CONFIG

*****************************/

#define CURRENT_LOG_LEVEL           LOG_LEVEL_DEBUG     // LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_WARN, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG

#define SD_SPI_SPEED                1'000'000

#define OLCD_I2C_SPEED              400'000

#define BATT_V_R1                   20000.0f
#define BATT_V_R2                   6800.0f

#define CAR_CLOCK_KHZ               176'000

#define TELEMETRY_EVERY_MS          (1000)*  1'000

#define CONNECT_TIMEOUT             20'000

/*****************************
DO NOT EDIT 

FUNCTIONS
*****************************/

#if (defined(PILOT) && defined(CAR)) || (!defined(PILOT) && !defined(CAR))
    #error "Define exactly ONE of PILOT or CAR"
#endif