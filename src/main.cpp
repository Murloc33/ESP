#include <ESP8266WiFi.h>
#include <network.h>
#include <effects.h>
#include <string>
#include <ArduinoJson.h>


Effects effects;
// Network network(effects);
ESP8266WebServer httpServer(80);

void handle_WIFI(const String& info) {
  effects.set_effect(0);
  Serial.print(info);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 15000) {
    ESP.wdtFeed();
    effects.show();
    delay(50);
    Serial.print(".");
  }
  
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi");
    ESP.restart(); // Или другая логика обработки ошибки
    return;
  }
  
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupServer() {
  Serial1.println();
  handle_WIFI("Connecting to WiFi");
  Serial.println();
  Serial.print(WiFi.localIP());
  Serial.println();

  httpServer.on("/mode", HTTP_POST, [&](){
    int mode = httpServer.arg("mode").toInt();
    effects.set_effect(mode);
    Serial.print("Switch mode to " + String(mode));
    Serial.println();
    httpServer.send(200);
  });

  httpServer.on("/brightness", HTTP_POST, [&](){
    int brightness = httpServer.arg("brightness").toInt();
    effects.set_brightness(brightness);
    Serial.print("Switch brightness to " + String(brightness));
    Serial.println();
    httpServer.send(200);
  });

  httpServer.on("/color", HTTP_POST, [&](){
    uint32_t color = static_cast<uint32_t>(httpServer.arg("color").toInt());
    effects.set_color(color);
    Serial.print("Switch color to " + String(color));
    Serial.println();
    httpServer.send(200);
  });

  httpServer.on("/state", HTTP_POST, [&](){
    uint32_t state = static_cast<uint32_t>(httpServer.arg("state").toInt());
    effects.set_state(state);
    Serial.print("Switch state to " + String(state));
    Serial.println();
    httpServer.send(200);
  });

  httpServer.on("/info", HTTP_GET, [&](){
    DynamicJsonDocument doc(256);  // Выделяем память под JSON
  
    // Заполняем JSON
    doc["mode"] = effects.get_effect();
    doc["state"] = effects.get_state();
    doc["brightness"] = effects.get_brightness();
    doc["color"] = effects.get_color();
  
    // Сериализуем JSON в строку
    String jsonResponse;
    serializeJson(doc, jsonResponse);
  
    httpServer.send(200, "application/json", jsonResponse);
  });

  httpServer.begin();
}

void setup() {
  ESP.wdtDisable();
  Serial.begin(115200);
  randomSeed(analogRead(A0));
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  strip_init();
  // effects.set_effect(0);
  effects.set_wheel_color(random(255));
  setupServer();
}

void loop() {
  ESP.wdtFeed();
  
  static unsigned long lastWifiCheck = 0;
  if(millis() - lastWifiCheck > 5000) { // Проверяем соединение каждые 5 сек
    lastWifiCheck = millis();
    
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected, reconnecting...");
      WiFi.disconnect();
      delay(100);
      handle_WIFI("Reconnecting to WiFi");
      
      if(WiFi.status() == WL_CONNECTED) {
        httpServer.stop();
        delay(100);
        httpServer.begin();
      }
    }
  }
  
  httpServer.handleClient();
  effects.show();
}
