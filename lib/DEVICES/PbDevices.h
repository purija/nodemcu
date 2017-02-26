#ifndef PBDEVICES_H
#define PBDEVICES_H

#include <ESP8266WiFi.h>
#include <string>

class Device{
private:
    String auth;
    String ssid;
    String pass;
public:
    Device(String auth, String ssid, String pass);
    Device();

    void setDevice(String auth, String ssid, String pass);
    Device getNodeMcu();

    String getAuth() { return auth; }
    String getSsid() { return ssid; }
    String getPass()  { return pass; }

    void setAuth(String auth) { Device::auth = auth; }
    void setSsid(String ssid) { Device::ssid = ssid; }
    void setPass(String pass)  { Device::pass = pass; }
};


#endif
