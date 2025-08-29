# 🚀 SciFy IoT Library

SciFy IoT is an **Arduino-compatible library** designed to easily connect your IoT devices with the **SciFy Cloud Dashboard**.  
It helps developers build IoT-based applications quickly by providing built-in functions for **WiFi connectivity**, **data upload**, **real-time monitoring**, and **remote control**.

---

## 📌 Features
- 🌐 **Easy WiFi Setup** — Connect your device to the internet in seconds.
- 📡 **Real-time Data Upload** — Send sensor data directly to SciFy Cloud.
- 🟢 **LED / Device Control** — Control devices from the dashboard or mobile app.
- 🔔 **Live Monitoring** — Monitor sensor readings instantly.
- ⚡ **Lightweight & Fast** — Optimized for ESP8266 / ESP32 boards.

---

## 📦 Installation

### **Option 1 — Arduino IDE**
1. Open **Arduino IDE**
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for **"SciFy IoT"**
4. Click **Install**

### **Option 2 — Manual Installation**
1. Download the repository as `.zip` from [GitHub](https://github.com/AlphaNodesDev/SciFy-Iot)
2. Open **Arduino IDE** → **Sketch → Include Library → Add .ZIP Library**
3. Select the downloaded `.zip` file.

---

## 🛠️ Usage Examples

### **Example 1 — Basic LED Control**
```cpp
#include <SciFyIot.h>

SciFyIot scify;

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Initialize SciFy IoT connection
  scify.begin("Your_SSID", "Your_PASSWORD", "Your_DEVICE_ID", "Your_AUTH_TOKEN");

  // Setup LED Pin
  pinMode(2, OUTPUT);  // ESP8266 (D4), ESP32 may use GPIO2
}

void loop() {
  // Check for incoming commands from dashboard
  String command = scify.listen();

  if (command == "LED_ON") {
    digitalWrite(2, HIGH);
    Serial.println("LED Turned ON");
  } else if (command == "LED_OFF") {
    digitalWrite(2, LOW);
    Serial.println("LED Turned OFF");
  }

  delay(100);
}
```

---

### **Example 2 — Sensor Data Upload**
```cpp
#include <SciFyIot.h>

SciFyIot scify;

// Sensor Pin
#define SENSOR_PIN A0

void setup() {
  Serial.begin(115200);

  // Initialize SciFy IoT connection
  scify.begin("Your_SSID", "Your_PASSWORD", "Your_DEVICE_ID", "Your_AUTH_TOKEN");
}

void loop() {
  // Read sensor data
  int sensorValue = analogRead(SENSOR_PIN);

  // Send data to SciFy Dashboard
  scify.sendData("sensor_1", sensorValue);

  Serial.print("Sensor Data Sent: ");
  Serial.println(sensorValue);

  delay(2000);  // Send every 2 seconds
}
```
