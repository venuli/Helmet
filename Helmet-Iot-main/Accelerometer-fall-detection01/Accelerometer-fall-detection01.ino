#include <Wire.h>
#include <Adafruit_Sensor.h>        
#include <Adafruit_ADXL345_U.h>     

// Define pins 
#define SDAPin D2  
#define SCLPin D1  

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(); 

void setup() {
  Serial.begin(9600);

  // Initialize pins
  Wire.begin(SDAPin, SCLPin);

  if (!accel.begin()) {
    Serial.println("ADXL345 not detected");
    while (1); 
  }

  // Set range
  accel.setRange(ADXL345_RANGE_16_G);  
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;

  // Print acceleration data
  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  Z: "); Serial.print(z);
  
  // fall detection on X-axis
  if (x > 6.00 || x < -6.00) {
    Serial.println(" Fall Detected!");
  } else if (y > 6.00 || y < -6.00) {
    Serial.println(" Fall Detected!");
  } else if (z < 0) {
    Serial.println(" Fall Detected!");
  } else {
    Serial.println(" Normal");
  }

  delay(500);
}



