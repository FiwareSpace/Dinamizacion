#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Instancia del sensor
Adafruit_MPU6050 mpu;

// Pines del HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 18

// ==========================================
// CONFIGURACIÓN DE RED
// ==========================================
const char* ssid = "PON_AQUI_TU_WIFI";
const char* password = "PON_AQUI_TU_CONTRASEÑA";
const char* mqtt_server = "192.168.1.64"; // IP de tu ordenador con Node-RED

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.print("\nConectando a la red WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado exitosamente.");
}

void reconnect() {
  // Bucle hasta que logremos reconectar al servidor MQTT
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT a 192.168.1.64... ");
    if (client.connect("ESP32_Maqueta_Guardia")) {
      Serial.println("¡Conectado!");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" -> Intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Iniciar WiFi y MQTT
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  // Iniciar MPU6050
  if (!mpu.begin()) {
    Serial.println("Error: No se encontró el chip MPU6050. Revisa los cables I2C.");
    while (1) { delay(10); } // Se queda bloqueado aquí si falla el sensor
  }
  Serial.println("MPU6050 iniciado correctamente.");
  
  // Configurar sensibilidad del MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Iniciar pines del HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Mantener conexión MQTT viva
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 1. LEER MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Enviar datos en bruto del acelerómetro (Gravedad)
  client.publish("la_guardia/aceleracion/x", String(a.acceleration.x).c_str());
  client.publish("la_guardia/aceleracion/y", String(a.acceleration.y).c_str());
  client.publish("la_guardia/aceleracion/z", String(a.acceleration.z).c_str());

  // Enviar datos en bruto del giroscopio (Rotación)
  client.publish("la_guardia/giroscopio/x", String(g.gyro.x).c_str());
  client.publish("la_guardia/giroscopio/y", String(g.gyro.y).c_str());
  client.publish("la_guardia/giroscopio/z", String(g.gyro.z).c_str());

  // 2. LEER HC-SR04 (Ultrasonidos)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2; // Calcular distancia en cm

  // Enviar distancia
  client.publish("la_guardia/distancia", String(distance).c_str());

  // Pausa de 100ms para no saturar el servidor pero mantener fluidez
  delay(100);
}