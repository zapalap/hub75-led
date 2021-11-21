#include "WeatherStationMode.h"
#include <ArduinoJson.h>
#include <ezTime.h>

void refreshExternal(WeatherStationMode *mode);
void switchCardExternal(WeatherStationMode *mode);
void testUrl();

void WeatherStationMode::init()
{
    if (alreadyInitialized)
    {
        return;
    }

    alreadyInitialized = true;

    for (int i = 0; i < 7; i++)
    {
        auto card = new Card();
        card->title = "";
        card->temp = 0;
        card->weather = "";
        cards.push_back(card);
    }


    HUB75_I2S_CFG mxconfig;
    mxconfig.double_buff = true;

    display = new MatrixPanel_I2S_DMA(mxconfig);
    display->begin();

    ConnectionOptions connectionOptions;
    connectionOptions.ssid = "ISTS-2.4GHz-117C54";
    connectionOptions.password = "HDFVme5DjwMQ";
    connectionOptions.timeoutSeconds = 20;

    display->setTextColor(display->color565(255, 128, 64));

    display->setCursor(2, 13);
    display->println("Connecting");
    wifiConnection.Connect(connectionOptions);

    refreshTicker.attach(60, refreshExternal, this);
    cardSwitchTicker.attach(10, switchCardExternal, this);

    webServer.on("/test", testUrl);
    webServer.begin();

    refresh();
}

void WeatherStationMode::update()
{
    webServer.handleClient();
    showData();
}

void WeatherStationMode::refresh()
{
    DynamicJsonDocument doc(100000);

    HTTPClient http;
    http.begin("http://api.openweathermap.org/data/2.5/onecall?lat=50.08312&lon=19.94309&units=metric&exclude=minutely,hourly,alerts,current&appid=16ca9a0000ddbec0ed0a3816e144548b");
    http.GET();
    const String stringJson = http.getString();
    Serial.println(stringJson);
    deserializeJson(doc, stringJson);

    for (int i = 0; i < 7; i++)
    {
        auto card = cards[i];

        JsonObject wday = doc["daily"][i];
        auto dt = wday["dt"];
        card->title = dayShortStr(weekday(dt, UTC_TIME)) + "  " + day(dt) + "" + monthShortStr(month(dt));
        card->temp = (int)round(wday["temp"]["day"].as<double>());
        card->weather = wday["weather"][0]["main"].as<String>();
    }
}

void WeatherStationMode::showData()
{
    display->fillScreen(display->color444(0, 0, 0));

    display->setTextColor(display->color565(255, 128, 64));

    auto card = cards[currentCard];

    display->setCursor(2, 5);
    display->println(card->title);
    display->setCursor(2, 20);
    display->print(String(card->temp) + "C");
    display->setCursor(25, 20);
    display->print(card->weather);

    display->showDMABuffer();
    display->flipDMABuffer();
}

void WeatherStationMode::switchCard()
{
    currentCard++;
    if (currentCard >= cards.size())
    {
        currentCard = 0;
    }
}

void WeatherStationMode::handleRequest() {
    Serial.println("Request!");
}

void refreshExternal(WeatherStationMode *mode)
{
    mode->refresh();
}

void switchCardExternal(WeatherStationMode *mode)
{
    mode->switchCard();
}

void testUrl() {
    Serial.println("Request!");
}