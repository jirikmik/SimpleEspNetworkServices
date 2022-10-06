#include "simpleespnetworkservices.h"
WiFiMulti wifiMulti;

SimpleEspNetworkServices::SimpleEspNetworkServices() {
    this->hostname = NETWORK_HOSTNAME;
    initializeMqttSubscribedTopic();
}

void SimpleEspNetworkServices::begin() {
    startWifi();
    #ifndef NETWORK_DISABLE_OTA 
    startOta();
    #endif
    #ifndef NETWORK_DISABLE_MQTT 
    startMqtt();
    #endif
}

void SimpleEspNetworkServices::setHostname(const char* param_hostname) {
    this->hostname = param_hostname;
}
#ifdef NETWORK_HOSTNAME
void SimpleEspNetworkServices::startWifi() {


    Serial.print("Pripojuji k WiFi ... ");
    WiFi.setAutoReconnect(true);
    WiFi.setHostname(this->hostname);
    
    WiFi.enableSTA(true);
    WiFi.mode(WIFI_STA);

    #ifdef WIFI_SSID_01
    wifiMulti.addAP(WIFI_SSID_01, WIFI_PASS_01);
    #endif
    #ifdef WIFI_SSID_02
    wifiMulti.addAP(WIFI_SSID_02, WIFI_PASS_02);
    #endif
    #ifdef WIFI_SSID_03
    wifiMulti.addAP(WIFI_SSID_03, WIFI_PASS_03);
    #endif
    #ifdef WIFI_SSID_04
    wifiMulti.addAP(WIFI_SSID_04, WIFI_PASS_04);
    #endif
    #ifdef WIFI_SSID_05
    wifiMulti.addAP(WIFI_SSID_05, WIFI_PASS_05);
    #endif
    #ifdef WIFI_SSID_06
    wifiMulti.addAP(WIFI_SSID_06, WIFI_PASS_06);
    #endif
    #ifdef WIFI_SSID_07
    wifiMulti.addAP(WIFI_SSID_07, WIFI_PASS_07);
    #endif
    #ifdef WIFI_SSID_08
    wifiMulti.addAP(WIFI_SSID_08, WIFI_PASS_08);
    #endif
    #ifdef WIFI_SSID_09
    wifiMulti.addAP(WIFI_SSID_09, WIFI_PASS_09);
    #endif
    #ifdef WIFI_SSID_10
    wifiMulti.addAP(WIFI_SSID_10, WIFI_PASS_10);
    #endif

    uint8_t connection_counter = 0;
    while (wifiMulti.run() != WL_CONNECTED)
    { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above

        int status = WL_IDLE_STATUS;
        status = WiFi.status();
        //Serial.println(get_wifi_status(status));
        connection_counter++;
        if (connection_counter >= 5)  {
            ESP.restart();
        }
        Serial.print('.');
        delay(500);
        
    }
    //Serial.println();
    Serial.println(".. pripojeno :-)");

    ipAddress = WiFi.localIP();
    Serial.print("IP: ");
    Serial.println(ipAddress);
    //Serial.println(WiFi.getHostname());
    //WiFi.setHostname("ESP32-meteostanice");
    Serial.print("Hostname: ");
    Serial.println(WiFi.getHostname());

    if (MDNS.begin("ESP32-meteostanice"))
    {
        Serial.println("MDNS responder je zapnuty.");
    }


}
#endif

#ifdef NETWORK_HOSTNAME
#ifndef NETWORK_DISABLE_OTA 
void SimpleEspNetworkServices::startOta() {

    ArduinoOTA.setHostname(NETWORK_HOSTNAME);
    ArduinoOTA.setPassword(NETWORK_OTA_PASSWORD);

    ArduinoOTA.onStart([]()
        {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
            {
                type = "sketch";
            }
            else
            { // U_SPIFFS
                type = "filesystem";
            }

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type); 
        });
    ArduinoOTA.onEnd([]()
                    { Serial.println("\nEnd"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                            { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });
    ArduinoOTA.onError([](ota_error_t error)
                     {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    } });

    ArduinoOTA.begin();

}
#endif
#endif

