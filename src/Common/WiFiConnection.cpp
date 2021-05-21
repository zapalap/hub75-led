#include "WiFiConnection.h"
#include <WiFi.h>

WiFiConnection::WiFiConnection() {
}

void WiFiConnection::Connect(ConnectionOptions options) {
    WiFi.begin(options.ssid.c_str(), options.password.c_str());
    int connectionStartTime = millis();
    int millisSinceStart = 0;

    delay(500);
    Serial.print("Connecting to WiFi");
    while (millisSinceStart < options.timeoutSeconds * 1000 && WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        millisSinceStart = millis() - connectionStartTime;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
       Serial.print("Success! ("); 
       Serial.print(WiFi.localIP());
       Serial.print(")"); 
    } else {
       Serial.print("Timed out :("); 
    }

}