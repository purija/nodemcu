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

void handleDht(const String &virtualTemp, const String &virtualHumidity){
    float humidity = getHumidity();
    Serial.print("humidity: ");
    Serial.println(humidity);
    float temperature = getTemperature();
    Serial.print("temperature: ");
    Serial.println(temperature);

    writePinValue(virtualHumidity, humidity);
    writePinValue(virtualTemp, temperature);
}

void handlePin5(){
  String virtual5 = readPinValueAsString("V5");
    if (virtual5.toInt() == 0){
        Serial.println("write LOW");
        digitalWrite(ledPin, LOW);
    }

    if (virtual5.toInt() == 1){
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
  handleDht("V4", "V3");
  handlePin5();

  //sendPushNotification("hey notification");
  handleDeepSleep();

  delay(5000L);
}
