/*
   =====================================================================
        SciFyIoT Example 2: Sending Sensor Data
   =====================================================================

   📌 Description:
   This example reads sensor data (e.g., temperature, LDR, etc.)
   and sends it to the SciFy IoT platform every 15 seconds.

   🌐 SciFy IoT Dashboard:  https://connect.scify-tech.com/
   📦 GitHub Repository:    https://github.com/AlphaNodesDev/SciFy-Iot
   👨‍💻 Developer:          Abhiram S (AlphaNodesDev)
*/

#include "SciFyIot.h"

// ================== WiFi Credentials ==================
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// ================== SciFy IoT Project Keys ==================
const char* apiKey = "API_Key";
const char* secret = "API_Secret";
// ================== SciFyIoT Object ==================
SciFyIoT iot;

// Sensor pin (Example: LDR or Temperature)
const int sensorPin = A0;

// ======================================================
// Setup Function
// ======================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=========================================");
  Serial.println("     🚀 SciFyIoT Sensor Data Example    ");
  Serial.println("=========================================");

  pinMode(sensorPin, INPUT);

  // Start SciFy IoT connection
  iot.begin(ssid, password, apiKey, secret);

  Serial.println("✅ Device connected! Sending data soon...");
}

// ======================================================
// Loop Function
// ======================================================
void loop() {
  iot.loop();

  static unsigned long lastSend = 0;
  if (millis() - lastSend > 15000) {
    int sensorValue = analogRead(sensorPin);
    float voltage = (sensorValue / 1024.0) * 3.3;

    // Send data to SciFy IoT
    DynamicJsonDocument doc(256);
    JsonObject data = doc.to<JsonObject>();
    data["sensor_value"] = sensorValue;
    data["voltage"] = voltage;

    iot.sendCustomData("sensor_data", data);
    Serial.println("📤 Sent sensor data: Value=" + String(sensorValue) + " | Voltage=" + String(voltage) + "V");

    lastSend = millis();
  }
}
