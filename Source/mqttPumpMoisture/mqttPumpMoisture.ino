#include <WiFi.h>
#include <PubSubClient.h>

#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 7
#define sensorPin A0
#define relayPin 5


const char* ssid = "realme C21-Y";
const char* password = "123456789";
const char* mqttServer = "mqtt://192.168.1.157";
const int mqttPort = 1883;
const char* mqttUser = "thanu";
const char* mqttPassword = "1234";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(sensorPower, OUTPUT);
  pinMode(relayPin, OUTPUT);
	digitalWrite(sensorPower, HIGH);
	digitalWrite(relayPin, LOW);
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

  float moisture = readSensor(); // Get moisture value
  int moistureStatus = getMoistureValue(moisture);
  float temperature = 25.0; // Example temperature value
  float pH = 6.5; // Example pH value
  
  char payload[100]; // Create a char array to hold the combined payload
  snprintf(payload, sizeof(payload), "{\"moisture\": %.2f, \"temperature\": %.2f, \"pH\": %.2f}", moisture, temperature, pH);
  
  client.publish("sensor-values", payload); // Publish the combined payload

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

//  This function returns the analog soil moisture measurement
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle
	int val = analogRead(sensorPin);	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// Return analog moisture value
}

int getMoistureValue(int moisture){
  // Determine status of our soil
	if (moisture < soilWet) {
		Serial.println("Status: Soil is too wet");
    return 1;
	} else if (moisture >= soilWet && moisture < soilDry) {
		Serial.println("Status: Soil moisture is perfect");
    return 2;
	} else {
		Serial.println("Status: Soil is too dry - time to water!");
    return 0;
	}
}

void pumpOn(){
  Serial.println("pump on");
	digitalWrite(relayPin, HIGH);
}

void pumpOff(){
  Serial.println("pump off");
	digitalWrite(relayPin, LOW);
}