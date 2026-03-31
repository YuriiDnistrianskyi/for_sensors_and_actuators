#include <Arduino.h>
#include <DHT.h>

#define DHT11_PIN 4
#define DHT22_PIN 5 

#define DHT11_TYPE DHT11
#define DHT22_TYPE DHT22

DHT dht11(DHT11_PIN, DHT11_TYPE);
DHT dht22(DHT22_PIN, DHT22_TYPE);

unsigned long lastMeasureTime = 0;
const unsigned long interval = 2000;

void setup() {
  Serial.begin(115200);
  
  dht11.begin();
  dht22.begin();

  Serial.println("System initialized. Waiting for sensors to stabilize...");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastMeasureTime >= interval) {
    lastMeasureTime = currentMillis;

    float h11 = dht11.readHumidity();
    float t11 = dht11.readTemperature();

    float h22 = dht22.readHumidity();
    float t22 = dht22.readTemperature();

    Serial.println("---------------------------------");

    if (isnan(h11) || isnan(t11)) {
      Serial.println("Error: Failed to read from DHT11!");
    } else {
      Serial.printf("DHT11 -> Temp: %.1f °C, Hum: %.1f %%\n", t11, h11);
    }

    if (isnan(h22) || isnan(t22)) {
      Serial.println("Error: Failed to read from DHT22!");
    } else {
      Serial.printf("DHT22 -> Temp: %.1f °C, Hum: %.1f %%\n", t22, h22);
    }
  }
}