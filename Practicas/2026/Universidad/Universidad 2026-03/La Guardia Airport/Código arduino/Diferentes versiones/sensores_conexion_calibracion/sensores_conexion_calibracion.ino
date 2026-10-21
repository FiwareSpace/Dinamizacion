// Sensor MPU6050 y HC-SR04
// Telemetría con AUTO-CALIBRACIÓN HARDWARE inicial

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>           
#include <PubSubClient.h>

Adafruit_MPU6050 mpu;

#define TRIG_PIN 5
#define ECHO_PIN 18

// =========================
// DATOS DE RED
// =========================
const char* ssid = "Fiware_space";     
const char* password = "centroinnovacion";   
const char* mqtt_server = "192.168.1.64"; 

WiFiClient espClient;
PubSubClient client(espClient);

// Variables para guardar el error del sensor (Offsets)
float off_ax = 0, off_ay = 0, off_az = 0;
float off_gx = 0, off_gy = 0, off_gz = 0;

void setup_wifi() {
  delay(10);
  Serial.print("\nConectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("Placa_Sensores_Guardia")) {
      Serial.println("Conectado a MQTT!");
    } else {
      delay(5000);
    }
  }
}

// ==========================================
// FUNCIÓN DE AUTOCALIBRACIÓN
// ==========================================
void calibrar_sensor() {
  Serial.println("\n--- INICIANDO CALIBRACION ---");
  Serial.println("NO MUEVAS LA MAQUETA EN 3 SEGUNDOS...");
  delay(2000); // Dar tiempo a quitar las manos de la placa

  float sum_ax = 0, sum_ay = 0, sum_az = 0;
  float sum_gx = 0, sum_gy = 0, sum_gz = 0;
  int lecturas = 200;

  for (int i = 0; i < lecturas; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    sum_ax += a.acceleration.x;
    sum_ay += a.acceleration.y;
    sum_az += a.acceleration.z;

    sum_gx += g.gyro.x;
    sum_gy += g.gyro.y;
    sum_gz += g.gyro.z;
    delay(10);
  }

  // Se calcula la media del error
  off_ax = sum_ax / lecturas;
  off_ay = sum_ay / lecturas;
  // Al eje Z le restamos la gravedad ideal (9.81) para hallar solo el error
  off_az = (sum_az / lecturas) - 9.81; 

  off_gx = sum_gx / lecturas;
  off_gy = sum_gy / lecturas;
  off_gz = sum_gz / lecturas;

  Serial.println("--- CALIBRACION COMPLETADA ---");
  Serial.print("Error X: "); Serial.println(off_ax);
  Serial.print("Error Y: "); Serial.println(off_ay);
}

void setup() {
  Serial.begin(115200);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  if (!mpu.begin()) {
    Serial.println("Error: MPU6050 no encontrado");
    while (1) { delay(10); }
  }
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Llamamos a la calibración justo antes de empezar a enviar datos
  calibrar_sensor();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // 1. Tomar lectura bruta
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 2. Aplicar corrección matemática restando el error
  float ax_limpio = a.acceleration.x - off_ax;
  float ay_limpio = a.acceleration.y - off_ay;
  float az_limpio = a.acceleration.z - off_az;

  float gx_limpio = g.gyro.x - off_gx;
  float gy_limpio = g.gyro.y - off_gy;
  float gz_limpio = g.gyro.z - off_gz;

  // 3. Enviar datos limpios por MQTT
  client.publish("la_guardia/aceleracion/x", String(ax_limpio).c_str());
  client.publish("la_guardia/aceleracion/y", String(ay_limpio).c_str());
  client.publish("la_guardia/aceleracion/z", String(az_limpio).c_str());

  client.publish("la_guardia/giroscopio/x", String(gx_limpio).c_str());
  client.publish("la_guardia/giroscopio/y", String(gy_limpio).c_str());
  client.publish("la_guardia/giroscopio/z", String(gz_limpio).c_str());

  // 4. Ultrasonidos
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float distance = pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
  client.publish("la_guardia/distancia", String(distance).c_str());

  delay(100); // Reducido a 100ms para que el avión 3D se mueva muy fluido
}