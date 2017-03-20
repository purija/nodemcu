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

Device Device::getNode1(){
    Device node;
    node.auth = "auth1";
    node.ssid = "ssid1";
    node.pass = "pass1" ;

    return node;
}

Device Device::getNode2(){
    Device node;
    node.auth = "auth2";
    node.ssid = "ssid2";
    node.pass = "pass2" ;

    return node;
}
