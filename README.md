
# 🚀 SciFy IoT Library

SciFy IoT is an **Arduino-compatible IoT library** designed to connect IoT devices with the **[SciFy Cloud Dashboard](https://connect.scify-tech.com/)**.  
It simplifies **WiFi connectivity**, **real-time data upload**, **remote device control**, and **sensor monitoring** for IoT developers, students, and makers.

---

## 🌟 Features

- 🌐 **Easy WiFi Setup** — Connect ESP8266 / ESP32 boards in seconds.
- 📡 **Real-time Data Upload** — Send sensor readings directly to the **SciFy Cloud**.
- 🟢 **Device Control** — Control LEDs, motors, and other devices remotely from the dashboard.
- 🔔 **Live Monitoring** — View sensor data instantly.
- ⚡ **Optimized & Lightweight** — Minimal memory usage for faster performance.
- 📊 **Dashboard Integration** — Full compatibility with **[SciFy Cloud](https://connect.scify-tech.com/)**.

---

## 🛠️ Installation

### **Option 1 — Arduino IDE (Recommended)**
1. Open **Arduino IDE**
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for **"SciFy IoT"**
4. Click **Install**

### **Option 2 — Manual Installation**
1. Download the repository as a `.zip` → [SciFy IoT GitHub](https://github.com/AlphaNodesDev/SciFy-Iot)
2. Open **Arduino IDE**
3. Go to **Sketch → Include Library → Add .ZIP Library**
4. Select the downloaded `.zip` file.

---

## 🔗 Connect Your Device to SciFy Cloud

Follow these steps to connect your ESP8266 / ESP32 to the **SciFy IoT Dashboard**:

### **Step 1 — Sign Up**
- Go to [https://connect.scify-tech.com/](https://connect.scify-tech.com/)
- Create a free account.

### **Step 2 — Create a Project**
- After login, click **"Create Project"**
- Add your **Project Name** and **Description**.

### **Step 3 — Add Your IoT Device**
- Go to **Devices → Add Device**.
- Enter **Device Name**, **Device Type** (ESP8266 / ESP32), and **Location**.
- The dashboard will generate:
  - **DEVICE_ID**
  - **AUTH_TOKEN**
  - **API_KEY**

### **Step 4 — Copy Credentials**
- Use these credentials in your Arduino code for **WiFi + SciFy IoT setup**.

---

## 📦 Usage Examples

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
  pinMode(2, OUTPUT);  // ESP8266 (D4) / ESP32 GPIO2
}

void loop() {
  // Listen for commands from SciFy Cloud Dashboard
  String command = scify.listen();

  if (command == "LED_ON") {
    digitalWrite(2, HIGH);
    Serial.println("LED Turned ON");
  } 
  else if (command == "LED_OFF") {
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

---

## 🖥️ SciFy IoT Dashboard Features

| Feature              | Description                                   |
|---------------------|-------------------------------------------|
| **Live Data**      | Monitor sensor readings in real-time.    |
| **Remote Control** | Control IoT devices from anywhere.      |
| **Project Logs**   | View device connection & data logs.     |
| **API Integration**| Connect with other services easily.     |

🌐 **Dashboard:** [https://connect.scify-tech.com/](https://connect.scify-tech.com/)  

---

## 📚 Documentation

Full documentation is available here:  
[https://docs.scify-tech.com/](https://docs.scify-tech.com/) *(Coming Soon)*

---

## 🛠️ Troubleshooting

| Issue | Solution |
|-------|----------|
| **Library not found** | Make sure you've installed it via Library Manager or `.zip`. |
| **Device not connecting** | Double-check WiFi credentials and `AUTH_TOKEN`. |
| **No data on dashboard** | Verify your `DEVICE_ID` and check serial logs. |
| **SSL Issues** | Update your board's certificates from Arduino IDE. |

---

## 🤝 Contributing

We welcome contributions!  
- Fork the repo  
- Create a feature branch  
- Submit a pull request 🚀

---

## 📧 Support

If you face issues, contact us at:  
📩 **support@scify-tech.com**  
🌐 **Website:** [https://scify-tech.com](https://scify-tech.com)  
📌 **Dashboard:** [https://connect.scify-tech.com/](https://connect.scify-tech.com/)

---

## 🏢 About SciFy Technologies

**SciFy Technologies Pvt Ltd** is a multi-domain R&D company focused on IoT, AI, and automation solutions.  
We provide **IoT hardware, cloud integration, project assistance,** and **student empowerment programs**.

🔗 **Website:** [https://scify-tech.com](https://scify-tech.com)  
📍 **Location:** Bangalore, India

---

## 🏷️ License

This project is licensed under the **MIT License**.  
Feel free to modify and distribute.

---

**Made with ❤️ by [SciFy Technologies](https://scify-tech.com)**
