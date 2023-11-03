#include <WiFi.h>
#include <HTTPClient.h>

//Introducir Parámetros de la red a la que te quieres conectar_ SSID y PASSWORD
const char* ssid="SSID";
const char* password="PASSWORD";

const String host = "httpbin.org";
const String endpoint = "/get";

void setup() {
  Serial.begin(115200);
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
}

void loop() {
  WiFiClient client;
  HTTPClient http;

  String dato1 = "21";
  String dato2 = "32";

  String getData = "?dato1=" + dato1 + "&dato2=" + dato2;
  String url = "http://" + host + endpoint + getData;

  Serial.print("Request Link: ");
  Serial.println(url);

  http.begin(client, url);
  int errorCode = http.GET();
  String payload = http.getString();

  Serial.print("Response code: ");
  Serial.println(errorCode);
  Serial.print("Returned data from Server: ");
  Serial.println(payload);

  http.end();
  delay(5000);
}
