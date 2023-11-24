#include <DHT.h>
#include <DHT_U.h>


DHT dht(D1,DHT11);
float temp;
float hum;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
dht.begin();

}

void loop() {
temp = dht.readTemperature();
hum = dht.readHumidity();
Serial.print("Temperatura = "); Serial.print(  String(temp));
Serial.print("     Humedad = "); Serial.println(hum);

delay (60000);




}
