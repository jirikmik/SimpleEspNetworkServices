#ifndef NETWORKING_H
#define NETWORKING_H
#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <WiFiMulti.h> // Include the Wi-Fi-Multi library
#include <WiFiClient.h>
#include <ESPmDNS.h>
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

#define NETWORKING_LIB_VERSION 2022060802

#ifndef MQTT_TOPICS_MAX_NUM 
#define MQTT_TOPICS_MAX_NUM 5
#endif

class SimpleEspNetworkServices {

public:
	SimpleEspNetworkServices();
    void begin();
    void loop();
    bool isWifiConnected();
    IPAddress getIpAddress();
    void setHostname(const char* param_hostname);
    const char* getHostname();
    #ifndef NETWORK_DISABLE_MQTT 
    PubSubClient getPubSubClient();
    void setMqttCallback(MQTT_CALLBACK_SIGNATURE);
    boolean mqttSubscribe(const char* topic);
    boolean mqttUnsubscribe(const char* topic);
    boolean mqttPublish(const char* topic, const char* payload);
    boolean mqttPublish(const char* topic, const char* payload, boolean retained);
    void setTimer(hw_timer_t *);
    void mqttSetSubscribedTopics(const char* topics[20]);
    #endif

private:
    const char* hostname;
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
    //void static mqttCallback(char *topic, byte *payload, unsigned int length);
    //void (*mqttCallback)(char *topic, byte *payload, unsigned int length);
    std::function<void(char*, uint8_t*, unsigned int)> mqttCallback;
    bool mqttCallbackSaved = false;
    hw_timer_t * timer = NULL;
    void initializeMqttSubscribedTopic();
    bool addMqttSubscribedTopic(const char* topic);
    bool removeMqttSubscribedTopic(const char* topic);
    String mqttSubscribedTopics[MQTT_TOPICS_MAX_NUM ];

};

#endif