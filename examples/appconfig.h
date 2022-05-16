
#ifndef APPCONFIG_H
#define APPCONFIG_H

// if you can disable ArduinoOTA
//#define NETWORK_DISABLE_OTA
// if you can disable PubSubClient
//#define NETWORK_DISABLE_MQTT
#define NETWORK_HOSTNAME "esp32_netservices"

#define NETWORK_OTA_PASSWORD "change_me!"

#define NETWORK_MQTT_SERVER ""
#define NETWORK_MQTT_PORT 1883
#define NETWORK_MQTT_USERNAME ""
#define NETWORK_MQTT_PASSWORD ""

#define MQTT_TOPICS "netservices"

// up to 10 SSIDs

#define WIFI_SSID_01 ""
#define WIFI_PASS_01 ""

#define WIFI_SSID_02 ""
#define WIFI_PASS_02 ""

#define WIFI_SSID_03 ""
#define WIFI_PASS_03 ""

#define WIFI_SSID_04 ""
#define WIFI_PASS_04 ""

#define WIFI_SSID_09 ""
#define WIFI_PASS_09 ""

#define WIFI_SSID_10 ""
#define WIFI_PASS_10 ""


#endif