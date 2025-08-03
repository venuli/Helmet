#define sensorDigital 14  // D5 GPIO14 
#define sensorAnalog A0  

void setup() {
  pinMode(sensorDigital, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool digital = digitalRead(sensorDigital);
  int analog = analogRead(sensorAnalog);
  
  if (digital == 0) {
    Serial.println("Detected alcohol");
  } else {
    Serial.println("No alcohol");
  }

  delay(1000);
}
