#include <WiFi.h>
#include <WebServer.h>
#include <string.h>

#define ledServ 19
#define ledCon 5


//Introducir Parámetros de la red a la que te quieres conectar_ SSID y PASSWORD
const char* ssid="SSID";
const char* password="PASSWORD";

String ESTADO = "En espera, ON/OFF";

const String html_page_orig1 PROGMEM = "<!DOCTYPE html><html> <head> <title>Led Control</title> </head> <body> <h1>Led State</h1> <h2>";

const String html_page_orig2 PROGMEM = "</h2> <div> <form method=\"POST\" action=\"/\"> <button id=\"on\" name=\"LED\" value=\"1\">ON</button> <button id=\"off\" name=\"LED\" value=\"0\">OFF</button> </form> </div> </body></html>";

String POST = "prueba post";

String PROGMEM html_page;

String Html_construct() {

  html_page = html_page_orig1 + ESTADO + html_page_orig2;
  delay(100);
  return html_page;
}

WebServer server(80);

// ip?LED=0/1
void handleRoot() {

  String ledState = server.arg("LED");
  Serial.print("Argumento recibido: ");
  ledState.toUpperCase();
  Serial.println(ledState);

  if (ledState == "1") {
    ESTADO = "ON";
    digitalWrite(ledServ, HIGH);
  }

  if (ledState == "0") {
    ESTADO = "OFF";
    digitalWrite(ledServ, LOW);
  }

  else {
    ESTADO = "Pulse ON/OFF";
  }

  html_page = Html_construct();
  server.send(200, "text/html", html_page);

  digitalWrite(ledCon, HIGH);
  Serial.println("Solicitud aceptada");
  delay(500);
  digitalWrite(ledCon, LOW);
}

void setup() {
  pinMode(ledCon, OUTPUT);
  pinMode(ledServ, OUTPUT);
  Serial.begin(115200);

  Serial.println("\nWIFI station setting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
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