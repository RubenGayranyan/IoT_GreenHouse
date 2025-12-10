#include <DHT.h>
#include <ESP32Servo.h>

#define SERVO_PIN 19   // Servo motor
#define SOIL_PIN 32  // Soil Moisture
#define DHT_PIN 27   // DHT
#define US_TRIG 33   // UltraSonic - Trigger
#define US_ECHO 35   // Ultrasonic - Echo

DHT dht(DHT_PIN, DHT22);
Servo motor;

bool waterState = false;

void source(float hum, float temp, float distance, int moisture) {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  if (distance > 20) { // There is no water
    Serial.println("WARNING: No water");
  }

  if (distance < 10 && moisture < 25) { // There is enough water and moisture is low
    motor.write(90);
    waterState = true;
  }

  if (moisture > 25  || distance > 10) { // Moisture is high, but there is not enough water
    motor.write(0);
    waterState = false;
  }

  Serial.println(" ");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(US_TRIG, OUTPUT);  // UltraSonic - TRIG
  pinMode(US_ECHO, INPUT);   // UltraSonic - ECHO
  pinMode(DHT_PIN, INPUT_PULLUP); // DHT

  dht.begin();
  motor.attach(SERVO_PIN);

  motor.write(0);
}

void loop() {
  /* SOIL MOISTURE */
  int value = analogRead(SOIL_PIN);
  int moisture = map(value, 3000, 1200, 0, 100);
  moisture = constrain(moisture, 0, 100);
  /* SOIL MOISTURE */

  /* ULTRASONIC */
  digitalWrite(US_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(US_TRIG, LOW);
  long duration = pulseIn(US_ECHO, HIGH, 30000);
  /* ULTRASONIC */

  /* DHT */
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  /* DHT */

  if (duration != 0) {
    float distance_cm = duration / 58.0;
    source(hum, temp, distance_cm, moisture);
  }
  else {
    Serial.println("Sensors are not connected.");
    delay(1000);
  }
  delay(1000);
}
