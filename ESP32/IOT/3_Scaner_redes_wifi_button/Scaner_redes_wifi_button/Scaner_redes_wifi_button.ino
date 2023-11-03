#include<WiFi.h>

#define puls 17   //Conectar pin 17 a pulsador
                  //Sin pulsador, conectar pin 17 a GND para entrar en reposo, y conectar a +3v o +5v para comenzar ejecucion 
void setup() {
  // put your setup code here, to run once:
  pinMode(puls,INPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
 int net= WiFi.scanNetworks();
  if (digitalRead(puls)==HIGH) {
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
  }
  else{
    delay(500);
    
  }
}
