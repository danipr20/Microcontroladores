#include <WiFi.h>


//Introducir Parámetros de la red a la que te quieres conectar_ SSID y PASSWORD
const char* ssid="SSID";
const char* password="PASSWORD";

void setup() {

Serial.begin(115200);
Serial.println("\nWIFI station setting");
WiFi.mode(WIFI_AP_STA);
WiFi.softAP("TU QUIERE MI PINGA EN TU CULO", "mondongo");
WiFi.begin(ssid, password);


while(  WiFi.status()!=WL_CONNECTED){ 
  delay(500); 
  Serial.print(".");
    }
  Serial.println("\n WIFI ready");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
int power= WiFi.RSSI();
Serial.printf("Signal dB: %d\n",power);
delay(3500);
}