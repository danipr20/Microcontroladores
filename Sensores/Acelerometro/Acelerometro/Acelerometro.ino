#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() {
  Serial.begin(9600);
  if (!accel.begin()) {
    Serial.println("El sensor no se inició");
    while (1);
  } else {
    Serial.println("El sensor se inició");
  }
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  Serial.print("X= ");
  Serial.print(event.acceleration.x);  // Corregir aquí
  Serial.print(", Y= ");  // Agregar coma aquí
  Serial.print(event.acceleration.y);  // Corregir aquí
  Serial.print(", Z= ");
  Serial.println(event.acceleration.z);

  delay(1000);  // Añadir un retraso para no imprimir demasiado rápido
}
