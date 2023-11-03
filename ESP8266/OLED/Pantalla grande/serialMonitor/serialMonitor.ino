#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int maxLines = 6; // Cantidad máxima de líneas a mostrar
String lines[maxLines];
int currentLine = 0;

void setup() {
  Serial.begin(9600);
  display.begin(0x3C, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 16);
  display.cp437(true);
  display.write(173);
  display.write(173);
  display.display();
}

void loop() {
  static int i = 0;
  
  // Borra la pantalla
  display.clearDisplay();

  // Actualiza las líneas en el arreglo
  lines[currentLine] = "Valor de i: " + String(i);
  currentLine = (currentLine + 1) % maxLines;

  // Muestra las líneas en orden
  int displayLine = 0;
  for (int j = 0; j < maxLines; j++) {
    int index = (currentLine + j) % maxLines;
    display.setCursor(10, displayLine * 8 + 16);
    display.print(lines[index]);
    displayLine++;
  }

  // Muestra la pantalla
  display.display();

  // Muestra el valor en el puerto serie
  Serial.println("Valor de i: " + String(i));

  i++;
  delay(1000);
}
