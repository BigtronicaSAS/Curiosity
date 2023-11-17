#include <Curiosity.h>
#define Right    A0
#define Center   A1
#define Left     A2
/*Velocidad Bigbot Magic: 100*/
#define Velocidad 100
/*Velocidad Bigbot 4WD: 180*/
// #define Velocidad 180 

Bot bot;

void setup() {
  Serial.begin(9600);
  pinMode(Right, INPUT);
  pinMode(Center, INPUT);
  pinMode(Left, INPUT);
}

void loop() {
	bot.seguidor(Left ,Center ,Right ,Velocidad);
}