#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WebServer.h>

DHT dht(17, DHT11);
float temp;
float hum;

const char *ssid = "";
const char *password = "";

WebServer server(80);

void handleRoot()
{
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  String html_page = "<!DOCTYPE html><html><head> <title>Mi Pagina de Pruebas IoT: Danipr20</title></head><body> <h1>Bienvenido a Mi Pagina IoT</h1> <p>Temperatura: " + String(temp) + " &deg;C</p> <p>Humedad: " + String(hum) + " %</p> <p>Estado del dispositivo: <span id=\"estado\">Desconectado</span></p> <button onclick=\"encender()\">Encender</button> <button onclick=\"apagar()\">Apagar</button> <script> function encender() { document.getElementById('estado').innerText = 'Encendido'; // Aquí puedes agregar código para controlar tu dispositivo IoT cuando se enciende. } function apagar() { document.getElementById('estado').innerText = 'Apagado'; // Aquí puedes agregar código para controlar tu dispositivo IoT cuando se apaga. } </script></body></html>";

  server.send(200, "text/html", html_page);
}

void setup()
{
  Serial.begin(115200);
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

void loop()
{
  server.handleClient();
}