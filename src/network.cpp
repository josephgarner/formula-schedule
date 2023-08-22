#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <WiFi.h>
#include <network.h>
#include <time.h>

const char *WIFI_SSID = "ssid";
const char *WIFI_PASSWORD = "password";

wl_status_t startWiFi(int &wifiRSSI) {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to '%s'", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long timeout = millis() + 10000;
    wl_status_t status = WiFi.status();
    while ((status != WL_CONNECTED) && (millis() < timeout)) {
        Serial.print(".");
        delay(50);
        status = WiFi.status();
    }
    Serial.println();

    if (status == WL_CONNECTED) {
        wifiRSSI = WiFi.RSSI();
        Serial.println("IP: " + WiFi.localIP().toString());
    } else {
        Serial.printf("Could not connect to '%s'\n", WIFI_SSID);
    }
    return status;
}