#include <SoftwareSerial.h>

#define TOUCH_PIN         15
#define GPS_RX_PIN        13
#define GPS_TX_PIN        12
#define ACCEL_X_PIN       5
#define ACCEL_Y_PIN       4
#define BLINK_SENSOR_PIN  0
#define ALCOHOL_DIGITAL   2
#define ALCOHOL_ANALOG    A0

bool systemOn = false;

SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  digitalWrite(TOUCH_PIN, LOW);

  pinMode(ACCEL_X_PIN, INPUT);
  pinMode(ACCEL_Y_PIN, INPUT);
  pinMode(BLINK_SENSOR_PIN, INPUT);
  pinMode(ALCOHOL_DIGITAL, INPUT);

  Serial.begin(115200);
  gpsSerial.begin(9600);

  Serial.println("Helmet system ready. Waiting for rider to wear the helmet...");
}

void loop() {
  int touchValue = digitalRead(TOUCH_PIN);

  if (touchValue == HIGH && !systemOn) {
    Serial.println("Helmet worn. System activating...");
    systemOn = true;
    activateHelmetSystem();
  } else if (touchValue == LOW && systemOn) {
    Serial.println("Helmet removed. System deactivating...");
    systemOn = false;
    deactivateHelmetSystem();
  }

  if (systemOn) {
    runHelmetSensors();
  }

  delay(100);
}

void activateHelmetSystem() {
  Serial.println("Helmet is ON.");
}

void deactivateHelmetSystem() {
  Serial.println("Helmet is OFF.");
}

void runHelmetSensors() {
  Serial.println("Running sensors...");

  //GPS
  while (gpsSerial.available()) {
    String gpsData = gpsSerial.readStringUntil('\n');
    Serial.print("GPS: ");
    Serial.println(gpsData);
  }

  //Accelerometer
  int accelX = digitalRead(ACCEL_X_PIN);
  int accelY = digitalRead(ACCEL_Y_PIN);
  Serial.print("Accelerometer -> X: ");
  Serial.print(accelX);
  Serial.print(" | Y: ");
  Serial.println(accelY);

  //Eye Blink Sensor
  int blinkDetected = digitalRead(BLINK_SENSOR_PIN);
  Serial.print("Eye Blink: ");
  Serial.println(blinkDetected == HIGH ? "Blink Detected" : "No Blink");

  //Alcohol Sensor
  int alcoholDigital = digitalRead(ALCOHOL_DIGITAL);
  int alcoholAnalog = analogRead(ALCOHOL_ANALOG);
  Serial.print("Alcohol Level -> Digital: ");
  Serial.print(alcoholDigital);
  Serial.print(" | Analog: ");
  Serial.println(alcoholAnalog);

  Serial.println("-----------------------------------------------------------");
  delay(1000);
}