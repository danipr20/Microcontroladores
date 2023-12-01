/*
  SD card basic file example

  This example shows how to create and destroy an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {

pinMode(2, OUTPUT);
/*
***Importante***
El archivo se crea en MAYUSCULAS
El limite de caracteres del nombre son 8, es decir el nombre más largo que admite es "12345678.txt"
*/
  SD.begin(4);

  SD.mkdir("Arduino");
  // open a new file and immediately close it:
  myFile = SD.open("Arduino/regdat1.txt", FILE_WRITE);
  myFile.println("Prueba de escritura");
  myFile.println("Prueba de escritura2");
  myFile.println("Prueba de escritura3");

  myFile.close();
  digitalWrite(2, HIGH);


}

void loop() {
delay(10000);

}



