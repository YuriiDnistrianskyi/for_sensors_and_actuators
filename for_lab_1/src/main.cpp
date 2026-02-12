#include <Arduino.h>

uint8_t ledPin = D3;
uint8_t sensorPin = D4;

bool ledPinHigh = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  uint8_t state = digitalRead(sensorPin);
  if (state == 1) 
  {
    if (ledPinHigh != true) 
    {
      ledPinHigh = true;
      digitalWrite(ledPin, HIGH);
    }
  }
  else 
  {
    if (ledPinHigh != false) 
    {
      ledPinHigh = false;
      digitalWrite(ledPin; LOW);
    }
  }
}
