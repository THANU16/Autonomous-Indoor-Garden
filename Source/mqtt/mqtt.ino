#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqttServer = "mqtt://192.168.1.157";
const int mqttPort = 1883;
const char* mqttUser = "thanu";
const char* mqttPassword = "1234";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // WiFi.begin("Wokwi-GUEST", "", 6);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi Connected");
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  String data = "Hello from ESP32!";
  client.publish("moistrue", data.c_str());
  client.publish("temperature", data.c_str());
  client.publish("pH", data.c_str());

  delay(5000); // Send data every 5 seconds
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages (if needed)
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
