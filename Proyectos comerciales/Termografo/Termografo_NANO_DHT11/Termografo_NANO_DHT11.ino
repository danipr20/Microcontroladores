#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <DHT_U.h>

#define TIME 800

//
DHT dht(3, DHT11); //conectar sensor al pin D3
float temp;
float hum;

File myFile;
int i = 0;
int numArch = 0;
String nombreArchivo = "regdat";
String terminacion = ".txt";
String nombreArchivoCompl = "";

void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(9600);
  dht.begin();
  SD.begin(4);

  // SD.mkdir("Arduino");
  SD.mkdir("ARDUINO/Proyect/registro");

  do {
    nombreArchivoCompl = nombreArchivo + String(numArch) + terminacion;
    numArch++;
  } while (SD.exists("ARDUINO/Proyect/registro/" + nombreArchivoCompl));

  myFile = SD.open("ARDUINO/Proyect/registro/" + nombreArchivoCompl, FILE_WRITE);

  myFile.print("Config: ");
  myFile.print("Tiempo de muestreo establecido: ");
  myFile.print(TIME / 1000); myFile.print(" Segundos");  // Convierte a segundos

  myFile.close();
  digitalWrite(2, HIGH);
}

void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  Serial.print("Temperatura = ");
  Serial.print(String(temp));
  Serial.print("     Humedad = ");
  Serial.println(hum);

  myFile = SD.open("ARDUINO/Proyect/registro/" + nombreArchivoCompl, FILE_WRITE);

  myFile.print("Registro ");
  myFile.println(i);

  myFile.print("Temperatura = ");
  myFile.print(String(temp));
  myFile.print("     Humedad = ");
  myFile.println(hum);

  myFile.close();
  i++;
  delay(TIME);
}
