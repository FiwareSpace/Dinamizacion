

//----------------------------------------------------LIBRERIAS DE MEDICIÓN ----------------------------------------------
#include <Wire.h>
#include <Multichannel_Gas_GMXXX.h>  // Grove Multichannel Gas Sensor V2
#include <DHT.h>
#include "SensirionI2cSps30.h"      // Librería I2C para SPS30


//----------------------------------------------------LIBRERIAS DE COMUNICACIÓN ----------------------------------------------
#include <WiFi.h>
#include <esp_system.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager

//---------------------------------------------------- ARCHIVOS EXTERNOS ----------------------------------------------
#include "config.h"
#include "fiware.h"
#include <Arduino.h>

//----------------------------------------------------DECLARACIONES DE MEDICIÓN ----------------------------------------------

// =======================
// ----- GAS SENSOR -----
// =======================
GAS_GMXXX<TwoWire> gas;  
#define FACTOR_NO2     0.001
#define FACTOR_VOC     0.001
#define FACTOR_C2H5OH  0.001
#define FACTOR_CO      0.012   // Ajuste especial CO

// =======================
// ----- DHT22 ---------
// =======================
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// =======================
// ----- SPS30 I2C ------
// =======================
#define SPS30_SDA 25
#define SPS30_SCL 26
SensirionI2cSps30 sps30;
TwoWire I2C_SPS30 = TwoWire(1);

float pm1, pm2_5, pm4, pm10;
float nc0_5, nc1, nc2_5, nc4, nc10;
float typicalParticle;

// =======================
// ----- TIMERS ---------
// =======================
unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 10000; // cada 10s

// -----------------------
// ----- PRECALENTAMIENTO SENSOR GAS -----
// -----------------------
unsigned long gasPreheatStart = 0;
bool gasPreheated = false;


//--------------------------------------------------- DECLARACIONES DE COMUNICACION -----------------------

// Wifi managerapp
WiFiManager wifiManager;
const char wmPassword[] = "respira";

// Device MAC address
char deviceMac[16];

// Description string
char deviceId[32];

// FIWARE object
FIWARE fiware(FIWARE_SERVER, FIWARE_UL_PORT, FIWARE_APIKEY, FIWARE_QRY_PORT, FIWARE_SERVICE, FIWARE_SERVICE_PATH, APP_NAME);

// Time of last sample in msec
uint32_t lastSampleTime = 0;

// Time of last transmission in msec
uint32_t lastTxTime = 0;

// First reading after startup
bool firstReading = true;

// force transmission
bool transmitNow = false;




//---------------------------------------------------- SETUP ----------------------------------------------

