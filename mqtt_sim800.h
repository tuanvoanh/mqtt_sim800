#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#define mqtt_server "cretatech.com"
#define mqtt_port   1883
#define mqtt_topic "cretatech/server/"

void mqttSetup();
void mqttLoop();

extern const char* gSdt;
extern const char* gContent;


