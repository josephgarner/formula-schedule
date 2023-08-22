#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

wl_status_t startWiFi(int &wifiRSSI);

#endif