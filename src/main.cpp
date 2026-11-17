#include <Arduino.h>

int lightArray[]= {10, 9, 8};
int currentLight = 0;
unsigned long stateStart = 0;
unsigned long durations[] ={15000, 4000, 9000};
const int NUM_LIGHTS = 3;
const unsigned long MIN_GREEN = 3000;
const int BUTTON_PIN = 2;
volatile bool pedRequested = false;
volatile unsigned long lastPedRequest = 0;

void onButton(){
  unsigned long now = millis();
  if (now - lastPedRequest > 200) {
    pedRequested = true;
    lastPedRequest = now;
  }
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  digitalWrite(lightArray[currentLight], HIGH);
  stateStart = millis();
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButton, FALLING);
}

void loop() {
  if (millis() - stateStart >= durations[currentLight] || (currentLight ==0 && pedRequested && millis() - stateStart >= MIN_GREEN)) {
    digitalWrite(lightArray[currentLight], LOW);
    currentLight++;
    if (currentLight >= NUM_LIGHTS) {
      currentLight = 0;
    }
    if (currentLight == 0) {
      pedRequested = false;
    }
    digitalWrite(lightArray[currentLight], HIGH);
    stateStart = millis();
  }
}
