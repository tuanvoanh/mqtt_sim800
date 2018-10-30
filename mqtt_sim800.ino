#include "mqtt_sim800.h"

const char* gSdt = "";
const char* gContent = "";
WiFiClient espClient;
PubSubClient client(espClient);

void mqttSetup(){  
  client.setServer(mqtt_server,mqtt_port);
  client.setCallback(callback);
  reconnect();
}
void mqttLoop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  DynamicJsonBuffer jsonBuffer(200);
  JsonObject& root = jsonBuffer.parseObject(payload);
//  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    //return;
  }
  gSdt = root["sdt"];
  //Serial.print("sdt: ");
  //Serial.println(gSdt);
  gContent = root["content"];
  //Serial.print("content: ");
  //Serial.println(gContent);
  
}



