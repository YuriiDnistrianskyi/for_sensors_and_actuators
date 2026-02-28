#include <Arduino.h>
#define READ_PULSE_TIME 1000UL

const uint8_t tachPin = D2;

uint32_t pulseCount = 0;
uint32_t lastReadPulse = 0;

void IRAM_ATTR tachInterrupt() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(tachPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(tachPin), tachInterrupt, FALLING);
}

void loop() {
  uint32_t currentTime = millis();
  if (currentTime - lastReadPulse >= READ_PULSE_TIME) {
    lastReadPulse = currentTime;

    noInterrupts();
    uint32_t rpm = (pulseCount / 2) * 60;
    pulseCount = 0;
    interrupts();

    Serial.println("RPM: " + String(rpm)); 
  }
}
