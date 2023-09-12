/* Change these values based on your calibration values */
#define soilWet 3000   // Define max value we consider soil 'wet'
#define soilDry 4000   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 27
#define sensorPin 34

void setup() {
	pinMode(sensorPower, OUTPUT);
	
	// Initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);
	
	Serial.begin(9600);
}

void loop() {
	//get the reading from the function below and print it
	int moisture = readSensor();
	Serial.print("Analog Output: ");
	Serial.println(moisture);
  int moistureStatus = getMoistureValue(moisture);
  Serial.println(moistureStatus);
	
	delay(1000);	// Take a reading every second for testing
					// Normally you should take reading perhaps once or twice a day
	Serial.println();
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