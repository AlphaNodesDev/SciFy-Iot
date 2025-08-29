/*
   =====================================================================
        SciFyIoT Example 1: LED Control via IoT Dashboard
   =====================================================================

   📌 Description:
   This example demonstrates how to control the built-in LED of your ESP
   device using the SciFy IoT platform.

   🌐 SciFy IoT Dashboard:  https://connect.scify-tech.com/
   📦 GitHub Repository:    https://github.com/AlphaNodesDev/SciFy-Iot
   👨‍💻 Developer:          Abhiram S (AlphaNodesDev)

   ---------------------------------------------------------------------
   How it works:
   1. Connects ESP to WiFi.
   2. Connects to the SciFy IoT platform.
   3. Waits for commands from the dashboard.
   4. Supports the following commands:
      • LED_ON  → Turns ON the built-in LED.
      • LED_OFF → Turns OFF the built-in LED.
   ---------------------------------------------------------------------
*/

#include "SciFyIoT.h"

// ================== WiFi Credentials ==================
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// ================== SciFy IoT Project Keys ==================
const char* apiKey = "API_Key";
const char* secret = "API_Secret";

// ================== SciFyIoT Object ==================
SciFyIoT iot;

// LED state
bool ledState = false;

// ======================================================
// Callback: When a command is received from the dashboard
// ======================================================
void onCommandReceived(const String& command, const String& commandId) {
  Serial.println("📨 Command received: " + command);

  if (command == "LED_ON") {
    digitalWrite(LED_BUILTIN, LOW);  // LED ON
    ledState = true;
    iot.sendResponse(commandId, "executed", "LED turned ON");
    Serial.println("💡 LED is ON");
  }
  else if (command == "LED_OFF") {
    digitalWrite(LED_BUILTIN, HIGH); // LED OFF
    ledState = false;
    iot.sendResponse(commandId, "executed", "LED turned OFF");
    Serial.println("💡 LED is OFF");
  }
  else {
    iot.sendResponse(commandId, "failed", "Unknown command");
    Serial.println("⚠️ Unknown command!");
  }
}

// ======================================================
// Callback: Monitor connection & authentication status
// ======================================================
void onStatusChanged(bool connected, bool authenticated) {
  Serial.print("🔗 Connected: ");
  Serial.print(connected ? "YES" : "NO");
  Serial.print(" | Authenticated: ");
  Serial.println(authenticated ? "YES" : "NO");
}

// ======================================================
// Setup Function
// ======================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=========================================");
  Serial.println("     🚀 SciFyIoT LED Control Example    ");
  Serial.println("=========================================");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // LED OFF initially

  // Start SciFy IoT connection
  iot.begin(ssid, password, apiKey, secret);

  // Register callbacks
  iot.onCommandReceived(onCommandReceived);
  iot.onStatusChanged(onStatusChanged);

  Serial.println("✅ Ready! Send commands from dashboard.");
}

// ======================================================
// Loop Function
// ======================================================
void loop() {
  iot.loop();
}
