#ifndef SCIFYIOT_H
#define SCIFYIOT_H

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

// Callback function types
typedef void (*CommandCallback)(const String& command, const String& commandId);
typedef void (*StatusCallback)(bool connected, bool authenticated);

class SciFyIoT {
private:
    // WebSocket client
    WebSocketsClient webSocket;
    
    // Configuration
    String _ssid;
    String _password;
    String _apiKey;
    String _secret;
    String _serverUrl;
    int _serverPort;
    String _serverPath;
    
    // State variables
    bool authenticated;
    unsigned long lastHeartbeat;
    unsigned long lastActivity;
    static const unsigned long heartbeatInterval = 25000;
    static const unsigned long connectionTimeout = 60000;
    
    // Callbacks
    CommandCallback _commandCallback;
    StatusCallback _statusCallback;
    
    // Private methods
    void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
    void authenticateDevice();
    void handleWebSocketMessage(const char* message);
    bool executeDefaultCommand(const String& command);
    void sendAck(const String& commandId, const String& status);
    void sendHeartbeat();
    void checkConnection();
    void connectWiFi();
    
    // Static callback wrapper for WebSocket events
    static SciFyIoT* instance;
    static void webSocketEventWrapper(WStype_t type, uint8_t * payload, size_t length);

public:
    // Constructor
    SciFyIoT();
    
    // Initialization
    void begin(const char* ssid, const char* password, const char* apiKey, const char* secret);
    void begin(const char* ssid, const char* password, const char* apiKey, const char* secret, 
               const char* serverUrl, int serverPort = 443, const char* serverPath = "/ws");
    
    // Main loop - call this in Arduino loop()
    void loop();
    
    // Status methods
    bool isConnected();
    bool isAuthenticated();
    bool isWiFiConnected();
    
    // Communication methods
    void sendSensorData(float temperature = 25.5, float humidity = 60.0);
    void sendCustomData(const String& dataType, JsonObject& data);
    void sendResponse(const String& commandId, const String& status, const String& data = "");
    
    // Callback setters
    void onCommandReceived(CommandCallback callback);
    void onStatusChanged(StatusCallback callback);
    
    // Utility methods
    void restart();
    void enableBuiltinLED(bool enable = true);
};

#endif