#include <Arduino.h>

#define SOUND_SPEED 0.032

const uint8_t trigPin = D6;
const uint8_t echoPin = D5;

uint32_t lastReadDistanceTime = 0;
const uint32_t readDistanceDebounce = 2000;

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  uint32_t currentTime = millis();
  if (currentTime - lastReadDistanceTime > readDistanceDebounce) 
  {
    lastReadDistanceTime = currentTime;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    uint32_t duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0) 
    {
      Serial.println("No signal");
    }
    else {
      float distance = duration * (SOUND_SPEED / 2);
      Serial.println("Distance: " + String(distance));
    }
  }
}
