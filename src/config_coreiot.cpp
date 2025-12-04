#include "config_coreiot.h"
#include <LittleFS.h>
#include <ArduinoJson.h>

// ✅ Biến toàn cục
//{clientId:"ESP32_S3",userName:"KietNguyen",password:"87654321"}
String coreiot_server    = "app.coreiot.io";
int    coreiot_port      = 1883;
String coreiot_client_id = "ESP32_S3";
String coreiot_username  = "KietNguyen";
String coreiot_password  = "87654321";

bool loadCoreIOTConfig() {
    if (!LittleFS.exists("/coreiot.json")) {
        Serial.println("⚠️ Chưa có coreiot.json");
        return false;
    }

    File f = LittleFS.open("/coreiot.json", "r");
    if (!f) {
        Serial.println("❌ Không mở được coreiot.json");
        return false;
    }

    StaticJsonDocument<512> doc;
    DeserializationError err = deserializeJson(doc, f);
    f.close();
    
    if (err) {
        Serial.print("❌ JSON parse error: ");
        Serial.println(err.c_str());
        return false;
    }

    coreiot_server    = doc["server"] | "";
    coreiot_port      = doc["port"] | 0;
    coreiot_client_id = doc["client_id"] | "";
    coreiot_username  = doc["username"] | "";
    coreiot_password  = doc["password"] | "";

    Serial.println("📄 Loaded CoreIOT config:");
    Serial.println("   Server: " + coreiot_server);
    Serial.println("   Port: " + String(coreiot_port));
    Serial.println("   Client ID: " + coreiot_client_id);
    Serial.println("   Username: " + coreiot_username);
    Serial.println("   Password: " + String(coreiot_password.length() > 0 ? "***" : "(empty)"));

    return true;
}

bool saveCoreIOTConfig() {
    StaticJsonDocument<512> doc;
    doc["server"]    = coreiot_server;
    doc["port"]      = coreiot_port;
    doc["client_id"] = coreiot_client_id;
    doc["username"]  = coreiot_username;
    doc["password"]  = coreiot_password;

    File f = LittleFS.open("/coreiot.json", "w");
    if (!f) {
        Serial.println("❌ Cannot write coreiot.json");
        return false;
    }

    serializeJson(doc, f);
    f.close();

    Serial.println("💾 Saved coreiot.json");
    return true;
}