void setup() {

// --------------------------------------------------- WIFIMANAGER SET UP ------------------------------------------
  // Let the power supply stabilize
  delay(2000);

  // Setup UART
  Serial.begin(115200);
  Serial.println();

  // Get MAC
  WiFi.begin();
  uint8_t mac[6];
  WiFi.macAddress(mac);
  sprintf(deviceMac, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  // Device ID
  sprintf(deviceId, "%s_%s", APP_NAME, deviceMac);

  Serial.print("Device ID:"); Serial.println(deviceId);
  Serial.print("API Key: "); Serial.println(FIWARE_APIKEY);

  // WiFi Manager timeout
  wifiManager.setConfigPortalTimeout(300);

  // WiFi Manager autoconnect
  if (!wifiManager.autoConnect(deviceId))
  {
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  else
  {
    Serial.println("");
    Serial.print("MAC address: ");
    Serial.println(deviceMac);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

//---------------------------------------------------- STARTUP DE SENSORES ----------------------------------------------      
  Wire.begin();                       // bus por defecto para Gas Sensor
  I2C_SPS30.begin(SPS30_SDA, SPS30_SCL); // bus 1 para SPS30

  // Gas sensor
  gas.begin(Wire, 0x08);
  Serial.println("Iniciando precalentamiento Grove Gas Sensor...");
  gasPreheatStart = millis();

  // DHT22
  dht.begin();

  // SPS30 I2C
  Serial.println("Inicializando SPS30 I2C...");
  sps30.begin(I2C_SPS30, SPS30_I2C_ADDR_69);

  // Wake-up y reset
  if (sps30.wakeUp() != 0) Serial.println("Error wakeUp SPS30");
  delay(50);
  if (sps30.deviceReset() != 0) Serial.println("Error deviceReset SPS30");
  delay(300);

  // Iniciar medición SPS30
  int16_t err = sps30.startMeasurement(SPS30_OUTPUT_FORMAT_OUTPUT_FORMAT_FLOAT);
  if (err == 0) Serial.println("SPS30 listo.");
  else {
    Serial.print("ERROR StartMeasurement SPS30: "); 
    Serial.println(err);
  }

}


//----------------------------------------------------LOOP ----------------------------------------------


void loop() {
  unsigned long now = millis();

  // Precalentamiento GAS
  if (!gasPreheated && (now - gasPreheatStart >= 60000UL)) {  // 1 min de calentamiento
    gasPreheated = true;
    Serial.println("Grove Gas Sensor listo.");
  }

  if (gasPreheated && now - lastRead >= READ_INTERVAL) {
    lastRead = now;

    // ---------- LEER GASES ----------
    float no2_ppm    = gas.measure_NO2()   * FACTOR_NO2;
    float co_ppm     = gas.measure_CO()    * FACTOR_CO;
    float voc_ppm    = gas.measure_VOC()   * FACTOR_VOC;
    float c2h5oh_ppm = gas.measure_C2H5OH()* FACTOR_C2H5OH;

    float no2_ugm3    = no2_ppm    * 1880.0 * 0.08;
    float co_ugm3     = co_ppm     * 1144.0 * 0.08;
    float voc_ugm3    = voc_ppm    * 2018.0 * 0.15;
    float c2h5oh_ugm3 = c2h5oh_ppm * 1880.0 * 0.25;

    // ---------- LEER DHT22 ----------
    float temp = dht.readTemperature();
    float hum  = dht.readHumidity();
    if (isnan(temp)) temp = -999;
    if (isnan(hum))  hum  = -999;

    // ---------- LEER SPS30 ----------
    int16_t err = sps30.readMeasurementValuesFloat(pm1, pm2_5, pm4, pm10,
                                                   nc0_5, nc1, nc2_5, nc4,
                                                   nc10, typicalParticle);
    if (err != 0) { 
      Serial.print("Error lectura SPS30: "); 
      Serial.println(err);
      pm1 = pm2_5 = pm4 = pm10 = -1;
    }

    // ---------- MOSTRAR RESULTADOS ----------
    Serial.println("============================");
    Serial.println("====== Sensor de Gases ======");
    Serial.print("NO2      : "); Serial.print(no2_ugm3,1); Serial.println(" µg/m³");
    Serial.print("CO       : "); Serial.print(co_ugm3,1); Serial.println(" µg/m³");
    Serial.print("VOC      : "); Serial.print(voc_ugm3,1); Serial.println(" µg/m³");
    Serial.print("C2H5OH   : "); Serial.print(c2h5oh_ugm3,1); Serial.println(" µg/m³");

    Serial.println("====== DHT22 ======");
    Serial.print("Temperatura  : "); Serial.print(temp); Serial.println(" °C");
    Serial.print("Humedad      : "); Serial.print(hum); Serial.println(" %");

    Serial.println("====== SPS30 ======");
    Serial.print("PM1.0    : "); Serial.print(pm1); Serial.println(" µg/m³");
    Serial.print("PM2.5    : "); Serial.print(pm2_5); Serial.println(" µg/m³");
    Serial.print("PM4.0    : "); Serial.print(pm4); Serial.println(" µg/m³");
    Serial.print("PM10     : "); Serial.print(pm10); Serial.println(" µg/m³");
    Serial.println("============================");

    transmit(temp,hum,no2_ugm3,pm1,pm2_5,pm4,pm10); //ESTO NO SERÁ ASÍ, tengo que ver como se llama
  }
 
  delay(10000);
}




// ------------------------------------------------------- FUNCION LLAMADA HTTPS ---------------------------------


bool transmit(float temp, float hum, float no2_ugm3, float pm1, float pm2, float pm4, float pm10)
{
  bool ret = false;
  char txBuf[256];

  // Lee medias de medidas
  float avgT = temp;
  float avgH = hum;
  float avgN = no2_ugm3;

  // Forma el mensaje
  sprintf(txBuf, "t|%.2f|h|%.2f|no2|%.2f|pm1|%.2f|pm10|%.2f|pm2|%.2f|pm4|%.2f", avgT, avgH, avgN, pm1, pm10, pm2, pm4);
  

  Serial.println();
  Serial.println(txBuf);

  // Envía el mensaje
  ret = fiware.send(deviceId, txBuf);

  if (ret)
  {
    Serial.println("Envio exitoso");
  }
  else
  {
    Serial.println("Envio NO exito");
  }

  return ret;
}
