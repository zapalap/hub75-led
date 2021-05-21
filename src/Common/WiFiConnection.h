#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <Arduino.h>

struct ConnectionOptions {
    String ssid;
    String password;
    int timeoutSeconds;
};

class WiFiConnection {
public:
    WiFiConnection();
    void Connect(ConnectionOptions options);
    void Disconnect();
};

#endif