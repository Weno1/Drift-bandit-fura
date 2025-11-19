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

#define PILOT_AP_SSID                   "Drift-Bandit-Fura"
#define PILOT_AP_PASSWD                 "N6znW5<x@D,0ki(tkWR£'4_!&0TK{(w'[4p1s8A+pBID.g9CpL"

#define PILOT_LISTEN_PORT               3404

#define PILOT_IP                        "192.168.4.1"
#define CAR_IP                          "192.168.4.2"

#define NETMASK                         "255.255.255.0"
#define GATEWAY                         PILOT_IP



/*****************************
DO NOT EDIT 

FUNCTIONS
*****************************/

#if defined(PILOT) && defined(CAR)
#error "!!! Can not be PILOT and CAR at the same time !!!"
#endif

#endif /* CONFIG_HPP */