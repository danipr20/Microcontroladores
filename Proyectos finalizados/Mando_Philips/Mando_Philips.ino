#include <Arduino.h>
#include <IRremote.h>



const int IR_SEND_PIN = 3;   // Pin GPIO para el emisor IR
const int BUTTON_PIN_4 = 4;  // Pin apagado tv
//const int BUTTON_PIN_5 = 5;  // Pin al que está conectado el botón 1
//const int BUTTON_PIN_6 = 6;  // Pin al que está conectado el botón 2

IRsend irsend(IR_SEND_PIN);
uint32_t signal = 0xC;  // Tu señal IR de encendido RC6 de 20 bits




void setup() {
  pinMode(BUTTON_PIN_4, INPUT);
  /*Serial.begin(9600);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  pinMode(BUTTON_PIN_6, INPUT_PULLUP);*/

}


void loop() {


  if (digitalRead(BUTTON_PIN_4) == HIGH) {
    irsend.sendRC6(signal, 20);  // Envía la señal IR RC6
    Serial.println("TV ON/OFF");

    delay(1000);  // Espera 7 segundos antes de enviar otra señal

  } 
  
  
  
  
  
  
  /* else if (digitalRead(BUTTON_PIN_5) == HIGH) {
    // Botón 1 presionado, enviar señal 2

    const uint16_t irSignalOn[24] = { 50, 1350, -350, 1300, -350, 500, -1150, 500, -1200, 450, -1200, 450, -1200, 450, -1200, 500, -1200, 1300, -350, 450, -1200, 450, -1200, 450 };
    Serial.println("lUZ ON");
    irsend.sendRaw(irSignalOn,24, khz);  //Note the approach used to automatically calculate the size of the array.

    delay(1000);  // Espera 7 segundos antes de enviar otra señal

  } else if (digitalRead(BUTTON_PIN_6) == HIGH) {
    // Botón 2 presionado, enviar señal 3
    const uint16_t irSignalOff[24] = { 642600, 1350, -350, 1300, -350, 500, -1150, 500, -1150, 500, -1150, 500, -1150, 1350, -350, 500, -1150, 500, -1150, 500, -1150, 500, -1150, 550 };
    Serial.println("LUZ OFF");

    irsend.sendRaw(irSignalOff, 24, khz);  //Note the approach used to automatically calculate the size of the array.

    delay(1000);  // Espera 7 segundos antes de enviar otra señal
  }*/
}
