#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <DHT_U.h>
//temp_anal
#include <OneWire.h>

#define TIME 2000

//temp digital
DHT dht(3, DHT11); //conectar sensor al pin D3
float temp;
float hum;
float temp_anal;

//temp anal
OneWire ds(10);  // on pin 10 (a 4.7K resistor is necessary)


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
delay(1000);
}

void loop() {
    digitalWrite(2, LOW);

  temp = dht.readTemperature();
  hum = dht.readHumidity();


  
  byte i;
  byte data[9];
  byte addr[8];
  float celsius;

  if (!ds.search(addr)) {
    
    ds.reset_search();
    delay(250);
    return 0.0;  // Devuelve un valor por defecto en caso de error
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    return 0.0;  // Devuelve un valor por defecto en caso de error
  }

  // El primer byte ROM indica qué chip es
  switch (addr[0]) {
    case 0x10:
      break;
    case 0x28:
      break;
    case 0x22:
      break;
    default:
      return 0.0;  // Devuelve un valor por defecto en caso de error
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);  // Inicia la conversión, con alimentación parásita al final
  delay(1000);        // Quizás 750ms es suficiente, tal vez no

  ds.reset();
  ds.select(addr);
  ds.write(0xBE);  // Lee el Scratchpad

  for (i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  // Convierte los datos a temperatura real
  int16_t raw = (data[1] << 8) | data[0];
  if (addr[0] == 0x10) {
    raw = raw << 3;  // Resolución predeterminada de 9 bits
    if (data[7] == 0x10) {
      // "count remain" da resolución completa de 12 bits
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;      // Resolución de 9 bits, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // Resolución de 10 bits, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // Resolución de 11 bits, 375 ms
    // Predeterminado es resolución de 12 bits, tiempo de conversión de 750 ms
  }
  temp_anal = (float)raw / 16.0;


  Serial.println("Temperatura y humedad, sensor digital:");
  Serial.print("Temperatura = ");
  Serial.print(String(temp));
  Serial.print("     Humedad = ");
  Serial.println(hum);

  Serial.println("Temperatura, sensor analogico:");
  Serial.print("Temperatura = ");
  Serial.print(String(temp_anal));

  myFile = SD.open("ARDUINO/Proyect/registro/" + nombreArchivoCompl, FILE_WRITE);

  myFile.print("Registro ");
  myFile.println(i);

  myFile.println("Temperatura y humedad, sensor digital:");
  myFile.print("Temperatura = ");
  myFile.print(String(temp));
  myFile.print("     Humedad = ");
  myFile.println(hum);
/*
  myFile.println("Temperatura, sensor analogico:");
  myFile.print("Temperatura = ");
  myFile.println(String(temp_anal));
*/
  myFile.close();
  digitalWrite(2, HIGH);

  i++;
  delay(TIME);
}