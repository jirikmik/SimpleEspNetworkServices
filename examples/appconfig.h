
#ifndef APPCONFIG_H
#define APPCONFIG_H

//#define NETWORK_DISABLE_OTA
//#define NETWORK_DISABLE_MQTT
#define NETWORK_HOSTNAME "esp32_netservices"

#define NETWORK_OTA_PASSWORD "netservices_d"

#define NETWORK_MQTT_SERVER ""
#define NETWORK_MQTT_PORT 1883
#define NETWORK_MQTT_USERNAME ""
#define NETWORK_MQTT_PASSWORD ""

//extern String mqttTopics[] = {"netservices", "netservices"};

#define MQTT_TOPICS "netservices"

// libovolných 10 sítí, lze vynechat, nezáleží na pořadí

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