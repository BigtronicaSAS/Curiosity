#include <Curiosity.h>
#include <Servo.h>

Bot bot;
void arm();

void setup() {
  bot.setup();
}

void loop() {
  bot.play();
  arm();
}

void arm(){
  
   if(bot.Button(PSB_PAD_UP))
  {  
    Serial.print("servo arriba");
  }
  
  else if(bot.Button(PSB_PAD_RIGHT))
  {
    Serial.print("servo derecha");
  }
  
  else if(bot.Button(PSB_PAD_LEFT))
  {
    Serial.print("servo izquierda"); 
  } 
  else if(bot.Button(PSB_PAD_DOWN))
  {
    Serial.print("servo atras");
  }
  delay(15);
  
}