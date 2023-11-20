#include <Arduino.h>
#include <IRremote.h>


int RECV_PIN = 11;


IRrecv irrecv(RECV_PIN);

decode_results results;

const int IR_SEND_PIN = 3; // Pin GPIO para el emisor IR
const int BUTTON_PIN_4 = 4; // Pin al que está conectado el botón 0
const int BUTTON_PIN_5 = 5; // Pin al que está conectado el botón 1
const int BUTTON_PIN_6 = 6; // Pin al que está conectado el botón 2

IRsend irsend(IR_SEND_PIN);
uint32_t signal = 0xC; // Tu señal IR de encendido RC6 de 20 bits
int khz=38;




void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  pinMode(BUTTON_PIN_6, INPUT_PULLUP);
}

void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) { 
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(" Value: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
 
  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }


  if (digitalRead(BUTTON_PIN_4) == HIGH) {
    // Botón 0 presionado, enviar señal 1
      irsend.sendRC6(signal, 20); // Envía la señal IR RC6

    delay(1000); // Espera 7 segundos antes de enviar otra señal

  } else if (digitalRead(BUTTON_PIN_5) == HIGH) {
    // Botón 1 presionado, enviar señal 2
  const uint16_t irSignalOn[] = {50, 1350, -350, 1300, -350, 500, -1150, 500, -1200, 450, -1200, 450, -1200, 450, -1200, 500, -1200, 1300, -350, 450, -1200, 450, -1200, 450};
    Serial.println("lUZ ON");
      irsend.sendRaw(irSignalOn, sizeof(irSignalOn) / sizeof(irSignalOn[0]), khz); //Note the approach used to automatically calculate the size of the array.

    delay(1000); // Espera 7 segundos antes de enviar otra señal

  } else if (digitalRead(BUTTON_PIN_6) == HIGH) {
    // Botón 2 presionado, enviar señal 3
  const uint16_t irSignalOff[] = {642600, 1350, -350, 1300, -350, 500, -1150, 500, -1150, 500, -1150, 500, -1150, 1350, -350, 500, -1150, 500, -1150, 500, -1150, 500, -1150, 550};
    Serial.println("LUZ OFF");
irsend.sendRaw(irSignalOff, sizeof(irSignalOff) / sizeof(irSignalOff[0]), khz); //Note the approach used to automatically calculate the size of the array.

    delay(1000); // Espera 7 segundos antes de enviar otra señal
  }
  // Agrega más casos según sea necesario para otros botones o acciones
}
