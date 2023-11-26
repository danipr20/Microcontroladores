int MoistureSensor;
int actuadorAguaPin = 8;
int actuadorParaPin = 7;
bool regando = false;
bool necesitaRegar = false;
bool actuadorPara = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(actuadorAguaPin, OUTPUT);
  pinMode(actuadorParaPin, INPUT);
}

void loop() {

  //Lectura de parametros
  MoistureSensor = analogRead(A3);
  actuadorPara = digitalRead(actuadorParaPin);


  //Controladora y establecimiento de modos en funcion de los parametros leidos
  if (MoistureSensor > 1000) {
    Serial.println("Sensor desconectado o fuera de la tierra");
  } else if (MoistureSensor > 600) {
    Serial.println("Bro, dale awita a la planta");
    necesitaRegar = true;
    Serial.print("bool necesita regar =");
    Serial.println(necesitaRegar);
  } else if (MoistureSensor > 370) {
    Serial.println("Suelo humedo, ta fleje mi pana");
  } else if (MoistureSensor < 370) {
    Serial.println("Bro tienes un poco de tierra en tu agua");
    necesitaRegar = false;
  }
  //Serial.println(MoistureSensor);




  //actuacion en funcion del sistema de control
  if (necesitaRegar == true && actuadorPara == true) {
    regando = true;
    digitalWrite(actuadorAguaPin, HIGH);

  } else {
    digitalWrite(actuadorAguaPin, LOW);
    regando = false;
    necesitaRegar = false;
  }


  delay(5000);
}
