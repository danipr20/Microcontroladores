#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define LED 2

const char* ssid = " ";
const char* password = "";

  WiFiServer server(80);
  WiFiClient clientmem;

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
    
  // Inicializa el servidor para escuchar conexiones entrantes
  server.begin();
}

void loop() {
  // Escucha conexiones entrantes
  WiFiClient client = server.available();

  if (client!=clientmem) {
    digitalWrite(LED, LOW);
    Serial.println("Nuevo cliente conectado");
    Serial.print("Dirección IP del cliente: ");
    Serial.println(client.remoteIP().toString().c_str());

    Serial.print("Dirección PORT del cliente: ");
    Serial.println(client.remotePort());

    // Responde al cliente
    client.println("Hola, ¡bienvenido!");
    delay(1000); // Espera un momento antes de cerrar la conexión
    Serial.println("Cliente desconectado");
    delay(1000);
    digitalWrite(LED, HIGH);
delay(10000);
  }
  clientmem=client;
}
