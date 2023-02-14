//    FILE: Parkingsensor.ino
//  AUTHOR: Angelo Stracuzzi
// VERSION: 1.1
// PURPOSE:
//    DATE: 14.02.2023
//

#define PIN_TRIGGER 12 // Ultrasonic Sensor Pin
#define PIN_ECHO 13 // Ultrasonic Sensor Pin
#define PIN_NEO 14 // Neopixel Pin
#define NUMPIXELS 6 // Count of Neopixels
#include "Adafruit_NeoPixel.h"

// see Adafruit strandtest example for more information on possible values.
//sets up an Object called "pixels" that our instructions will be sent to
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEO, NEO_GRBW + NEO_KHZ800);


const int SENSOR_MAX_RANGE = 300;  // in cm
unsigned long duration;
unsigned int distance;
unsigned long previousMillis = 0;
const long interval = 100;
int blinkstate = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // NEOPIXEL
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();  // Set all pixel colors to 'off'
}

void loop() {
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);

  duration = pulseIn(PIN_ECHO, HIGH);
  distance = duration / 58;

  if (distance > SENSOR_MAX_RANGE || distance <= 0) {
    Serial.println("Out of sensor range!");
    flash();

  } else {
    Serial.println("Distance to object: " + String(distance) + " cm");

    for (int i = 0; i < 6; i++) pixels.setPixelColor(i, pixels.Color(0, 80, 0, 0)); // Set all Neopixel to green


    if (distance < 85) {
      pixels.setPixelColor(0, pixels.Color(50, 20, 0, 0)); // Set yellow
    }
    if (distance < 80) {
      pixels.setPixelColor(0, pixels.Color(100, 0, 0, 0)); // Set red
    }
    if (distance < 75) {
      pixels.setPixelColor(1, pixels.Color(100, 20, 0, 0)); // Set yellow
    }
    if (distance < 70) {
      pixels.setPixelColor(1, pixels.Color(100, 0, 0, 0)); // Set red
    }
    if (distance < 65) {
      pixels.setPixelColor(2, pixels.Color(100, 20, 0, 0)); // Set yellow
    }
    if (distance < 60) {
      pixels.setPixelColor(2, pixels.Color(100, 0, 0, 0)); // Set red
    }
    if (distance < 55) {
      pixels.setPixelColor(3, pixels.Color(100, 20, 0, 0)); // Set yellow
    }
    if (distance < 50) {
      pixels.setPixelColor(3, pixels.Color(100, 0, 0, 0)); // Set red
    }
    if (distance < 45) {
      pixels.setPixelColor(4, pixels.Color(100, 20, 0, 0)); // Set yellow
    }
    if (distance < 40) {
      pixels.setPixelColor(4, pixels.Color(100, 0, 0, 0)); // Set red
    }
    if (distance < 35) {
      pixels.setPixelColor(5, pixels.Color(100, 20, 0, 0)); // Set yellow
    }
    if (distance < 30) {
      pixels.setPixelColor(5, pixels.Color(100, 0, 0, 0)); // Set red
    }
  }

  pixels.show();
  delay(5);
  pixels.clear();
}

// Blink red and blue if Senor is out of Range
void flash() {    
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (blinkstate == 0) {
      blinkstate = 1;
      for (int i = 0; i < 6; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 100, 0));
    } else {
      for (int i = 0; i < 6; i++) pixels.setPixelColor(i, pixels.Color(100, 0, 0, 0));
      blinkstate = 0;
    }
    pixels.show();
  }
}