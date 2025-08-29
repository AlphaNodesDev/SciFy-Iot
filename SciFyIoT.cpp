#include "SciFyIoT.h"

// Static instance pointer for callback wrapper
SciFyIoT* SciFyIoT::instance = nullptr;

// Constructor
SciFyIoT::SciFyIoT() {
    authenticated = false;
    lastHeartbeat = 0;
    lastActivity = 0;
    _commandCallback = nullptr;
    _statusCallback = nullptr;
    _serverUrl = "api.scify-tech.com";
    _serverPort = 443;
    _serverPath = "/ws";
    
    // Set static instance for callback wrapper
    instance = this;
}

// Initialize with default server
void SciFyIoT::begin(const char* ssid, const char* password, const char* apiKey, const char* secret) {
    begin(ssid, password, apiKey, secret, "api.scify-tech.com", 443, "/ws");
}

// Initialize with custom server
void SciFyIoT::begin(const char* ssid, const char* password, const char* apiKey, const char* secret, 
                     const char* serverUrl, int serverPort, const char* serverPath) {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("[SciFyIoT] Starting...");
    
    _ssid = ssid;
    _password = password;
    _apiKey = apiKey;
    _secret = secret;
    _serverUrl = serverUrl;
    _serverPort = serverPort;
    _serverPath = serverPath;
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    
    // Connect to WiFi
    connectWiFi();
    
    if (WiFi.status() == WL_CONNECTED) {
        webSocket.beginSSL(_serverUrl.c_str(), _serverPort, _serverPath.c_str());
        webSocket.onEvent(webSocketEventWrapper);
        webSocket.setReconnectInterval(5000);
        webSocket.enableHeartbeat(15000, 3000, 2);
        lastActivity = millis();
        Serial.println("[SciFyIoT] Initialized successfully!");
    } else {
        Serial.println("[SciFyIoT] WiFi connection failed");
    }
}

// Main loop processing
void SciFyIoT::loop() {
    webSocket.loop();
    
    if (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
    }
    
    if (authenticated && millis() - lastHeartbeat > heartbeatInterval) {
        sendHeartbeat();
        lastHeartbeat = millis();
    }
    
    checkConnection();
    delay(50);
}

// Status methods
bool SciFyIoT::isConnected() {
    return webSocket.isConnected();
}

bool SciFyIoT::isAuthenticated() {
    return authenticated;
}

bool SciFyIoT::isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

// Connect to WiFi
void SciFyIoT::connectWiFi() {
    WiFi.begin(_ssid.c_str(), _password.c_str());
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
        delay(500);
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("[WiFi] Connected");
    } else {
        Serial.println("[WiFi] Connection failed");
    }
}

// Static callback wrapper
void SciFyIoT::webSocketEventWrapper(WStype_t type, uint8_t * payload, size_t length) {
    if (instance) {
        instance->webSocketEvent(type, payload, length);
    }
}

// WebSocket event handler
void SciFyIoT::webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    lastActivity = millis();
    
    switch (type) {
        case WStype_DISCONNECTED:
            authenticated = false;
            digitalWrite(LED_BUILTIN, HIGH);
            if (_statusCallback) _statusCallback(false, false);
            break;
            
        case WStype_CONNECTED:
            authenticated = false;
            authenticateDevice();
            if (_statusCallback) _statusCallback(true, false);
            break;
            
        case WStype_TEXT:
            handleWebSocketMessage((char*)payload);
            break;
            
        case WStype_ERROR:
            Serial.printf("[WS] Error: %s\n", payload);
            break;
    }
}

// Authenticate with server
void SciFyIoT::authenticateDevice() {
    DynamicJsonDocument doc(256);
    doc["type"] = "auth";
    doc["apiKey"] = _apiKey;
    doc["secret"] = _secret;
    
    String message;
    serializeJson(doc, message);
    webSocket.sendTXT(message);
}

