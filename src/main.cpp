/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Sketch generator:           http://examples.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on NodeMCU.
 *
 * Note: This requires ESP8266 support package:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right NodeMCU module
 * in the Tools -> Board menu!
 *
 * For advanced settings please follow ESP examples :
 *  - ESP8266_Standalone_Manual_IP.ino
 *  - ESP8266_Standalone_SmartConfig.ino
 *  - ESP8266_Standalone_SSL.ino
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PbDht.h>
#include <DHT.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PbSsd1306.h>
#include <SimpleTimer.h>

SimpleTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "auth";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ssid";
char pass[] = "pass";

int sleepDuration = 0;
int maxTemperature = -1;
int minTemperature = -1;
int maxHumidity = -1;
int minHumidity = -1;
float temperature = 0;
float humidity = 0;
int dhtFailRate = 0;

BLYNK_WRITE(V0){
  sleepDuration = param.asInt();
}

BLYNK_WRITE(V3){
  maxTemperature = param.asInt();
}

BLYNK_WRITE(V4){
  minTemperature = param.asInt();
}

BLYNK_WRITE(V5){
  maxHumidity = param.asInt();
}

BLYNK_WRITE(V6){
  minHumidity = param.asInt();
}

void handleDeepSleep(void){
    if (sleepDuration == 0){
        return;
    }

    Blynk.disconnect();
    ESP.deepSleep(sleepDuration * 1000000);
}


String handleDht(void){
    float currentHumidity = getHumidity();
    float currentTemperature = getTemperature();
    String reciever = "reciever@mail.com";

    if (currentHumidity != -248 || currentTemperature != -248){
        humidity = currentHumidity;
        temperature = currentTemperature;
        Blynk.virtualWrite(V1, humidity);
        Blynk.virtualWrite(V2, temperature);
    }else{
        dhtFailRate += 1;
        if (dhtFailRate >= 100){
            Blynk.email(reciever.c_str(), "dht fails to read", "dht fail count" + String (dhtFailRate));
            Blynk.notify("dht fails to read by fail count " + String (dhtFailRate));
            dhtFailRate = 0;
        }
    }

    String dataSet = "max Temp " + String(maxTemperature) + " C" + "\n"
    + "min Temp " + String(minTemperature) + " C" + "\n"
    + "max humidity " + String(maxHumidity) + " %" + "\n"
    + "min humidity " + String(minHumidity) + " %" + "\n"
    + "\n"
    + "temperature " + String(temperature) + " C"  +"\n"
    + "humidity " + String(humidity) + " %";


    if (maxTemperature != -1 && temperature > maxTemperature){
        Blynk.email(reciever.c_str(), "temperature maximum exceeded", dataSet);
        Blynk.notify("temperature maximum exceeded");
    }

    if (minTemperature != -1 && temperature < minTemperature){
        Blynk.email(reciever.c_str(), "temperature minimum exceeded", dataSet);
        Blynk.notify("temperature minimum exceeded");
    }

    if (maxHumidity != -1 && humidity > maxHumidity){
        Blynk.email(reciever.c_str(), "humidity maxiumum exceeded", dataSet);
        Blynk.notify("humidity maxiumum exceeded");
    }

    if (minHumidity != -1 &&humidity < minHumidity){
        Blynk.email(reciever.c_str(), "humidity minimum exceeded", dataSet);
        Blynk.notify("humidity minimum exceeded");
    }

    return dataSet;
}

void dhtEvent(){
    printText(handleDht());
    //handleDeepSleep();
}

void healthCheckEvent(){
    if (ESP.getFreeHeap() < 500){
        String message = "deepsleep triggerd - reason - heap almost exceeded ";
        Blynk.notify(message + ESP.getFreeHeap());

        String reciever = "purija@googlemail.com";
        Blynk.email(reciever.c_str(), message, message + ESP.getFreeHeap());

        Blynk.disconnect();
        ESP.deepSleep(500000);
    }
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  initDisplay();
  initDhtSensor();
  timer.setInterval(500L, dhtEvent);
  timer.setInterval(500L, healthCheckEvent);
}

void loop(){
  Blynk.run();
  timer.run();
  //Try to execute Blynk.run only in loop
}
