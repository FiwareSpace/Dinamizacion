#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {

  Serial.begin(115200);

  // Iniciar MPU6050
  if (!mpu.begin()) {
    Serial.println("No se encontro el MPU6050");

    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 conectado");

  // HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("HC-SR04 conectado");
}

void loop() {

  // =========================
  // MPU6050
  // =========================

  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);

  Serial.println("===== MPU6050 =====");

  Serial.print("Aceleracion X: ");
  Serial.println(a.acceleration.x);

  Serial.print("Aceleracion Y: ");
  Serial.println(a.acceleration.y);

  Serial.print("Aceleracion Z: ");
  Serial.println(a.acceleration.z);

  Serial.print("Giroscopio X: ");
  Serial.println(g.gyro.x);

  Serial.print("Giroscopio Y: ");
  Serial.println(g.gyro.y);

  Serial.print("Giroscopio Z: ");
  Serial.println(g.gyro.z);

  // =========================
  // HC-SR04
  // =========================

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  Serial.println("===== HC-SR04 =====");

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.println("--------------------");

  delay(1000);
}