#ifdef NETWORK_MQTT_SERVER
#ifndef NETWORK_DISABLE_MQTT 
void SimpleEspNetworkServices::startMqtt() {
    
    pubSubClient.setClient(espClient);

    


    
    

    uint8_t connection_counter = 0;
    while (!pubSubClient.connected()) {
        Serial.print("Pripojuji k MQTT ... ");

        #ifdef NETWORK_MQTT_SERVER_IP
        if (connection_counter < 3) { // if defined server IP at first try to connect to IP and then to hostname
            IPAddress mqttServerIp;
            mqttServerIp.fromString(NETWORK_MQTT_SERVER_IP);
            pubSubClient.setServer(mqttServerIp, NETWORK_MQTT_PORT);
        } else {
            pubSubClient.setServer(NETWORK_MQTT_SERVER, NETWORK_MQTT_PORT);
        }
        #else
        pubSubClient.setServer(NETWORK_MQTT_SERVER, NETWORK_MQTT_PORT);
        #endif

        if (pubSubClient.connect(this->hostname, NETWORK_MQTT_USERNAME, NETWORK_MQTT_PASSWORD)) {

            Serial.println("connected");

            if (mqttCallbackSaved) {
                pubSubClient.setCallback(mqttCallback);
            }

            for (int i=0; i<MQTT_TOPICS_MAX_NUM; i++) {
                if (mqttSubscribedTopics[i] != "") {
                    pubSubClient.subscribe(mqttSubscribedTopics[i].c_str());
                    
                }
            }

        } else {

            Serial.print("failed with state ");
            Serial.print(pubSubClient.state());
            Serial.println();

            connection_counter++;
            if (connection_counter >= 5) {
                ESP.restart();
            }

            delay(1000);
        }

    }
}

/*
void SimpleEspNetworkServices::mqttSetSubscribedTopics(const char* topics[20]) {
    
    //mqttSubscribedTopics = topics;
}
*/


boolean SimpleEspNetworkServices::mqttPublish(const char* topic, const char* payload) {
    
    return pubSubClient.publish(topic, payload);
}

boolean SimpleEspNetworkServices::mqttPublish(const char* topic, const char* payload, boolean retained) {
    return pubSubClient.publish(topic, payload, retained);
}
#endif
#endif

void SimpleEspNetworkServices::loop() {
    if (!isWifiConnected()) {
        Serial.println("Znovupřipojuji WiFi");
        begin();
    }
    #ifndef NETWORK_DISABLE_OTA 
    ArduinoOTA.handle();
    #endif
    #ifndef NETWORK_DISABLE_MQTT 
    if (!pubSubClient.connected()) {
        startMqtt();
    }
    pubSubClient.loop();
    #endif
    
}

bool SimpleEspNetworkServices::isWifiConnected() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    } else return false;
}
#ifndef NETWORK_DISABLE_MQTT 
boolean SimpleEspNetworkServices::mqttSubscribe(const char* topic) {
    
    if (pubSubClient.subscribe(topic)) {
        if (addMqttSubscribedTopic(topic)) {
            return true;
        } else {
            pubSubClient.unsubscribe(topic);
            return false;
        }
    } else {
        return false;
    }
}

boolean SimpleEspNetworkServices::mqttUnsubscribe(const char* topic) {
    removeMqttSubscribedTopic(topic);
    return pubSubClient.unsubscribe(topic);
}


void SimpleEspNetworkServices::setMqttCallback(MQTT_CALLBACK_SIGNATURE) {
    if (!mqttCallbackSaved) {
        mqttCallback = callback;
    }
    pubSubClient.setCallback(mqttCallback);
    
}

bool SimpleEspNetworkServices::addMqttSubscribedTopic(const char* topic) {

    for (int i=0; i<MQTT_TOPICS_MAX_NUM; i++) {
        if (mqttSubscribedTopics[i] == "") {
            mqttSubscribedTopics[i] = String(topic);
            return true;
        }
    }
    return false;
}

bool SimpleEspNetworkServices::removeMqttSubscribedTopic(const char* topic) {

    for (int i=0; i<MQTT_TOPICS_MAX_NUM; i++) {
        if (mqttSubscribedTopics[i].c_str() == "") {
            mqttSubscribedTopics[i] = "";
            //return true;
        }
    }
    return true;
}

void SimpleEspNetworkServices::initializeMqttSubscribedTopic() {
    for (int i=0; i<MQTT_TOPICS_MAX_NUM; i++) {
        mqttSubscribedTopics[i] = "";
    }
}


PubSubClient SimpleEspNetworkServices::getPubSubClient() {
    return pubSubClient;
}
#endif

IPAddress SimpleEspNetworkServices::getIpAddress() {
    return ipAddress;
}
/*
void SimpleEspNetworkServices::mqttCallback(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");

}
*/