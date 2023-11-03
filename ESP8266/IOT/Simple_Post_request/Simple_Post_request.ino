#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

//Introducir Parámetros de la red a la que te quieres conectar_ SSID y PASSWORD
const char* ssid="SSID";
const char* password="PASSWORD";

const String host = "httpbin.org";
const String endpoint = "/post";

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

  String dato1 = "20012";
  String dato2 = "patata";

  String postData = "dato1=" + dato1 + "&dato2=" + dato2;
  String url = "http://" + host + endpoint;

  Serial.print("Request Link: ");
  Serial.println(url);

  http.begin(client, url);
  http.addHeader("Content-Type", "text/plain");

  Serial.print("Post Data:");
  Serial.println(postData);
  int httpCode = http.POST(postData);

  String payload = http.getString();

  Serial.print("Response code: ");
  Serial.println(httpCode);
  Serial.print("Returned data from Server: ");
  Serial.println(payload);

  http.end();
  delay(5000);
}