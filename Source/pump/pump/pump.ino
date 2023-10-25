//Motor
#define ENA 9 // Enable/speed motor Front Left D10->ENA L298N Front Side
#define IN_1 7 // L298N #2 in 1 motor Front Left D8->IN1 L298N Front Side
#define IN_2 8 // L298N #2 in 2 motor Front Left D9->IN2 L298N Front Side


void setup(){
   pinMode(ENA, OUTPUT);

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);

   //Serial.begin(115200);
   Serial.begin(9600);                             // start the serial port
}


void loop(){
  delay(2000); 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 240);
  delay(5000);
  analogWrite(ENA, 0);
  delay(5000);
}

