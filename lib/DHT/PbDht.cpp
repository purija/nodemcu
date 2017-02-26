/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.
    Downloads, docs, tutorials: http://www.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need SimpleTimer library:
    https://github.com/jfturcot/SimpleTimer
  and Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/
#include <DHT.h>

#define DHTPIN D4          // What digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

float getHumidity(){
  float humidity = dht.readHumidity();

  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }

  return humidity;
}

float getTemperature(){
    float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

    if (isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return 0;
    }

    return temperature;
}

void initDhtSensor(){
    Serial.println("initialize dht sensor");
    dht.begin();
    Serial.println("completed dht initialize");
}
