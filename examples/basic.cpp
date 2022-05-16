#include <Arduino.h>
#include "SimpleEspNetworkServices.h"

void mqttCallback(char *topic, byte *payload, unsigned int length);

SimpleEspNetworkServices networking;


void setup() {

  Serial.begin(9600);
  
  networking.begin();
  networking.mqttSubscribe("some/topic");
  networking.setMqttCallback(mqttCallback);
  
}

void loop() {
  
  networking.loop();
  delay(1);
}

void mqttCallback(char *topic, byte *payload, unsigned int length)
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