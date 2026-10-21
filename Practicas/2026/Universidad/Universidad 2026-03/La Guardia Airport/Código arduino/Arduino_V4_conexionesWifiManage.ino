#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

// ==========================================
// CONFIGURACIÓN DE SENSORES
// ==========================================
Adafruit_MPU6050 mpu;

#define TRIG_PIN 5
#define ECHO_PIN 18

// ==========================================
// CONFIGURACIÓN MQTT
// ==========================================
const char* mqtt_server = "192.168.1.64"; // IP de tu ordenador con Node-RED

WiFiClient espClient;
PubSubClient client(espClient);

// ==========================================
// CONFIGURACIÓN WIFIMANAGER
// ==========================================
char deviceMac[16];
char deviceId[32];

// Función para reconectar a Node-RED (MQTT)
void reconnect() {
  // Solo intentamos conectar a MQTT si el WiFi está funcionando
  while (!client.connected() && WiFi.status() == WL_CONNECTED) {
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
  // Estabilizar energía
  delay(2000);
  Serial.begin(115200);
  Serial.println();

  // ---------------------------------------------------
  // 1. INICIAR WIFIMANAGER
  // ---------------------------------------------------
  // Obtener la MAC para ponerle un nombre único a la red que va a crear
  WiFi.begin();
  uint8_t mac[6];
  WiFi.macAddress(mac);
  sprintf(deviceMac, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  
  // El nombre de la red WiFi que creará tu ESP32
  sprintf(deviceId, "Maqueta_Guardia_%s", deviceMac);

  WiFiManager wifiManager;
  // Tiempo máximo (en segundos) que el portal WiFi estará abierto esperando configuración
  wifiManager.setConfigPortalTimeout(300);

  Serial.println("Iniciando conexión WiFi...");
  
  if (!wifiManager.autoConnect(deviceId)) {
    Serial.println("Fallo al conectar al WiFi o se agotó el tiempo. Reiniciando placa...");
    delay(3000);
    ESP.restart();
  }
  
  // Si llegamos aquí, es que estamos conectados al router de casa
  Serial.println("\n¡WiFi conectado exitosamente!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // ---------------------------------------------------
  // 2. INICIAR MQTT Y SENSORES
  // ---------------------------------------------------
  client.setServer(mqtt_server, 1883);

  if (!mpu.begin()) {
    Serial.println("Error: No se encontró el chip MPU6050. Revisa los cables I2C.");
    while (1) { delay(10); } 
  }
  Serial.println("MPU6050 iniciado correctamente.");
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Asegurar que seguimos conectados al broker antes de enviar nada
  if (!client.connected() && WiFi.status() == WL_CONNECTED) {
    reconnect();
  }
  
  if (client.connected()) {
    client.loop();
  }

  // ---------------------------------------------------
  // 3. LEER Y ENVIAR MPU6050
  // ---------------------------------------------------
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  client.publish("la_guardia/aceleracion/x", String(a.acceleration.x).c_str());
  client.publish("la_guardia/aceleracion/y", String(a.acceleration.y).c_str());
  client.publish("la_guardia/aceleracion/z", String(a.acceleration.z).c_str());

  client.publish("la_guardia/giroscopio/x", String(g.gyro.x).c_str());
  client.publish("la_guardia/giroscopio/y", String(g.gyro.y).c_str());
  client.publish("la_guardia/giroscopio/z", String(g.gyro.z).c_str());

  // ---------------------------------------------------
  // 4. LEER Y ENVIAR HC-SR04 (Ultrasonidos)
  // ---------------------------------------------------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2;

  client.publish("la_guardia/distancia", String(distance).c_str());

  // Mantener la cadencia perfecta para Node-RED
  delay(100);
}