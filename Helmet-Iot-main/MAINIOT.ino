#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#define WIFI_SSID     "abc"
#define WIFI_PASSWORD "venuli1234"
#define WEB_API_KEY   "AIzaSyAPaoVjCk5hdbWDuF9x5Nn7IK6qwVD_lC8"
#define DATABASE_URL  "https://widearea-1738a-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define USER_EMAIL    "venulikalara@gmail.com"
#define USER_PASS     "12345678"

#define ALCO_DIGITAL  D5

FirebaseAuth   auth;
FirebaseConfig config;
FirebaseData   fbdo;

bool prevAlcoholDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(ALCO_DIGITAL, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("WiFi connected.");

  config.api_key      = WEB_API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email     = USER_EMAIL;
  auth.user.password  = USER_PASS;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  while (!Firebase.ready()) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("Firebase ready.");
}

void loop() {
  bool alcoholDetected = (digitalRead(ALCO_DIGITAL) == LOW);

  if (alcoholDetected && !prevAlcoholDetected) {
    Firebase.RTDB.setString(&fbdo, "/sensor/alcohol", "Alcohol detected");
    Serial.println("→ Alcohol detected!");
  }

  prevAlcoholDetected = alcoholDetected;
  delay(100);
}
