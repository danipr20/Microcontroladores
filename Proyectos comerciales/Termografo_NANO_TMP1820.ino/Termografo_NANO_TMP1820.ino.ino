#include <SPI.h>
#include <SD.h>

//temp_anal
#include <OneWire.h>

#define TIME 2000

//temp digital
OneWire ds(10);  // on pin 10 (a 4.7K resistor is necessary)

float temp_anal;

//temp anal


File myFile;
int i = 0;
int numArch = 0;
String nombreArchivo = "regdat";
String terminacion = ".txt";
String nombreArchivoCompl = "";




void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(9600);
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




  byte i;
  byte data[9];
  byte addr[8];
  float celsius;
  
  if (!ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    return;
  }

  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      break;
    case 0x28:
      break;
    case 0x22:
      break;
    default:
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);  // start conversion, with parasite power on at the end
  delay(1000);        // maybe 750ms is enough, maybe not

  ds.reset();
  ds.select(addr);
  ds.write(0xBE);  // Read Scratchpad

  for (i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  // Convert the data to actual temperature
  int16_t raw = (data[1] << 8) | data[0];
  if (addr[0] == 0x10) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;      // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  }
  celsius = (float)raw / 16.0;


  
  Serial.print("Temperature = ");
  Serial.println(celsius);
  temp_anal=celsius;




  Serial.println("Temperatura, sensor analogico:");
  Serial.print("Temperatura = ");
  Serial.print(String(temp_anal));

  myFile = SD.open("ARDUINO/Proyect/registro/" + nombreArchivoCompl, FILE_WRITE);

  myFile.print("Registro ");
  myFile.println(i);



  myFile.println("Temperatura, sensor analogico:");
  myFile.print("Temperatura = ");
  myFile.println(String(temp_anal));

  myFile.close();
  digitalWrite(2, HIGH);

  i++;
  delay(TIME);
}