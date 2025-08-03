const int inPin = D3;
const int Vbmotor = D5;
int val = 0;

unsigned long eyeClosedStart = 0;
const unsigned long warningTime = 1000;
bool alertSent = false;

void setup() {
  pinMode(inPin, INPUT_PULLUP);
  pinMode(Vbmotor, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  val = digitalRead(inPin);

  if (val == HIGH) {
    if (eyeClosedStart == 0) {
      eyeClosedStart = millis();
    } else if (millis() - eyeClosedStart >= warningTime) {
      if (!alertSent) {
        Serial.println("Alert");
        digitalWrite(Vbmotor, HIGH);
        alertSent = true;
      }
    }
  } else {
    eyeClosedStart = 0;
    alertSent = false;
    Serial.println("Eye open");
    digitalWrite(Vbmotor, LOW);
  }

  delay(100);
}
