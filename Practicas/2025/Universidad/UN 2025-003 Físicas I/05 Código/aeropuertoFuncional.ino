#include <WiFiS3.h> // Librería para conexión WiFi (placas como Arduino Uno R4 WiFi)
#include <DHT.h>
#include <DHT_U.h>
#include <WiFiS3.h> // Librería para conexión WiFi (placas como Arduino Uno R4 WiFi)

#define DHTTYPE DHT22  //Definimos Tipo de sensor
int DHTPIN=10;            //Conectado al pin 8

DHT_Unified dht(DHTPIN, DHTTYPE); //Creamos un objeto dht 

// uint32_t delayMS;
int delayMS = 1000;
float temp = 0;
float humi = 0;
bool  ni= true;
int LDR=0;
char ssid[] = "Fiware_Space";          // Nombre de la red WiFi
char pass[] = "centroinnovacion";      // Contraseña de la red WiFi
int status = WL_IDLE_STATUS;           // Estado de la conexión WiFi
float h;  //Lee la humedad
float t; //Lee la temperatura
int valorLDR;   //Lee el valor del fotosensor
WiFiClient client;                     // Cliente WiFi

char server[] = "iota-ul.iotplatform.telefonica.com"; // Dirección del servidor IoT
int port = 8085;  

char url1[] = "/iot/d?k=Carril:key&i=carril01";
  
char url2[] = "/iot/d?k=Carril:key&i=carril02";

void setup() {
  setup_wifi();
  // Initialize device.
  DHT_Initialize();
  pinMode(A0,INPUT);       //Definimos la entrada (sensor LDR) 
  //verde1
  pinMode(3, OUTPUT);
  //azul1
  pinMode(4, OUTPUT);
  //rojo1
  pinMode(7, OUTPUT);
  //sensor1
  pinMode(8, INPUT);
  //verde2
  pinMode(9, OUTPUT);
  //azul2
  pinMode(5,  OUTPUT);
  //rojo2
  pinMode(6,OUTPUT);
  //sensor2
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  int objeto1=digitalRead(8);
  int objeto2=digitalRead(2);
  h=get_Humidity();
  t=get_Temperature();
  valorLDR=analogRead(A0);
  
 // Send http call to the FIWARE platform
  httpPostmanTemp(t,h,valorLDR,ni);

  if(valorLDR>=800 && h>90) {      //Si el valor del LDR es mayor de 800 y la humedad es mayor de 90, se enciende el LED
  Serial.print("HAY NIEBLA");
  Serial.println(valorLDR);
  Serial.print("Humedad=");
  Serial.print (h);
  delay(500);
  ni=true;
  }
  else {
  Serial.println("NO HAY NIEBLA");
  Serial.println(valorLDR);
  Serial.print("Humedad=");
  Serial.print (h);
  delay(500);
  ni=false;
  }
  
  //Serial.println(A0);
  //delay(1000);
  if (objeto1==LOW){
    Serial.println("rojo1");
    rojo1();
    delay(500);
  }
  else {
    Serial.println("verde1");
    verde1();
    delay(500);
  }
  if (objeto2==LOW){
    Serial.println("cuidado");
    rojo2();
    delay(500);
  }
  else {
    Serial.println("ta weno");
    verde2();
    delay(500);
  }
  httpPostmanLibre(objeto1, url1);
  httpPostmanLibre(objeto2, url2);

}

void DHT_Initialize(){
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  // delayMS = sensor.min_delay / 1000;
}

float get_Temperature(){
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    //Serial.print(event.temperature);
    //Serial.println(F("°C"));
  }
  return event.temperature;
}

float get_Humidity(){
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    //Serial.print(event.relative_humidity);
    //Serial.println(F("%"));
  }
  return event.relative_humidity;
}


void verde1() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(7, LOW);
}
void rojo1() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
}
void verde2() {
  digitalWrite(9, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}
void rojo2() {
  digitalWrite(9, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
}
void setup_wifi() {
  while (!Serial);

  Serial.println("Conectando a WiFi...");

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(1000);
    Serial.print("Intentando conectar a: ");
    Serial.println(ssid);
  }

  Serial.println("Conectado a la red WiFi");
}

// Envio de Datos al agente UL

void httpPostmanLibre(bool obj, char url[]){
  char server[] = "iota-ul.iotplatform.telefonica.com";
  int port = 8085; 

  String body = "L|" + String(obj);
  //char url[] = url;
  

  if (client.connect(server, port)) {

    // Enviar petición HTTP POST
    client.print("POST ");
    client.print(url);
    client.println( " HTTP/1.1");
    client.println("Host: iota-ul.iotplatform.telefonica.com");
    client.println("Content-Type: text/plain");
    client.print("Content-Length: ");
    client.println(body.length());
    client.println();         
    client.println(body);

    Serial.println();
    Serial.println("Están libres");
  } else {
    Serial.println("Fallo en la conexión con el servidor IoT Agent");
  }
}
void httpPostmanTemp(float tem, float hum, int valorLDR, bool nib){
  char server[] = "iota-ul.iotplatform.telefonica.com";
  int port = 8085; 

  String body = "t|" + String(tem) + "#h|" + String(hum) + "#n|" + String(nib) + "#l|" + String(valorLDR);
  String url = "/iot/d?k=pistaAterrrizaje001:key&i=pistaAterrizaje001";

  if (client.connect(server, port)) {

    // Enviar petición HTTP POST
    client.println("POST " + url + " HTTP/1.1");
    client.println("Host: iota-ul.iotplatform.telefonica.com");
    client.println("Content-Type: text/plain");
    client.print("Content-Length: ");
    client.println(body.length());
    client.println();         
    client.println(body);

    Serial.println();
    Serial.println("Datos de Temperatura y Humedad");
  } else {
    Serial.println("Fallo en la conexión con el servidor IoT Agent");
  }
}





