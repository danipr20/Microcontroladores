#include<ESP8266WiFi.h>


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  IPAddress apIP = WiFi.localIP();
  Serial.print("IP Address of AP: ");
  Serial.println(apIP);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int net= WiFi.scanNetworks();
  Serial.println("\nWIFI scan begin");
  for (int i=1; i<=10; i++) {
  Serial.print(".");
  delay(1000);
  }
  Serial.print("\n");
  Serial.printf("Redes detectadas: %d",net);
  if(net == 0){
    Serial.println("\nNo hay redes disponibles");
  }
  Serial.print("\n");
    for (int i=0; i<net; i++) {
     
     Serial.print(i+1);
     Serial.print(" - ");
     Serial.print(WiFi.SSID(i));
     Serial.print(" (");
     Serial.print(WiFi.RSSI(i));
     Serial.print(" - ");
     Serial.print(WiFi.BSSIDstr(i));
     Serial.println(")");
     delay(100);
    }

}
