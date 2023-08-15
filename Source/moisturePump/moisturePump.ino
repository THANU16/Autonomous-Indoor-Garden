/* Change these values based on your calibration values */
#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 7
#define sensorPin A0
#define relayPin 5

void setup() {
	pinMode(sensorPower, OUTPUT);
    pinMode(relayPin, OUTPUT);
	digitalWrite(sensorPower, HIGH);
	digitalWrite(relayPin, LOW);
	Serial.begin(9600);
}

void loop() {
	//get the reading from the function below and print it
	int moisture = readSensor();
  int moistureStatus = getMoistureValue(moisture);
  if (moistureStatus == 0){
    pumpOn();
    delay(1000);
  }else if (moistureStatus == 1){
    pumpOff();
    delay(1000);
  }else if (moistureStatus == 2){
    pumpOff();
    delay(1000);
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

