#include "WeatherStationMode.h"
#include <ArduinoJson.h>

void refreshExternal(WeatherStationMode *mode);

void WeatherStationMode::init()
{
    Serial.begin(115200);

    HUB75_I2S_CFG mxconfig;
    mxconfig.double_buff = true;

    display = new MatrixPanel_I2S_DMA(mxconfig);
    display->begin();

    ConnectionOptions connectionOptions;
    connectionOptions.ssid = "ISTS-2.4GHz-117C54";
    connectionOptions.password = "HDFVme5DjwMQ";
    connectionOptions.timeoutSeconds = 20;
    wifiConnection.Connect(connectionOptions);
    refreshTicker.attach(60, refreshExternal, this);
    
    refresh();
}

void WeatherStationMode::update()
{
    showData();
}

void WeatherStationMode::refresh()
{
    DynamicJsonDocument doc(100000);

    HTTPClient http;
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=Krakow&units=metric&appid=16ca9a0000ddbec0ed0a3816e144548b");
    http.GET();
    const String stringJson = http.getString();
    Serial.println(stringJson);
    deserializeJson(doc, stringJson);
    tempC = doc["main"]["temp"];
    locationName = doc["name"];
}

void WeatherStationMode::showData()
{
    display->fillScreen(display->color444(0, 0, 0));
    
    display->setTextColor(display->color565(255, 128, 64));
    
    display->setCursor(10, 5);
    display->println(locationName);
    display->setCursor(10, 20);
    display->println(String(tempC) + " C");

    display->showDMABuffer();
    display->flipDMABuffer();
}

void refreshExternal(WeatherStationMode *mode)
{
    mode->refresh();
}