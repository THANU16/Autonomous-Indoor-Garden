/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 7
#define sensorPin A0
#define relayPin 5


const char* ssid = "realme C21-Y";
const char* password = "123456789";
const char* serverAddress = "http://192.168.219.117:5000/data"; // Replace with your server's address and port



void setup() {
  Serial.begin(115200);
  pinMode(sensorPower, OUTPUT);
  pinMode(relayPin, OUTPUT);
	digitalWrite(sensorPower, HIGH);
	digitalWrite(relayPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Create an HTTPClient object
  HTTPClient http;

  // Set the content type header
  http.addHeader("Content-Type", "application/json");

  // Create a JSON object
  StaticJsonDocument<200> jsonDoc; // Adjust the size based on your data

  // Populate the JSON object with data
  jsonDoc["sensor"] = "temperature";
  jsonDoc["value"] = 25.5;

  // Serialize the JSON object to a string
  String jsonData;
  serializeJson(jsonDoc, jsonData);

  // Send a POST request
  http.begin(serverAddress);
  Serial.println("Sending JSON data:");
  Serial.println(jsonData);
  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
  } else {
    Serial.println("Error on HTTP request");
  }

  // Disconnect and free resources
  http.end();
}

void loop() {
  // Your main loop
  float moisture = readSensor(); // Get moisture value
  int moistureStatus = getMoistureValue(moisture);
  // float temperature = 25.0; // Example temperature value
  // float pH = 6.5; // Example pH value

  if (moistureStatus == 2){
    pumpOn();
  }else{
    pumpOff();
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
