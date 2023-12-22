void setup() {
  // put your setup code here, to run once:
  
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // float power =analogRead(A0);
  float power =digitalRead(7);

  Serial.println(power);
  // digitalWrite(12, LOW);
  //   delay(100); 
  if(power > 0.5){
    Serial.println("Power is Occur");
    digitalWrite(12,LOW);
  delay(100);
    
    // digitalWrite(12,LOW);
    // delay(5);
  }else{
Serial.println("Power failure");
  digitalWrite(12, HIGH);
    delay(100);
  }
  
}
