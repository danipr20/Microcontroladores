#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define led 4

//Introducir Parámetros de la red a la que te quieres conectar_ SSID y PASSWORD
const char* ssid="SSID";
const char* password="PASSWORD";

const char* html_page PROGMEM = "<!DOCTYPE html><html><head> <title>Mi Pagina de Pruebas IoT: Danipr20</title></head><body> <h1>Bienvenido a Mi Pagina IoT </h1> <p>TEXTO</p> <p>Estado del dispositivo: <span id=\"estado\">Desconectado</span></p> <button onclick=\"encender()\">Encender</button> <button onclick=\"apagar()\">Apagar</button> <script> function encender() { document.getElementById('estado').innerText = 'Encendido'; // Aquí puedes agregar código para controlar tu dispositivo IoT cuando se enciende. } function apagar() { document.getElementById('estado').innerText = 'Apagado'; // Aquí puedes agregar código para controlar tu dispositivo IoT cuando se apaga. } </script></body></html>";


ESP8266WebServer server(80);

void handleRoot() {
  digitalWrite(led, HIGH);
  Serial.println("Solicitud aceptada");
  server.send(200, "text/html", html_page);
  delay(4000);
  digitalWrite(led, LOW);
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  Serial.println("\nWIFI station setting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n WIFI ready");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server HTTP started");
}

void loop() {
  server.handleClient();
}
