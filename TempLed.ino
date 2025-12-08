#include <Wire.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

#define SOIL_PIN 34 // Soil Moisture


void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(33, OUTPUT);  // TRIG
  pinMode(35, INPUT);   // ECHO


  Wire.begin(21, 22);
  Wire.setClock(100000);

  if (!aht.begin()) {
    Serial.println("AHT10 not found! Check wiring.");
    while (1) delay(10);
  }

  Serial.println("AHT10 OK");
}

void loop() {
  int value = analogRead(SOIL_PIN);

  int moisture = map(value, 4095, 1500, 0, 100);
  moisture = constrain(moisture, 0, 100);

  digitalWrite(33, LOW);
  delayMicroseconds(2);

  digitalWrite(33, HIGH);
  delayMicroseconds(10);
  digitalWrite(33, LOW);

  long duration = pulseIn(35, HIGH, 30000);

  if (duration != 0) {
    float distance_cm = duration / 58.0;
    if(distance_cm < 30.0) {
      sensors_event_t humidity, temp;
      aht.getEvent(&humidity, &temp);

      Serial.print("Destance: ");
      Serial.print(distance_cm);
      Serial.println("cm");

      Serial.print("Temperature: ");
      Serial.print(temp.temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity.relative_humidity);
      Serial.println(" %");

      Serial.print("Moisture: ");
      Serial.print(moisture);
      Serial.println("%");

      Serial.println("");
    }
  }
  delay(1000);
}
