#include <Arduino.h>
#include <Servo.h>

const uint8_t SERVO_PIN = D1;
const uint8_t POTENTIOMETER_PIN = D2;
const uint16_t READ_POTENTIOMETER_DEBOUNCE = 200;
const uint16_t SERIAL_PRINT_DEBOUNCE = 200;

Servo myServo;
uint32_t lastReadPotentiometer = 0;
uint16_t lastAngle;
uint32_t lastSerialPrintTime = 0;

void setup() {
  Serial.begin(115200);
  delay(200);
  myServo.attach(SERVO_PIN);
  myServo.write(90);
}

void loop() {
  uint32_t currentTime = millis();
  if (currentTime - lastReadPotentiometer > READ_POTENTIOMETER_DEBOUNCE) 
  {
    lastReadPotentiometer = currentTime;

    uint16_t potentiometerValue = analogRead(POTENTIOMETER_PIN);
    uint16_t targetAngle = map(potentiometerValue, 0, 1023, 0, 180); // 1023 -> 255 (254)
    targetAngle = constrain(targetAngle, 0, 180);

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














// #include <Arduino.h>
// #include <Servo.h>
// constexpr uint8_t SERVO_PIN = 9;  
// constexpr uint8_t POT_PIN = A0;

// Servo myServo;
// int currentAngle = -1;
// unsigned long lastPrintMs = 0;
// void setup()
// {
//  Serial.begin(115200);
//  delay(200);
//  myServo.attach(SERVO_PIN);
//  myServo.write(90);
//  Serial.println();
//  Serial.println("Pot -> Servo sync started");
//  Serial.println("ADC 0..1023 => Angle 0..180");
// }
// void loop()
// {
//  int potRaw = analogRead(POT_PIN); // 0..1023
//  int targetAngle = map(potRaw, 0, 1023, 0, 180);
//  targetAngle = constrain(targetAngle, 0, 180);
//  if (targetAngle != currentAngle)
//  {
//  currentAngle = targetAngle;
//  myServo.write(currentAngle);
//  }
//  if (millis() - lastPrintMs >= 200)
//  {
//  lastPrintMs = millis();
//  Serial.print("ADC: ");
//  Serial.print(potRaw);
//  Serial.print(" Angle: ");
//  Serial.println(currentAngle);
//  }
//  delay

