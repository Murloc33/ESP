#define WIFI_SSID "RT-GPON-0438"
#define WIFI_PASSWORD "D49i4i7hge"

// #define WIFI_SSID "Galaxy A51 ADE7"
// #define WIFI_PASSWORD "zcnn6255"

#define MQTT_BROKER "MQTT_BROKER"
#define MQTT_USERNAME "MQTT_USERNAME"
#define MQTT_PASSWORD "MQTT_PASSWORD"
#define MQTT_PORT 1883

#define DNS_HOST "esp8266strip"
#define UPDATE_PATH "/update"
#define UPDATE_USERNAME "admin"
#define UPDATE_PASSWORD "admin?"

#define RELAY_PIN 5
#define LED_PIN 2
#define LED_COUNT 27
#define STRIP_MID_POINT 14


// /*Переподключиться к wifi когда не получается подлючиться к MQTT.
// Активировать если лента рандомно зависает на подключении к MQTT или перезагржается*/
// #define WIFI_RECONECT_WHEN_MQTT_FAIL 0
// /*fail save - при невозможности подключиться к wifi,
// создаёт свою wifi точку к которой можно подключиться и загрузить прошивку
// (адрес обычно 192.168.1.4)*/
// #define HOST_WIFI_AP 1
// #if HOST_WIFI_AP
// #define HOSTED_WIFI_SSID     "Esp8266-strip-wifi"
// #define HOSTED_WIFI_PASSWORD "my_esp_passwd"
// #endif
