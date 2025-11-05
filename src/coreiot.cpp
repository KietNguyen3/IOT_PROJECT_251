#include "coreiot.h"
#include <WiFi.h>
#include "task_wifi.h"
// ----------- CONFIGURE THESE! -----------
const char* coreIOT_Server = "app.coreiot.io";  
const char* coreIOT_Token = "hsd93mmwaws3kivi7x5y";   // Device Access Token
const int   mqttPort = 1883;
// ------------CONFIGURING USERNAME AND PASSWORD---------
const char* mqttUsername = "KietNguyen";
const char* mqttPassword = "Kiet2005";
// ----------------------------------------

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect (username=token, password=empty)
    if (client.connect("ESP32_TEST", coreIOT_Token, "")) {
      Serial.println("connected to CoreIOT Server!");
      client.subscribe("v1/devices/me/rpc/request/+");
      Serial.println("Subscribed to v1/devices/me/rpc/request/+");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0';
  Serial.print("Payload: ");
  Serial.println(message);

  // Extract request ID from topic for response
  String topicStr = String(topic);
  int lastSlash = topicStr.lastIndexOf('/');
  String requestId = topicStr.substring(lastSlash + 1);
  String responseTopic = "v1/devices/me/rpc/response/" + requestId;

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);
                                                                                                                        
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  const char* method = doc["method"];
  Serial.print("Method received: ");
  Serial.println(method);
  
  // ============ SET LED STATE ============
  if (strcmp(method, "setLedSwitchValue") == 0) {
    
    bool newState = false;
    
    if(doc["params"].is<bool>()){
      newState = doc["params"];
      Serial.print("Boolean value: ");
      Serial.println(newState);
      
      digitalWrite(LED_GPIO, (newState ? HIGH : LOW));
      Serial.print("LED set to: ");
      Serial.println(newState ? "HIGH" : "LOW");
    }
    else if (doc["params"].is<const char*>()) {
      const char* params = doc["params"];
      Serial.print("String value: ");
      Serial.println(params);
      
      if (strcmp(params, "true") == 0) {
        Serial.println("→ Turning LED ON");
        digitalWrite(LED_GPIO, HIGH);
        newState = true;
      }  
      else if(strcmp(params, "false") == 0){   
        Serial.println("→ Turning LED OFF");
        digitalWrite(LED_GPIO, LOW);
        newState = false;
      }
    }
    
    // Send response
    String response = newState ? "true" : "false";
    client.publish(responseTopic.c_str(), response.c_str());
    Serial.println("Response sent: " + response);
  } 
  // ============ GET LED STATE ============
  else if (strcmp(method, "getLedSwitchValue") == 0) {
    Serial.println("✓ Matched getLedSwitchValue!");
    
    bool currentState = digitalRead(LED_GPIO);
    Serial.print("Current LED state: ");
    Serial.println(currentState ? "HIGH" : "LOW");
    
    // Send response with current state
    String response = currentState ? "true" : "false";
    client.publish(responseTopic.c_str(), response.c_str());
    Serial.println("Response sent: " + response);
  }
  else {
    Serial.print("Unknown method: ");
    Serial.println(method);
  }
}


void setup_coreiot(){

  startSTA();

  client.setBufferSize(512);  
  client.setServer(coreIOT_Server, mqttPort);
  client.setCallback(callback);

  Serial.println("Connecting to CoreIOT server...");
  if(client.connect("ESP32_TEST", coreIOT_Token, "")){
    Serial.println("Connected to CoreIOT Server");
    client.subscribe("v1/devices/me/rpc/request/+");
    Serial.println("Subscribed to v1/devices/me/rpc/request/+");
  } else {
    Serial.println("Failed to connect with state: ");
    Serial.println(client.state());
    reconnect();
  }

}

void coreiot_task(void *pvParameters){

    setup_coreiot();

    while(1){

        if (!client.connected()) {
            reconnect();
        }
        client.loop();

        // Sample payload, publish to 'v1/devices/me/telemetry'
        // String payload = "{\"temperature\":" + String(glob_temperature) +  ",\"humidity\":" + String(glob_humidity) + "}";
        
        // client.publish("v1/devices/me/telemetry", payload.c_str());

        // Serial.println("Published payload: " + payload);

        // vTaskDelay(10000);  // Publish every 10 seconds

        //-----FOR SWITCHING LED------//
        vTaskDelay(100);

    }
}

// RPC_Response setLedSwitchState(const RPC_Data &data){
//     bool newState = data;
//     Serial.println("LED switching to: ");
//     Serial.println(newState);
//     digitalWrite(LED_GPIO, newState);
//     return RPC_Response("setLedSwitchValue", newState);
// }

// RPC_Response getLedSwitchState(const RPC_Data &data){
//     bool currentState = digitalRead(LED_GPIO);
//     Serial.println("Reporting LED state: ");
//     Serial.println(currentState);
//     return RPC_Response("setLedSwitchValue", currentState);
// }

// const std::array<RPC_Callback, 2U> callbacks = {
//   RPC_Callback{ "setLedSwitchValue", setLedSwitchState },
//   RPC_Callback{ "getLedSwitchValue", getLedSwitchState }
// };
