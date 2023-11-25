// Definir pines del sensor
const int trigPin = 9;  // Pin de salida del pulso ultrasónico
const int echoPin = 10; // Pin de entrada para medir la duración del pulso

void setup() {
  Serial.begin(9600);  // Iniciar comunicación serial
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Generar pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medir la duración del pulso de eco
  unsigned long duration = pulseIn(echoPin, HIGH);

  // Calcular la distancia en milímetros
  // La velocidad del sonido es de aproximadamente 343 metros por segundo
  // La distancia se calcula dividiendo la duración por 2 y multiplicando por la velocidad del sonido
   float distanceCM = duration * 0.000343 / 2;

  // Imprimir la distancia en la consola
  Serial.print("Distancia: ");
  Serial.print(distanceCM);
  Serial.println(" m");

  delay(1000);  // Esperar un segundo antes de realizar la siguiente medición
}
