#include <WiFi.h>

const char* ssid = "Vendo OPEL CORSA";
const char* password = "password";

void setup() {
  Serial.begin(115200);
  Serial.println("\nSetting AP");
  WiFi.softAP(ssid, password);
  Serial.println("\nWiFi is ready");

  // Obtén la dirección IP del punto de acceso
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("IP Address of AP: ");
  Serial.println(apIP);
}

void loop() {
  // Puedes mantener la funcionalidad existente para contar dispositivos conectados
  int device = WiFi.softAPgetStationNum();
  Serial.printf("DEVICES CONNECTED = %d\n", device);

  delay(5000);
}