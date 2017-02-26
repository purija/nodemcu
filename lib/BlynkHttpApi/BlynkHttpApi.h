#ifndef BLYNK_HTTP_API_H
#define BLYNK_HTTP_API_H

#include <ESP8266WiFi.h>

bool httpRequest(const std::string& method, const std::string& request, std::string& response);
void connectNetwork();
void writePinValue(const String& pin, const float& data);
String readPinValue(const String& pin);
String readPinValueAsString(const String& pin);
//bool isHardWareConnected();
//bool isAppConnected();
void sendPushNotification(const String& message);
void sendMail(const String& to, const String& title, const String& subject);
//void pinHistoryData();
//std::string queryApi();

#endif
