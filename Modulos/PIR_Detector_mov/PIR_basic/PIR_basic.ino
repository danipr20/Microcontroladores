

#define PIR  3
int buzzPin = 7;
int buzzDelay = 10;
int ESTADO=0;

void setup() {
  // put your setup code here, to run once:
pinMode(PIR, INPUT);
pinMode(buzzPin, OUTPUT);

Serial.begin(9600);
delay(5000);

}

void loop() {
 ESTADO=digitalRead(PIR);
 if (ESTADO==HIGH) {
  Serial.println("Detectado....");
  digitalWrite(LED_BUILTIN, HIGH);
  
  
  delay(5000);


 
 }
 else {
 Serial.println("...");
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
 
   }
}
