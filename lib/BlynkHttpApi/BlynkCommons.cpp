#include <ESP8266WiFi.h>
#include <BlynkHttpApi.h>
#include <ArduinoJson.h>
#include <PbDht.h>

void handleDeepSleep(const String& virtualPin){
    String sleepDuration = readPinValueAsString(virtualPin);
    int sleepDurationValue = sleepDuration.toInt();
    if (sleepDurationValue == 0){
        return;
    }

    ESP.deepSleep(sleepDurationValue * 1000000);
}

void readVirtualWriteDigital(const String& virutalPin, const int& digitalPin){
    String virtual10 = readPinValueAsString(virutalPin);
    if (virtual10.toInt() == 0){
        Serial.println("write LOW");
        digitalWrite(digitalPin, LOW);
    }

    if (virtual10.toInt() == 1){
        Serial.println("write HIGH");
        digitalWrite(digitalPin, HIGH);
    }
}

String handleDht(const JsonObject &virtualPins){
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

    String dataSet = "max Temp " + maxTemperatureValue + " C" + "\n"
    + "min Temp " + minTemperatureValue + " C" + "\n"
    + "max humidity " + maxHumidityValue + " %" + "\n"
    + "min humidity " + minHumidityValue + " %" + "\n"
    + "\n"
    + "temperature " + temperatureValue + " C"  +"\n"
    + "humidity " + humidityValue + " %";

    String reciever = "reciever@mail.com";
    if (temperatureValue > maxTemperatureValue.toInt()){
        sendMail(reciever, dataSet, "temperature maximum exceeded");
        sendPushNotification("temperature maximum exceeded");
    }

    if (temperatureValue < minTemperatureValue.toInt()){
        sendMail(reciever, dataSet, "temperature minimum exceeded");
        sendPushNotification("temperature minimum exceeded");
    }

    if (humidityValue > maxHumidityValue.toInt()){
        sendMail(reciever, dataSet, "humidity maxiumum exceeded");
        sendPushNotification("humidity maxiumum exceeded");
    }

    if (humidityValue < minHumidityValue.toInt()){
        sendMail(reciever, dataSet, "humidity minimum exceeded");
        sendPushNotification("humidity minimum exceeded");
    }

    return dataSet;
}
