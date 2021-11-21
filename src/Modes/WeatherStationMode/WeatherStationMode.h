#ifndef WEATHER_STATION_MODE_H
#define WEATHER_STATION_MODE_H

#include "Arduino.h"
#include "../Mode.h"
#include "Common/WiFiConnection.h"
#include <HTTPClient.h>
#include <Ticker.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <WebServer.h>

struct Card
{
public:
    String title;
    int temp;
    String weather;
};

class WeatherStationMode : public Mode
{
public:
    void init();
    void update();
    void refresh();
    void switchCard();

private:
    bool alreadyInitialized;
    void showData();
    void handleRequest();
    int currentCard;
    std::vector<Card*> cards;
    Ticker refreshTicker;
    Ticker cardSwitchTicker;
    MatrixPanel_I2S_DMA *display = nullptr;
    WiFiConnection wifiConnection;
    WebServer webServer;
};

#endif