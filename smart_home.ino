#define BLYNK_TEMPLATE_ID "TMPL3zKXTiKjp"
#define BLYNK_TEMPLATE_NAME "smart home"
#define BLYNK_AUTH_TOKEN "FQSivrPnuhelg2cgRzuCrMYa1sgc-sxn"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Define IR sensor pin
#define IR_SENSOR_PIN 4  // GPIO 4 for example, change to your actual pin
// Define Light pin
#define LIGHT_PIN 2 // GPIO 2 for example, change to your actual pin

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "wifi name";
char pass[] = "password";

BLYNK_WRITE(V2){
  digitalWrite(LIGHT_PIN, param.asInt()); // Turn on/off light based on person detection
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Initialize IR sensor pin
  pinMode(IR_SENSOR_PIN, INPUT);

  // Initialize Light pin
  pinMode(LIGHT_PIN, OUTPUT);
}

void loop() {
  Blynk.run();

  // Read IR sensor
  int irValue = digitalRead(IR_SENSOR_PIN);

  // If a person is detected by the IR sensor
  if (irValue == HIGH) {
    Serial.println("Person detected!");
    Blynk.virtualWrite(V2, 1); // Turn on light
  } else {
    Serial.println("No person detected.");
    Blynk.virtualWrite(V2, 0); // Turn off light
  }

  delay(1000); // Delay to avoid reading too frequently
}
