/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * This example code is in public domain.
 *
 **************************************************************
 * Project setup in the Blynk app:
 *   Value Display widget on V2
 *
 **************************************************************/
#include <ESP8266WiFi.h>
#include <PbDevices.h>
#include <ArduinoJson.h>

// Blynk cloud server
const char* host = "blynk-cloud.com";
unsigned int port = 8080;

WiFiClient client;
Device node;

// Start the WiFi connection
void connectNetwork()
{
  Serial.print("Connecting to ");
  Serial.println();

  node = node.getNodeMcu();
  Serial.print("node getSsid");
  Serial.println(node.getSsid());

  Serial.print("node getPass");
  Serial.println(node.getPass());

  Serial.print("node getAuth");
  Serial.println(node.getAuth());

  WiFi.begin(node.getSsid().c_str(), node.getPass().c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


bool httpRequest(const String& method,
                 const String& request,
                 String&       response)
{
  Serial.print(F("Connecting to "));
  Serial.print(host);
  Serial.print(":");
  Serial.print(port);
  Serial.print("... ");
  if (client.connect(host, port)) {
    Serial.println("OK");
  } else {
    Serial.println("failed");
    return false;
  }

  client.print(method); client.println(F(" HTTP/1.1"));
  client.print(F("Host: ")); client.println(host);
  client.println(F("Connection: close"));
  if (request.length()) {
    client.println(F("Content-Type: application/json"));
    client.print(F("Content-Length: ")); client.println(request.length());
    client.println();
    client.print(request);
  } else {
    client.println();
  }

  //Serial.println("Waiting response");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return false;
    }
  }

  //Serial.println("Reading response");
  int contentLength = -1;
  while (client.available()) {
    String line = client.readStringUntil('\n');
    line.trim();
    line.toLowerCase();
    if (line.startsWith("content-length:")) {
      contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
    } else if (line.length() == 0) {
      break;
    }
  }

  //Serial.println("Reading response body");
  response = "";
  response.reserve(contentLength + 1);
  while (response.length() < contentLength && client.connected()) {
    while (client.available()) {
      char c = client.read();
      response += c;
    }
  }
  client.stop();
  return true;
}

void writePinValue(const String& pin, const float& data){
    String response;
    String putData = String("[\"") + data + "\"]";
    Serial.println("put for auth " + node.getAuth() + " and pin " + pin);
    if (httpRequest(String("PUT /") + node.getAuth() + "/update/" + pin, putData, response)) {
        if (response.length() != 0) {
        Serial.print("WARNING: ");
        Serial.println(response);
        }
    }
}

String readPinValue(const String& pin){
    String response;
    Serial.println("get for auth " + node.getAuth() + " and pin " + pin);
    if (httpRequest(String("GET /") + node.getAuth() + "/get/" + pin, "", response)) {
        Serial.print("response from server: ");
        Serial.println(response);
    }

    return response;
}

String readPinValueAsString(const String& pin){
    DynamicJsonBuffer jsonBuffer;
    JsonArray& virtualArray = jsonBuffer.parseArray(readPinValue(pin));
    String virtual5 = virtualArray[0];
    return virtual5;
}

void sendMail(const String& to, const String& title, const String& subject){
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["to"] = to;
    root["title"] = title;
    root["subj"] = subject;

    String payload;
    root.printTo(payload);

    Serial.println("email post for auth " + node.getAuth() + " with payload " + payload);
    String response;
    if (httpRequest(String("POST /") + node.getAuth() + "/email", payload, response)) {
        if (response.length() != 0) {
        Serial.print("WARNING: ");
        Serial.println(response);
        }
    }
}

void sendPushNotification(const String& message){
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["body"] = message;

    String payload;
    root.printTo(payload);

    Serial.println("notification post for auth " + node.getAuth() + " with payload " + payload);
    String response;
    if (httpRequest(String("POST /") + node.getAuth() + "/notify", payload, response)) {
        if (response.length() != 0) {
        Serial.print("WARNING: ");
        Serial.println(response);
        }
    }
}
