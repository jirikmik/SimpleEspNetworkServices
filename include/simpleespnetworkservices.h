#ifndef NETWORKING_H
#define NETWORKING_H
#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <WiFiMulti.h> // Include the Wi-Fi-Multi library
#include <WiFiClient.h>
//#include <WebServer.h>
#include <ESPmDNS.h>
//#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h> // Include the Wi-Fi-Multi library
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#endif

#ifndef NETWORK_DISABLE_OTA 
#include <ArduinoOTA.h>
#endif

#ifndef NETWORK_DISABLE_MQTT 
#include <PubSubClient.h>
#endif

#ifndef APPCONFIG_H
#include "appconfig.h"
#endif

#define NETWORKING_LIB_VERSION 2022051301

class Networking {

public:
	Networking();
    void begin();
    void loop();
    bool isWifiConnected();
    IPAddress getIpAddress();
    #ifndef NETWORK_DISABLE_MQTT 
    PubSubClient getPubSubClient();
    void setMqttCallback(MQTT_CALLBACK_SIGNATURE);
    boolean mqttSubscribe(const char* topic);
    boolean mqttUnsubscribe(const char* topic);
    //void setMqttSubscribedTopics(const char topics[][100]);
    //void setMqttSubscribedTopics(const String* topics);
    #endif

    
    
//    void prepare();
//    void setMeteoHodnoty(MeteoHodnoty meteoHodnoty);

private:
    WiFiMulti wifiMulti;
    IPAddress ipAddress;
    WiFiClient espClient;
    #ifndef NETWORK_DISABLE_MQTT 
    PubSubClient pubSubClient;
    #endif
    void startWifi();
    #ifndef NETWORK_DISABLE_OTA 
    void startOta();
    #endif
    #ifndef NETWORK_DISABLE_MQTT 
    void startMqtt();
    #endif
    void static mqttCallback(char *topic, byte *payload, unsigned int length);
};


#endif