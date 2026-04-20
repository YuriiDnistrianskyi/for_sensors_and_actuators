#include <Arduino.h>
#include <Servo.h>

const uint8_t SERVO_PIN = D4;
const uint8_t POTENTIOMETER_PIN = A0;
const uint16_t READ_POTENTIOMETER_DEBOUNCE = 50;
const uint16_t SERIAL_PRINT_DEBOUNCE = 200;

Servo myServo;
uint32_t lastReadPotentiometer = 0;
uint16_t lastAngle;
uint32_t lastSerialPrintTime = 0;

void setup() {
  Serial.begin(115200);
  delay(200);
  myServo.attach(SERVO_PIN, 500, 2500);
  myServo.write(0);
}

void loop() {
  uint32_t currentTime = millis();
  if (currentTime - lastReadPotentiometer > READ_POTENTIOMETER_DEBOUNCE) 
  { 
    lastReadPotentiometer = currentTime;

    uint16_t potentiometerValue = analogRead(POTENTIOMETER_PIN);
    uint16_t targetAngle = map(potentiometerValue, 0, 1023, 0, 180);
    // targetAngle = constrain(targetAngle, 0, 180);

    if (targetAngle != lastAngle) 
    {
      lastAngle = targetAngle;
      myServo.write(targetAngle);
    }

    if (millis() - lastSerialPrintTime > SERIAL_PRINT_DEBOUNCE) 
    {
      Serial.println("--------------------------");
      Serial.println("Potentiometer: " + String(potentiometerValue));
      Serial.println("Angle: " + String(targetAngle));
    }
  }
}
