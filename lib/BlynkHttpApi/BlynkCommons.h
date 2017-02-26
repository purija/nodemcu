#ifndef BLYNK_COMMONS_H
#define BLYNK_COMMONS_H

#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

void handleDeepSleep(const String& virtualPin);
void readVirtualWriteDigital(const String& virutalPin, const int& digitalPin);
void handleDht(const JsonObject &virtualPins);

#endif
