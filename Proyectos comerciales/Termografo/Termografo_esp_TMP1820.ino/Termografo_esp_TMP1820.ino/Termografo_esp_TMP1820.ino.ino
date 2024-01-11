#include <SPI.h>
#include <SD.h>

//temp_anal
#include <OneWire.h>

int TIME = 1;  //SEGUNDOS

//temp digital
OneWire ds(7);  // on pin 10 (a 4.7K resistor is necessary)

float temp_anal;

//variables config
byte configDat[10];
int numCon = 0;



File myFile;


int tiempo = 0;
int nReg = 0;
int numArch = 0;
String nombreArchivo = "regdat";
String terminacion = ".txt";
String nombreArchivoCompl = "";

void resetearArray() {
  // Establecer todos los elementos del array en 255
  for (int i = 0; i < 10; i++) {
    configDat[i] = 255;
  }
}

void creaRegistro(){
  do {
    nombreArchivoCompl = nombreArchivo + String(numArch) + terminacion;
    numArch++;
  } while (SD.exists("ARDUINO/Proyect/registro/" + nombreArchivoCompl));
}

void setup() {
  //variables config
  String tiempoConfig = "";
  byte lect = 255;
  //int lineaConfig = 0;
  int hora = 0;

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  Serial.begin(9600);
  SD.begin(4);

  resetearArray();
  // SD.mkdir("Arduino");
  SD.mkdir("ARDUINO/Proyect/registro");
  SD.mkdir("ARDUINO/Proyect/config");


  creaRegistro();

  SD.remove("ARDUINO/Proyect/config/config.ini");


  // Lee la primera linea del archivo y la admite como el valor de Tiempo muestreo
  ///////////////////////////// LECTOR DE ARCHIVO CONFIG, HAY QUE REPASARLO PORQUE NO FUNCIONA
  myFile = SD.open("ARDUINO/Proyect/config/config.ini", FILE_WRITE);
  myFile.println("24");  //tiempo de muestreo

  myFile.close();

  myFile = SD.open("ARDUINO/Proyect/config/config.ini", FILE_READ);

  //Importante, para leer el valor correctamente en el archivo debe haber un \n , es decir si se escribe el valor mediante codigo usar println y si no dar enter a mano

  while ((lect = myFile.read()) != 255) {
    Serial.println(lect);
    if ((lect != '\n') || (lect = myFile.read() == 255)) {
      configDat[numCon] = lect;
      numCon++;
    } else {
      //lineaConfig++;
      for (int z = 0; z < numCon; z++) {
        char charActual = char(configDat[z]);
        tiempoConfig += charActual;

        Serial.print("configDat ");
        Serial.print(z);
        Serial.print(" = ");
        Serial.println(charActual);
        Serial.print("tiempoConfig = ");
        Serial.println(tiempoConfig);
      }

      resetearArray();
    }

    TIME = tiempoConfig.toInt();

    //Habrá que ver como leer las distintas lineas del archivo de configuración
    /*switch (lineaConfig) {
      case 1:
        TIME = tiempoConfig.toInt();
        break;
      case 2:
        hora = tiempoConfig.toInt();
        break;
      default:
        break;
    }*/
  }

  Serial.print("Tiempo seleccionado= ");
  Serial.println(TIME);
  Serial.print("HORA seleccionado= ");
  Serial.println(hora);
  myFile.close();
  /////////////////////////////

  Serial.print("Tiempo seleccionado= ");
  Serial.println(TIME);
  digitalWrite(2, LOW);
}




void loop() {

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
    raw = raw << 3;  // 9 bit resolution default
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;       // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3;  // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1;  // 11 bit res, 375 ms
  }
  celsius = (float)raw / 16.0;

  temp_anal = celsius;

  Serial.println("Temperatura, sensor analogico:");
  Serial.print("Temperatura = ");
  Serial.println(String(temp_anal));

  Serial.print("TIEMPO MUESTREO = ");
  Serial.println(String(TIME));

  myFile = SD.open("ARDUINO/Proyect/registro/" + nombreArchivoCompl, FILE_WRITE);

  myFile.print(tiempo);
  myFile.print(";");
  myFile.print(nReg);
  myFile.print(";");
  myFile.println(String(temp_anal));


  myFile.close();

  nReg++;
  delay(TIME * 1000);
  tiempo = tiempo + TIME;
}