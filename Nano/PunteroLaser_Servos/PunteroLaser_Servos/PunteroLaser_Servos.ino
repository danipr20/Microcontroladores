#include <Servo.h>



Servo servoX;  // Servo para el eje X
Servo servoY;  // Servo para el eje Y

#define potYPin A0 // Pin analógico para el potenciómetro del eje X
#define potXPin A1 // Pin analógico para el potenciómetro del eje Y

#define serX 3
#define serY 4

void setup() {
  servoX.attach(serX); // Adjunta el servo del eje X al pin D2
  servoY.attach(serY); // Adjunta el servo del eje Y al pin D3
}

void loop() {
  // Lee el valor de los potenciómetros
  int potXValue = analogRead(potXPin); // Lee el potenciómetro del eje X
  int potYValue = analogRead(potYPin); // Lee el potenciómetro del eje Y

  // Mapea los valores de los potenciómetros a ángulos para los servos (0-180 grados)
  int angleX = map(potXValue, 0, 1023, 45, 145);
  int angleY = map(potYValue, 0, 1023, 45, 145);
  // Mueve los servos a las posiciones calculadas
  servoX.write(angleX);
  servoY.write(angleY);

  delay(100); // Pequeña pausa para estabilizar la posición de los servos
}
