#include <Arduino.h>
#include <DHT.h>

const uint8_t dht11Pin = D6;
const uint8_t dht22Pin = D7;

DHT dht11(dht11Pin, DHT11);
DHT dht22(dht22Pin, DHT22);

const uint32_t readSensorsDebounceTime = 2000;
uint32_t lastReadSensorsTime = 0;

void setup() {
  Serial.begin(115200);
  dht11.begin();
  dht22.begin();
}

void loop() {
  uint32_t nowTime = millis();
  if ((nowTime - lastReadSensorsTime) >= readSensorsDebounceTime)
  {
    lastReadSensorsTime = nowTime;

    float t11 = dht11.readTemperature();
    float t22 = dht22.readTemperature();
    
    float h11 = dht11.readHumidity();
    float h22 = dht22.readHumidity();

    Serial.println("DHT11 Temperature: " + String(t11) + "℃");
    Serial.println("DHT22 Temperature: " + String(t22) + "℃");
    
    Serial.println("DHT11 Humidity: " + String(h11) + "%");
    Serial.println("DHT22 Humidity: " + String(h22) + "%");
  }
}
