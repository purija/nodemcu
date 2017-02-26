#include <ESP8266WiFi.h>
#include <BlynkHttpApi.h>
#include <PbDht.h>
#include <DHT.h>
#include <PbDevices.h>
#include <ArduinoJson.h>

int ledPin = 0;

void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();

  connectNetwork();
  initDhtSensor();

  //debug area
  pinMode(ledPin, OUTPUT);

  //sendMail("mail@reciever.com", "setup nodemcu", "nodemcu was initialized");
}

void handleDht(const JsonObject &virtualPins){
    String humidity = virtualPins["humidity"];
    float humidityValue = getHumidity();
    
    String temperature = virtualPins["temperature"];
    float temperatureValue = getTemperature();

    writePinValue(humidity, humidityValue);
    writePinValue(temperature, temperatureValue);

    String maxTemperature = virtualPins["maxTemperature"];
    String minTemperature = virtualPins["minTemperature"];
    String maxHumidity = virtualPins["maxHumidity"];
    String minHumidity = virtualPins["minHumidity"];

    String maxTemperatureValue = readPinValueAsString(maxTemperature);
    String minTemperatureValue = readPinValueAsString(minTemperature);
    String maxHumidityValue = readPinValueAsString(maxHumidity);
    String minHumidityValue = readPinValueAsString(minHumidity);

    String dataSet = "max Temp " + maxTemperatureValue + " °C" + "\n"
    + "min Temp " + minTemperatureValue + " °C" + "\n"
    + "max humidity " + maxHumidityValue + " %" + "\n"
    + "min humidity " + minHumidityValue + " %" + "\n"
    + "\n"
    + "temperature value " + temperatureValue + " °C"  +"\n"
    + "humidity value " + humidityValue + " %";

    String reciever = "mail@reciever.com";
    if (temperatureValue > maxTemperatureValue.toInt()){
        sendMail(reciever, dataSet, "temperature maximum exceeded");
    }

    if (temperatureValue < minTemperatureValue.toInt()){
        sendMail(reciever, dataSet, "temperature minimum exceeded");
    }

    if (humidityValue > maxHumidityValue.toInt()){
        sendMail(reciever, dataSet, "humidity maxiumum exceeded");
    }

    if (humidityValue < minHumidityValue.toInt()){
        sendMail(reciever, dataSet, "humidity maxiumum exceeded");
    }
}

void handlePin10(){
    String virtual10 = readPinValueAsString("V10");
    if (virtual10.toInt() == 0){
        Serial.println("write LOW");
        digitalWrite(ledPin, LOW);
    }

    if (virtual10.toInt() == 1){
        Serial.println("write HIGH");
        digitalWrite(ledPin, HIGH);
    }
}

void handleDeepSleep(){
    String virtual5 = readPinValueAsString("V0");
    int sleepDuration = virtual5.toInt();
    if (sleepDuration == 0){
        return;
    }

    ESP.deepSleep(sleepDuration * 1000000);
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

    handleDht(dhtPins);

    //debug control
    handlePin10();

    //sendPushNotification("hey notification");
    handleDeepSleep();
}
