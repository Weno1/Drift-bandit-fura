struct pack
{
    uint8_t throtle;
    uint8_t yaw;
    uint16_t cmd;
};

void wifiStaticConfig(char* ip_s, char* nm_s, char* gw_s);

void wifiInit();

void carConnectToPilot();
