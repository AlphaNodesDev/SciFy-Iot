# 🚀 SciFy-IOT Control System

A complete **IoT device control platform** that lets you command ESP32/ESP8266 devices from anywhere in the world — now available at **[https://connect.scify-tech.com](https://connect.scify-tech.com)**!  
Perfect for students, makers, and anyone wanting to build smart devices.

---

## 🌍 Live Platform
- **Website:** [[https://connect.scify-tech.com](https://connect.scify-tech.com)  ]
- **API Base URL:** `https://connect.scify-tech.com`
- **GitHub Repo:** [https://github.com/AlphaNodesDev/SciFy-Iot](https://github.com/AlphaNodesDev/SciFy-Iot)

---

## 🎯 What This System Does

Think of this as a **remote control for your electronics** that works from anywhere with internet:

- 💡 Turn lights on/off from your phone
- 🚪 Control door locks remotely  
- 🌡️ Monitor temperature sensors
- 🤖 Control robot cars from across the world
- 🔧 And much more!

## 🧠 How It Works (Simple Explanation)

```
Your Phone/Computer  →  Internet  →  SciFi-IOT Platform  →  Your Device
     (Send Command)      (Cloud)      (Process & Route)      (LED turns on!)
```

1. **You create a project** and get special "keys" (like passwords for your devices)
2. **Program your ESP32/ESP8266** with these keys so it knows it's yours
3. **Send commands** from any phone, computer, or website
4. **Your device receives** and executes the commands instantly!

## 🎓 Perfect for Students

This system is designed to be **easy enough for 8th graders** to understand:

- ✅ No complex server setup required
- ✅ Works with simple Arduino code
- ✅ Visual interface for testing
- ✅ Detailed step-by-step guides
- ✅ Ready-to-copy code examples

## 🌟 Features

### 🎮 Control Panel
- **Quick Buttons**: One-click commands (LED ON, LED OFF, etc.)
- **Custom Commands**: Create your own buttons for any action
- **String & JSON**: Support for simple text and complex data commands
- **Real-time**: Instant communication with your devices

### 🔧 Device Support
- **ESP32** and **ESP8266** microcontrollers
- **Arduino IDE** compatible
- **WiFi-based** communication
- **Multiple devices** per project

### 💻 Programming Languages
- **JavaScript** (websites, React, Vue, etc.)
- **Python** (automation, AI, data science)
- **cURL** (command line testing)
- **Any language** that can make HTTP requests

### 🔐 Security
- **API Keys** for device identification
- **Secret Keys** for secure communication
- **Project isolation** (your devices only respond to you)

## 🔑 Getting Your API Keys

### Step 1: Create Account
1. Visit [[https://connect.scify-tech.com](https://connect.scify-tech.com)]
2. Click **"Sign Up"** and create your free account
3. Verify your email address

### Step 2: Create a Project
1. Go to **"Projects"** in the dashboard
2. Click **"Create New Project"**
3. Enter a project name (e.g., "My Smart LED")
4. Your **API Key** and **Secret Key** will be automatically generated

### Step 3: Find Your Keys
- Navigate to **"API Keys"** section in the dashboard
- Copy your **API Key** and **Secret Key**
- Use these in your Arduino code and API calls

⚠️ **Important:** Keep your keys private and never share them publicly!

---

## 💎 Subscription Plans

### 🆓 Free Tier
- **30,000 API calls/month**
- Unlimited projects
- Basic support
- Perfect for learning and small projects

### ⭐ Premium Tier  
- **60,000 API calls/month**
- All Free features
- Priority support
- Advanced analytics

### 🚀 Enterprise Tier
- **Unlimited API calls**
- All Premium features
- Dedicated support
- Custom integrations
- SLA guarantee

### How to Upgrade
1. Go to **"Settings"** → **"Subscription"** in your dashboard
2. Choose your plan
3. Complete payment securely
4. Enjoy increased limits instantly!

---

## 🚀 Quick Start Guide

### Step 1: Get Your API Keys
Follow the **"🔑 Getting Your API Keys"** section above to create your account and get credentials.

### Step 2: Create Your First Project
1. In the dashboard, go to **"Projects"**
2. Click **"Create New Project"**
3. Name it something like "My Smart Home"
4. Note down your **API Key** and **Secret Key**

### Step 2: Program Your Device
1. Open Arduino IDE
2. Copy the ESP32/ESP8266 code from **API Docs → Device Code**
3. Replace `YOUR_WIFI_NAME` and `YOUR_WIFI_PASSWORD`
4. Upload to your device

### Step 3: Test It Works
1. Go to **Dashboard → Control Panel**
2. Click **"POWER ON"** button
3. Watch your device LED turn on! 🎉

## 📚 API Documentation

### 🔗 Main Endpoint
```
POST https://connect.scify-tech.com/sendSignal
```

### 📝 Request Format
```json
{
  "apiKey": "your-api-key-here",
  "secret": "your-secret-key-here", 
  "command": "LED_ON"
}
```

### ⚡ Quick JavaScript Example
```javascript
// Replace with your actual API keys
fetch("https://connect.scify-tech.com/sendSignal", {
  method: "POST",
  headers: {"Content-Type": "application/json"},
  body: JSON.stringify({
    apiKey: "your-api-key",
    secret: "your-secret-key",
    command: "LED_ON"
  })
})
.then(response => response.json())
.then(data => console.log("Success:", data))
.catch(error => console.error("Error:", error));
```

### 🐍 Quick Python Example
```python
import requests

# Replace with your actual API keys
response = requests.post(
  "https://connect.scify-tech.com/sendSignal",
  json={
    "apiKey": "your-api-key",
    "secret": "your-secret-key", 
    "command": "LED_ON"
  }
)

print(f"Status: {response.status_code}")
print(f"Response: {response.json()}")
```

### Example with cURL
```bash
curl -X POST https://connect.scify-tech.com/sendSignal \
  -H "Content-Type: application/json" \
  -d '{
    "apiKey": "your-api-key",
    "secret": "your-secret-key",
    "command": "LED_ON"
  }'
```

## 🔧 Arduino Device Code

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const String apiKey = "your-api-key-here";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); // Built-in LED
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected!");
}

void loop() {
  checkForCommands();
  delay(5000); // Check every 5 seconds
}

void checkForCommands() {
  HTTPClient http;
  http.begin("https://connect.scify-tech.com/getCommands");
  http.addHeader("Content-Type", "application/json");
  
  String payload = "{\"apiKey\":\"" + apiKey + "\"}";
  int httpCode = http.POST(payload);
  
  if (httpCode == 200) {
    String response = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);
    
    String command = doc["command"];
    if (command == "LED_ON") {
      digitalWrite(2, HIGH);
      Serial.println("LED ON");
    } else if (command == "LED_OFF") {
      digitalWrite(2, LOW); 
      Serial.println("LED OFF");
    }
  }
  http.end();
}
```

## 🛠️ Common Commands

| Command | Description | Device Action |
|---------|-------------|---------------|
| `LED_ON` | Turn LED on | `digitalWrite(2, HIGH)` |
| `LED_OFF` | Turn LED off | `digitalWrite(2, LOW)` |
| `SERVO_90` | Rotate servo | `servo.write(90)` |
| `SENSOR_READ` | Read sensors | Return sensor data |
| `RELAY_ON` | Turn relay on | Control high-power devices |
| `BUZZER_BEEP` | Sound buzzer | Make noise alert |

## 🧪 Testing Your Setup

### Method 1: Use Control Panel (Easiest)
1. Go to **Dashboard** 
2. Select your project
3. Click **Quick Command** buttons
4. Watch your device respond!

### Method 2: Browser Console  
1. Press **F12** to open browser tools
2. Go to **Console** tab
3. Copy and run the JavaScript example above
4. Check if device responds

### Method 3: Command Line
1. Open terminal/command prompt
2. Run the cURL command from API docs
3. Verify the response

## 🐛 Troubleshooting

### Device Not Responding?
- ✅ Check WiFi connection (device must be online)
- ✅ Verify API keys are correct in device code
- ✅ Make sure device is powered on
- ✅ Check Serial Monitor for error messages

### API Errors?
- ✅ Verify API Key and Secret Key are correct
- ✅ Check command spelling (case-sensitive)
- ✅ Ensure internet connection works
- ✅ Try the test methods above

### LED Not Working?
- ✅ Try different pin numbers (2, 13, LED_BUILTIN)
- ✅ Check if LED is connected properly
- ✅ Test with external LED + resistor
- ✅ Verify digitalWrite commands in code

## 📱 What You Can Build

### 🏠 Smart Home Projects
- **Smart Lights**: Control room lights from phone
- **Smart Door**: Lock/unlock with app or website  
- **Temperature Monitor**: Get alerts when too hot/cold
- **Security System**: Motion detection with notifications

### 🤖 Robotics Projects  
- **Remote Robot Car**: Drive from anywhere in the world
- **Drone Control**: Control flight patterns remotely
- **Robot Arm**: Control servo movements precisely
- **Pet Feeder**: Schedule feeding times automatically

### 🌱 Garden & Agriculture
- **Smart Watering**: Water plants based on soil moisture
- **Greenhouse Control**: Manage temperature and humidity  
- **Weather Station**: Monitor local weather conditions
- **Growth Lights**: Control LED growing lights

### 🎮 Fun Projects
- **Remote Pranks**: Surprise friends with IoT tricks
- **Game Controllers**: Create custom game interfaces
- **Art Installations**: Interactive art that responds to commands
- **Magic Tricks**: IoT-powered magic illusions

## 🎯 Learning Path

### Beginner (Start Here!)
1. **Create first project** and get API keys
2. **Upload basic LED code** to ESP32/ESP8266  
3. **Test with Control Panel** - turn LED on/off
4. **Try different commands** and see what happens

### Intermediate  
1. **Add more components** (servo, sensor, buzzer)
2. **Create custom commands** for your components
3. **Build a simple robot** or smart device
4. **Use JSON commands** for complex data

### Advanced
1. **Build mobile app** to control devices
2. **Create web dashboard** with real-time data
3. **Add multiple sensors** and data logging
4. **Build complete IoT system** for your home

## 🔐 Security Best Practices

### ✅ Do This:
- Keep your **Secret Key private** (never share publicly)
- Use different projects for different devices
- Regularly check what commands your devices accept
- Test with simple commands before complex ones

### ❌ Don't Do This:
- Don't put Secret Key in public GitHub repos
- Don't share API credentials with untrusted people
- Don't hardcode secrets in public websites
- Don't forget to secure your WiFi network

## 🆘 Need Help?

### 📖 Documentation
- **API Docs**: Complete code examples and guides
- **Control Panel**: Visual interface for testing
- **Project Settings**: Manage your devices and keys

### 🤝 Support
- Check **Troubleshooting** section above
- Test with simple commands first
- Use **Serial Monitor** to see device messages
- Try the browser console method for testing

## 🎉 Success Stories

*"I built a smart dog feeder that I can control from work!" - Sarah, 9th grade*

*"My IoT security camera sends me alerts when someone enters my room!" - Alex, 10th grade*  

*"I control my entire bedroom lighting system from my phone!" - Maria, 8th grade*

## 🚀 Get Started Now!

1. **Go to Projects page** → Create new project
2. **Copy the device code** → Upload to your ESP32/ESP8266  
3. **Test in Control Panel** → Watch the magic happen!
4. **Build something awesome** → Share your creation!

---
