#include<WiFi.h>

#define puls 16
void setup() {
  // put your setup code here, to run once:
  pinMode(puls, INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(puls)==HIGH) {
  
  int net= WiFi.scanNetworks();
  Serial.println("\nWIFI scan begin");
  for (int i=1; i<=5; i++) {
  Serial.print(".");
  delay(500);
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

    }else{
      delay(500);}
}