// Handle incoming WebSocket messages
void SciFyIoT::handleWebSocketMessage(const char* message) {
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, message);
    
    if (error) return;
    
    String type = doc["type"];
    
    if (type == "auth_success") {
        authenticated = true;
        digitalWrite(LED_BUILTIN, LOW);
        lastHeartbeat = millis();
        if (_statusCallback) _statusCallback(true, true);
    }
    else if (type == "auth_error") {
        authenticated = false;
        digitalWrite(LED_BUILTIN, HIGH);
        if (_statusCallback) _statusCallback(true, false);
    }
    else if (type == "command" && authenticated) {
        String commandId = doc["id"];
        String payload = doc["payload"];
        
        bool handled = executeDefaultCommand(payload);
        
        if (!handled && _commandCallback) {
            _commandCallback(payload, commandId);
        } else if (handled) {
            sendAck(commandId, "executed");
        } else {
            sendAck(commandId, "failed");
        }
    }
}

// Execute default commands
bool SciFyIoT::executeDefaultCommand(const String& command) {
    if (command == "LED_ON") {
        digitalWrite(LED_BUILTIN, LOW);
        return true;
    }
    else if (command == "LED_OFF") {
        digitalWrite(LED_BUILTIN, HIGH);
        return true;
    }
    else if (command == "STATUS") {
        sendSensorData();
        return true;
    }
    else if (command == "RESTART") {
        ESP.restart();
        return true;
    }
    
    return false;
}

// Send acknowledgement
void SciFyIoT::sendAck(const String& commandId, const String& status) {
    DynamicJsonDocument doc(256);
    doc["type"] = "ack";
    doc["commandId"] = commandId;
    doc["status"] = status;
    doc["timestamp"] = millis();
    
    String message;
    serializeJson(doc, message);
    webSocket.sendTXT(message);
}

// Send heartbeat
void SciFyIoT::sendHeartbeat() {
    if (!authenticated) return;
    
    DynamicJsonDocument doc(128);
    doc["type"] = "heartbeat";
    doc["timestamp"] = millis();
    
    String message;
    serializeJson(doc, message);
    webSocket.sendTXT(message);
}

// Send sensor data
void SciFyIoT::sendSensorData(float temperature, float humidity) {
    DynamicJsonDocument doc(256);
    doc["type"] = "sensor_data";
    doc["payload"]["temperature"] = temperature;
    doc["payload"]["humidity"] = humidity;
    doc["payload"]["uptime"] = millis();
    doc["payload"]["free_heap"] = ESP.getFreeHeap();
    doc["payload"]["wifi_rssi"] = WiFi.RSSI();
    doc["timestamp"] = millis();
    
    String message;
    serializeJson(doc, message);
    webSocket.sendTXT(message);
}

// Send custom data
void SciFyIoT::sendCustomData(const String& dataType, JsonObject& data) {
    DynamicJsonDocument doc(512);
    doc["type"] = dataType;
    doc["payload"] = data;
    doc["timestamp"] = millis();
    
    String message;
    serializeJson(doc, message);
    webSocket.sendTXT(message);
}

// Send response
void SciFyIoT::sendResponse(const String& commandId, const String& status, const String& data) {
    sendAck(commandId, status);
}

// Check connection health
void SciFyIoT::checkConnection() {
    if (millis() - lastActivity > connectionTimeout) {
        webSocket.disconnect();
        authenticated = false;
        lastActivity = millis();
    }
}

// Set command callback
void SciFyIoT::onCommandReceived(CommandCallback callback) {
    _commandCallback = callback;
}

// Set status callback
void SciFyIoT::onStatusChanged(StatusCallback callback) {
    _statusCallback = callback;
}

// Restart device
void SciFyIoT::restart() {
    ESP.restart();
}

// Enable/disable built-in LED
void SciFyIoT::enableBuiltinLED(bool enable) {
    if (enable) {
        pinMode(LED_BUILTIN, OUTPUT);
    }
}