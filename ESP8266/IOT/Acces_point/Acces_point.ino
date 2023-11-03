#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define LED 2

const char* ssid = "Vendo Opel Corsa";
const char* password = "";

  int devicemem=0;

WiFiServer server(80);

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);

  Serial.begin(115200);
  Serial.println("\nSetting AP");
  WiFi.softAP(ssid,password);
  Serial.println("\nWiFi is ready");

  // Obtén la dirección IP del punto de acceso
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("IP Address of AP: ");
  Serial.println(apIP);

   server.begin(); 

}


void loop() {
    WiFiClient client = server.available();

  // Puedes mantener la funcionalidad existente para contar dispositivos conectados
  int device = WiFi.softAPgetStationNum();

  if (devicemem!=device) {

    Serial.println("Nuevo cliente conectado");
    Serial.print("Dirección IP del cliente: ");
    Serial.println(client.remoteIP().toString().c_str());    
  Serial.printf("DEVICES CONNECTED = %d\n", device);

  

  digitalWrite(LED,LOW);
  delay(4000);
  digitalWrite(LED,HIGH);
  }
  devicemem=device;

}