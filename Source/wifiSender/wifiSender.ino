#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "realme C21-Y";
const char* password = "123456789";
const char* serverAddress = "localhost";
const int serverPort = 5000; // Replace with your server's port

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

  // Your data collection code goes here

  // Create an HTTPClient object
  HTTPClient http;

  // Set the server address and port
  String serverURL = "http://" + String(serverAddress) + ":" + String(serverPort) + "/data";

  // Set the content type header
  http.addHeader("Content-Type", "application/json");

  // Prepare your data as JSON (replace with your own data)
  String jsonData = "{\"sensor\": \"temperature\", \"value\": 25.5}";

  // Send a POST request with the JSON data
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
  // Your main loop code goes here
}
