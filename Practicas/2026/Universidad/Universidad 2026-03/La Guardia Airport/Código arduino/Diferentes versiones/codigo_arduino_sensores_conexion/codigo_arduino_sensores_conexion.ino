// Sensor MPU6050 y HC-SR04
// Telemetría real por WiFi local, MQTT hacia Node-RED (Tema: la_guardia) y Monitor Serie

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>           // Si usas ESP8266, cambia esto por <ESP8266WiFi.h>
#include <PubSubClient.h>

Adafruit_MPU6050 mpu;

// Pines del HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 18

// =========================
// 1. TUS DATOS DE RED Y MQTT
// =========================
const char* ssid = "NOMBRE_DE_TU_WIFI";     // Pon el nombre de tu red WiFi
const char* password = "CONTRASEÑA_WIFI";   // Pon tu contraseña

// IP de tu ordenador donde tienes Node-RED y el Broker MQTT (Ej: "192.168.1.33")
const char* mqtt_server = "192.168.1.X"; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a la red WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");
  Serial.print("Direccion IP de la placa: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conectar al servidor MQTT...");
    // Nombre del cliente ligeramente modificado para evitar conflictos
    if (client.connect("Placa_Sensores_Guardia")) {
      Serial.println("¡Conectado a MQTT!");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" reintentando en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Iniciar WiFi y MQTT
  setup_wifi();
  client.setServer(mqtt_server, 1883); // 1883 es el puerto por defecto de Mosquitto

  // Iniciar MPU6050
  if (!mpu.begin()) {
    Serial.println("No se encontro el MPU6050");
    while (1) { delay(10); }
  }
  Serial.println("MPU6050 OK");

  // Iniciar HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("HC-SR04 OK");
  Serial.println("=====================================");
}

void loop() {
  // Mantener MQTT vivo
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // =========================
  // LECTURA MPU6050
  // =========================
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.println("===== MPU6050 =====");

  // Imprimir por Serie y publicar por MQTT en "la_guardia"
  Serial.print("Aceleracion X: "); Serial.println(a.acceleration.x);
  client.publish("la_guardia/aceleracion/x", String(a.acceleration.x).c_str());

  Serial.print("Aceleracion Y: "); Serial.println(a.acceleration.y);
  client.publish("la_guardia/aceleracion/y", String(a.acceleration.y).c_str());

  Serial.print("Aceleracion Z: "); Serial.println(a.acceleration.z);
  client.publish("la_guardia/aceleracion/z", String(a.acceleration.z).c_str());

  Serial.print("Giroscopio X: "); Serial.println(g.gyro.x);
  client.publish("la_guardia/giroscopio/x", String(g.gyro.x).c_str());

  Serial.print("Giroscopio Y: "); Serial.println(g.gyro.y);
  client.publish("la_guardia/giroscopio/y", String(g.gyro.y).c_str());

  Serial.print("Giroscopio Z: "); Serial.println(g.gyro.z);
  client.publish("la_guardia/giroscopio/z", String(g.gyro.z).c_str());

  // =========================
  // LECTURA HC-SR04
  // =========================
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.println("===== HC-SR04 =====");
  
  // Imprimir por Serie y publicar por MQTT en "la_guardia"
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  client.publish("la_guardia/distancia", String(distance).c_str());

  Serial.println("--------------------");

  // Esperar un segundo antes de la próxima lectura
  delay(1000);
}