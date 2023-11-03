#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int devicesConnected = 0;
int prevDevicesConnected = -1;

const int historySize = 5;  // Tamaño del historial
int devicesHistory[historySize];
int historyIndex = 0;

void setup() {
  Serial.begin(9600);

  // Inicializa la pantalla OLED
  display.begin(0x3C, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 16);
  display.cp437(true);
  display.write(173);
  display.write(173);
  display.display();
  
  // Configura el ESP8266 como Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Vendo opel corsa", "");
}

void loop() {
  // Obtiene el número de dispositivos conectados
  devicesConnected = WiFi.softAPgetStationNum();
  
  // Verifica si ha habido un cambio en las conexiones
  if (devicesConnected != prevDevicesConnected) {
    // Actualiza el historial
    devicesHistory[historyIndex] = devicesConnected;
    historyIndex = (historyIndex + 1) % historySize;
    
    // Borra la pantalla
    display.clearDisplay();
    
    // Muestra el estado actual
    display.setCursor(10, 16);
    display.print("Device connected: ");
    display.print(devicesConnected);
    
    // Muestra el historial de estados anteriores
    int x = 10;
    int y = 32;
    for (int i = 0; i < historySize; i++) {
      display.setCursor(x, y);
      display.print("State " + String(i) + ": " + String(devicesHistory[i]));
      y += 8;
    }
    
    // Muestra la pantalla
    display.display();
    
    // Actualiza el valor previo
    prevDevicesConnected = devicesConnected;
  }
  
  // Espera un momento antes de verificar de nuevo
  delay(1000);
}
