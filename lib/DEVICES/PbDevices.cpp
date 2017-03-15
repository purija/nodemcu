#include <ESP8266WiFi.h>
#include <PbDevices.h>


Device::Device(String auth, String ssid, String pass){
        setDevice(auth, ssid, pass);
}

Device::Device(){
}

void Device::setDevice(String auth_m, String ssid_m, String pass_m) {
    auth = auth_m;
    ssid = ssid_m;
    pass = pass_m;
}

Device Device::getNodeMcu(){
    Device node;
    node.auth = "auth";
    node.ssid = "ssid";
    node.pass = "pass" ;

    return node;
}
