#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework

#define LED_ROJO 2
#define LED_AMBAR 3
#define LED_VERDE 4

#define LED_VERDE_PEATON 5
#define LED_ROJO_PEATON 6





#define PULS_1 7
#define PULS_2 8



bool VERDE=false;
bool AMBAR=false;
bool ROJO=false;
bool camb=true;
int i=0;

bool est_puls_1 = HIGH;  // Inicializado en HIGH para representar que el pulsador no está presionado
bool est_puls_2 = HIGH;  // Inicializado en HIGH para representar que el pulsador no está presionado



void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AMBAR,OUTPUT);
  pinMode(LED_VERDE,OUTPUT);

  pinMode(LED_VERDE_PEATON,OUTPUT);
  pinMode(LED_ROJO_PEATON,OUTPUT);

  pinMode(PULS_1,INPUT);
  pinMode(PULS_2,INPUT);


}

void loop()
{


    if (VERDE==false&&AMBAR==false&&ROJO==false){
  VERDE=true;

    }
    if(VERDE==true){
      i=0;

do
{ 
    est_puls_1=digitalRead(PULS_1);    est_puls_2=digitalRead(PULS_2);



  digitalWrite(LED_VERDE, HIGH);



  digitalWrite(LED_ROJO_PEATON,HIGH);
  digitalWrite(LED_VERDE_PEATON,LOW);



  delay(100);
  i++;
} while (i < 100 && est_puls_1 == LOW && est_puls_2 == LOW);
  delay(1000);
  digitalWrite(LED_VERDE, LOW);
  VERDE=false;
  AMBAR=true;

    

  i=0;
    }
    if(AMBAR==true){
      digitalWrite(LED_ROJO_PEATON,HIGH);
      digitalWrite(LED_VERDE_PEATON,LOW);

}while (i<=3)
{
  digitalWrite(LED_AMBAR, HIGH);
  delay(400);
  digitalWrite(LED_AMBAR, LOW);
  delay(400);
  i++;
  }
    digitalWrite(LED_AMBAR, HIGH);
    delay(1000);
    digitalWrite(LED_AMBAR, LOW);
   AMBAR=false;
   ROJO=true;


if (ROJO==true)
{ 



  digitalWrite(LED_ROJO, HIGH);
  digitalWrite(LED_ROJO_PEATON,LOW);
  digitalWrite(LED_VERDE_PEATON,HIGH);
  delay(4000);
  digitalWrite(LED_ROJO, LOW);
  }
   ROJO=false;
   VERDE=true;

}