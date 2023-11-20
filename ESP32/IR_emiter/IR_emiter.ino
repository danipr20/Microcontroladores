#include <Arduino.h>
#include <IRremote.h>

uint32_t irSignal = 0xC; // Tu señal IR de encendido RC6 de 20 bits

const int IR_SEND_PIN = 5; // Pin GPIO para el emisor IR en el ESP32

IRsend irsend(IR_SEND_PIN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Enviando señal de encendido...");

  irsend.sendRC6(irSignal, 20); // Envía la señal IR RC6

  delay(3000); // Espera 10 segundos antes de enviar otra señal
}
