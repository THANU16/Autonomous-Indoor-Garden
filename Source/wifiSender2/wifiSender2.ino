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


const char* ssid = "realme C21-Y";
const char* password = "123456789";
const char* serverAddress = "http://192.168.219.117:5000/data"; // Replace with your server's address and port



void setup() {
  Serial.begin(115200);
  delay(10);

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
  int httpResponseCode = http.POST("hi connect");

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
}
