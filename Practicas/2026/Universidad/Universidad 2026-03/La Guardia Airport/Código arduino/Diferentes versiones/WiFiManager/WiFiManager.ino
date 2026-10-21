

//-----------------------LIBRERIAS DE COMUNICACIÓN ----------------------------------------------
#include <WiFi.h>
#include <esp_system.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>         // https://github.com/tzapu/WiFiManager





// Wifi managerapp
WiFiManager wifiManager;
const char wmPassword[] = "respira";

// Device MAC address
char deviceMac[16];

// Description string
char deviceId[32];



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

  /*
  sprintf(deviceId, "%s_%s", APP_NAME, deviceMac);

  Serial.print("Device ID:"); Serial.println(deviceId);
  Serial.print("API Key: "); Serial.println(FIWARE_APIKEY);
*/

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
}


//----------------------------------------------------LOOP ----------------------------------------------


void loop() {
  Serial.println("Todo OK");
  delay(10000);
}



