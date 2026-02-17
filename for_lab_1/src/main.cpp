#include <Arduino.h>
#define DEBOUNCE 300

uint8_t ledGreenPin = D5;
uint8_t ledRedPin = D6;
uint8_t sensorPin = D2;

bool ledPinHigh = 0;
uint32_t lastReadSensor = 0;

void setup() 
{
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
}

void loop() 
{
  uint32_t readSensorTime = millis();
  if (readSensorTime - lastReadSensor >= DEBOUNCE) 
  {
    lastReadSensor = readSensorTime;

    uint8_t state = digitalRead(sensorPin); //
    if (state == 1) 
    {
      if (ledPinHigh != true) 
      {
        ledPinHigh = true;
        digitalWrite(ledGreenPin, HIGH);
        digitalWrite(ledRedPin, LOW);
      }
    }
    else 
    {
      if (ledPinHigh != false) 
      {
        ledPinHigh = false;
        digitalWrite(ledGreenPin, LOW);
        digitalWrite(ledRedPin, HIGH);
      }
    }

  }
}
