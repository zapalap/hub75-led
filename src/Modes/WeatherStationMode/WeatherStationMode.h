#ifndef WEATHER_STATION_MODE_H
#define WEATHER_STATION_MODE_H

#include "Arduino.h"
#include "../Mode.h"
#include "Common/WiFiConnection.h"
#include <HTTPClient.h>
#include <Ticker.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class WeatherStationMode : public Mode
{
public:
    void init();
    void update();
    void refresh();
    
private:
    void showData();
    double tempC;
    const char* locationName;
    Ticker refreshTicker;
    MatrixPanel_I2S_DMA *display = nullptr;
    WiFiConnection wifiConnection;
};

#endif