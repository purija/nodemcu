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
    node.auth = "01543b676a8745b28f2e2dafc168cdf6";
    node.ssid = "darkside";
    node.pass = "4321075668542576" ;

    return node;
}

Device Device::getNode2(){
    Device node;
    node.auth = "80afd90f471e4d4085c7d1fe3e97b5f0";
    node.ssid = "darkside";
    node.pass = "4321075668542576" ;

    return node;
}
