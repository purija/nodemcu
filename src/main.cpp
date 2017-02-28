#include <ESP8266WiFi.h>
#include <BlynkHttpApi.h>
#include <PbDht.h>
#include <DHT.h>
#include <PbDevices.h>
#include <ArduinoJson.h>
#include <BlynkCommons.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PbSsd1306.h>


//digital debug pin
int ledPin = 0;

void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();

  connectNetwork();
  initDhtSensor();

  //initialize debug pin
  pinMode(ledPin, OUTPUT);

  initDisplay();

  //sendPushNotification("hey notification");
  //sendMail("mail@reciever.com", "setup nodemcu", "nodemcu was initialized");
}


void loop() {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& dhtPins = jsonBuffer.createObject();
    dhtPins["humidity"] = "V1";
    dhtPins["temperature"] = "V2";
    dhtPins["maxTemperature"] = "V3";
    dhtPins["minTemperature"] = "V4";
    dhtPins["maxHumidity"] = "V5";
    dhtPins["minHumidity"] = "V6";

    String dataSet = handleDht(dhtPins);
    printText(dataSet);

    //debug control
    readVirtualWriteDigital("V10", ledPin);

    handleDeepSleep("V0");
}
