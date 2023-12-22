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

#define soilWet 3000   // Define max value we consider soil 'wet'
#define soilDry 4000   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 27
#define sensorPin 34
#define relayPin 18

// const char* ssid = "realme C21-Y";
// const char* password = "123456789";
const char* ssid = "SLT-Fiber";
const char* password = "@Home#321";
const char* serverName = "http://192.168.1.3:5000/data"; // Replace with your server's address and port

void setup() {
  Serial.begin(115200);

  pinMode(sensorPower, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(sensorPower, HIGH);
  digitalWrite(relayPin, HIGH);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float moisture = readSensor(); // Get moisture value
  int moistureStatus = getMoistureValue(moisture);
  // float temperature = 25.0; // Example temperature value
  // float pH = 6.5; // Example pH value
  Serial.println(moisture);
  Serial.println(moistureStatus);


  if (moistureStatus == 0) {
    digitalWrite(relayPin, LOW);
    delay(200);
  } else {
    digitalWrite(relayPin, HIGH);
    delay(20);
  }

  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);

    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Data to send with HTTP POST
    String moistureString = String(moisture);
    String temperatureString = "24.25"; // i put example temperature value
    String pHString = "7.8"; // i put example pH value
    String httpRequestData = "moisture=" + moistureString + "&temperature=" + temperatureString + "&pH=" + pHString;
    Serial.println(httpRequestData);
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(5000);
}

// This function returns the analog soil moisture measurement
int readSensor() {
  digitalWrite(sensorPower, HIGH); // Turn the sensor ON
  delay(10);                        // Allow power to settle
  int val = analogRead(sensorPin);  // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);  // Turn the sensor OFF
  return val;                       // Return analog moisture value
}

int getMoistureValue(int moisture) {
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

void pumpOn() {
  Serial.println("pump on");
  digitalWrite(relayPin, LOW);
}

void pumpOff() {
  Serial.println("pump off");
  digitalWrite(relayPin, HIGH);
}
