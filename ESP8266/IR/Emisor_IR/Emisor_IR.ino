#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

uint32_t signal = 0xC; // Tu señal IR de encendido RC6 de 20 bits

const int IR_SEND_PIN = 3; // Pin GPIO para el emisor IR

IRsend irsend(IR_SEND_PIN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Enviando señal de encendido...");

  irsend.sendRC6(signal, 20); // Envía la señal IR RC6

  delay(10000); // Espera 10 segundos antes de enviar otra señal
}
