#include <Arduino.h>

#define SOUND_SPEED 0.034

const int trigPin = 5;
const int echoPin = 18;

uint32_t duration;
float distanceCm;

unsigned long lastMeasureTime = 0;
const int interval = 1000;

void setup()
{
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    if (millis() - lastMeasureTime >= interval)
    {
        lastMeasureTime = millis();

        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);

        digitalWrite(trigPin, LOW);

        duration = pulseIn(echoPin, HIGH, 30000);

        if (duration == 0)
        {
            Serial.println("No signal");
            return;
        }

        distanceCm = duration * SOUND_SPEED / 2;

        Serial.print("Distance (cm): ");
        Serial.println(distanceCm);
    }

}