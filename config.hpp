#ifndef CONFIG_HPP
#define CONFIG_HPP

/*****************************

DEVICE SELECTION

*****************************/

//#define PILOT
#define CAR

/*****************************

WIRELESS CONNECTION CONFIG

*****************************/

#define PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE CYW43_COUNTRY_POLAND

#define PILOT_AP_SSID               "Drift-Bandit-Fura"
#define PILOT_AP_PASSWD             "N6znW5<x@D,0ki(tkWR£'4_!&0TK{(w'[4p1s8A+pBID.g9CpL" //Random generated password, you can set your own.

#define PILOT_LISTEN_PORT           3404

#define PILOT_IP                    "192.168.4.1"
#define CAR_IP                      "192.168.4.2"

#define NETMASK                     "255.255.255.0"
#define GATEWAY                     PILOT_IP

/*****************************
DO NOT EDIT 

FUNCTIONS
*****************************/

#if (defined(PILOT) && defined(CAR)) || (!defined(PILOT) && !defined(CAR))
#error "Define exactly ONE of PILOT or CAR"
#endif

#endif /* CONFIG_HPP */