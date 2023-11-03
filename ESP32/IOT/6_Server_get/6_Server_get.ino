#include <WiFi.h>
#include <WebServer.h>


#define ledCon 5
#define ledServ 13

//Introducir Parámetros de la red a la que te quieres conectar_ SSID y PASSWORD
const char* ssid="SSID";
const char* password="PASSWORD";

String ESTADO = "En espera, ON/OFF";

const String html_page_orig1 PROGMEM = "<!DOCTYPE html><html><head> <title>Mi Pagina de Pruebas IoT: Danipr20</t<!DOCTYPE html><html><head> <title>Mi Pagina de Pruebas IoT: Danipr20</title></head><body> <h1>Bienvenido a Mi Pagina IoT: Soy Dani</h1> <p>Aqui hago pruebas con IOT, enviando y recibiendo valores, ahora mismo a un LED</p> <p>Estado del dispositivo: <span id=\"estado\">";

const String html_page_orig2 PROGMEM = "</span></p> <button onclick=\"encender()\">Encender</button> <button onclick=\"apagar()\">Apagar</button> <script> function encender() { document.getElementById('estado').innerText = 'Encendido'; // Aquí puedes agregar código para controlar tu dispositivo IoT cuando se enciende. } function apagar() { document.getElementById('estado').innerText = 'Apagado'; // Aquí puedes agregar código para controlar tu dispositivo IoT cuando se apaga. } </script></body></html>";

String html_page;

String Html_construct() {
  return html_page = html_page_orig1 + ESTADO + html_page_orig2;
}

WebServer server(80);

// ip?LED=0/1
void handleRoot() {
  int i=0;

  String ledState = server.arg("LED");
  Serial.print("Argumento recibido: ");
  ledState.toUpperCase();
  Serial.println(ledState);

  if (ledState == "ON") {
    ESTADO = ledState;
    digitalWrite(ledServ, HIGH);
    html_page = Html_construct();
    server.send(200, "text/html", html_page);
  }

  if (ledState == "OFF") {
    ESTADO = ledState;    
    digitalWrite(ledServ, LOW);
    html_page = Html_construct();
    server.send(200, "text/html", html_page);
  } 
  
  else if (i=!0) {
    ESTADO = "Error, comando no valido, use ON/OFF";
    html_page = Html_construct();
    server.send(200, "text/html", html_page);
  } 
    
  

  digitalWrite(ledCon, HIGH);
  Serial.println("Solicitud aceptada");
  delay(500);
  digitalWrite(ledCon, LOW);
  i++;
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

void loop(){
  server.handleClient();
}