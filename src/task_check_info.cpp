#include "task_check_info.h"

// ✅ Forward declaration
extern void startAP();

void Load_info_File() {
    File file = LittleFS.open("/info.dat", "r");
    if (!file) {
        Serial.println("⚠️ File /info.dat không tồn tại");
        return;
    }
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.print(F("❌ deserializeJson() failed: "));
        Serial.println(error.c_str());
    } else {
        WIFI_SSID = doc["WIFI_SSID"] | "";
        WIFI_PASS = doc["WIFI_PASS"] | "";
        WIFI_USERNAME = doc["WIFI_USERNAME"] | "";  // ✅ THÊM DÒNG NÀY
        CORE_IOT_TOKEN = doc["CORE_IOT_TOKEN"] | "";
        CORE_IOT_SERVER = doc["CORE_IOT_SERVER"] | "";
        CORE_IOT_PORT = doc["CORE_IOT_PORT"] | "";
        Serial.println("✅ Đã load cấu hình:");
        Serial.println("SSID: " + WIFI_SSID);
        Serial.println("Pass: " + String(WIFI_PASS.length()) + " chars");  // ✅ THÊM DÒNG NÀY
        if (!WIFI_USERNAME.isEmpty()) {  // ✅ THÊM DÒNG NÀY
            Serial.println("Username: " + WIFI_USERNAME + " (WPA2-Enterprise)");
        }
    }
    file.close();
}

void Delete_info_File()
{
    if (LittleFS.exists("/info.dat"))
    {
        LittleFS.remove("/info.dat");
        Serial.println("🗑️ Đã xóa file cấu hình");
    }
    ESP.restart();
}

void Save_info_File(String wifi_ssid, String wifi_pass, String core_iot_token, String core_iot_server, String core_iot_port, bool restartAfter)
{
    Serial.println("💾 Đang lưu cấu hình...");
    Serial.println("SSID: " + wifi_ssid);

    DynamicJsonDocument doc(4096);
    doc["WIFI_SSID"] = wifi_ssid;
    doc["WIFI_PASS"] = wifi_pass;
    doc["WIFI_USERNAME"] = WIFI_USERNAME;

    doc["CORE_IOT_TOKEN"] = core_iot_token;
    doc["CORE_IOT_SERVER"] = core_iot_server;
    doc["CORE_IOT_PORT"] = core_iot_port;

    File configFile = LittleFS.open("/info.dat", "w");
    if (configFile)
    {
        serializeJson(doc, configFile);
        configFile.close();
        Serial.println("✅ Đã lưu cấu hình thành công");
    }
    else
    {
        Serial.println("❌ Không thể lưu cấu hình!");
    }

    if (restartAfter) {
        delay(1000);
        ESP.restart();
    }
}

bool check_info_File(bool check)
{
    if (!check)
    {
        if (!LittleFS.begin(true))
        {
            Serial.println("❌ Lỗi khởi động LittleFS!");
            return false;
        }
        Load_info_File();
    }
    
    if (WIFI_SSID.isEmpty())
{
    if (!ap_started)
    {
        delay(100); // ✅ Đợi Serial ổn định (nếu chưa mở)
        Serial.println("⚠️ Không có thông tin WiFi, khởi động AP mode");
        if (!check)
        {
            startAP();
            Serial.println("🌐 Hãy kết nối Wi-Fi: ESP32-Setup-Wifi");
            Serial.println("➡️ Truy cập http://192.168.4.1 để cấu hình");

        }
        ap_started = true;  // ✅ Chỉ gọi AP 1 lần
    }
    return false;
}

    
    return true;
}