#include <ESP32Servo.h>


Servo servoX;  // Servo para el eje X
Servo servoY;  // Servo para el eje Y

int potYPin = 15; // Pin analógico para el potenciómetro del eje X
int potXPin = 2; // Pin analógico para el potenciómetro del eje Y

void setup() {
  servoX.attach(18); // Adjunta el servo del eje X al pin GPIO2
  servoY.attach(19); // Adjunta el servo del eje Y al pin GPIO4
}

void loop() {
  // Lee el valor de los potenciómetros
  int potXValue = analogRead(potXPin); // Lee el potenciómetro del eje X
  int potYValue = analogRead(potYPin); // Lee el potenciómetro del eje Y

  // Mapea los valores de los potenciómetros a ángulos para los servos (0-180 grados)
  int angleX = map(potXValue, 0, 4095, 45, 135);
  int angleY = map(potYValue, 0, 4095, 45, 135);

  // Mueve los servos a las posiciones calculadas
  servoX.write(angleX);
  servoY.write(angleY);

  delay(50); // Pequeña pausa para estabilizar la posición de los servos
}
