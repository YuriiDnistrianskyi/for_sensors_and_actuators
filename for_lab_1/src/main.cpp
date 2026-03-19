#include <Arduino.h>
#define DEBOUNCE 300


uint8_t ledGreenPin = 18; 
uint8_t ledRedPin = 4;
uint8_t sensorPin = 5;

bool ledPinHigh = 0;
uint32_t lastReadSensor = 0;

void setup() 
{
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() 
{
  uint32_t readSensorTime = millis();
  if (readSensorTime - lastReadSensor >= DEBOUNCE) 
  {
    lastReadSensor = readSensorTime;

    uint8_t state = digitalRead(sensorPin); 
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