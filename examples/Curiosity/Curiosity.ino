#include <Curiosity.h>

Bot bot;

void setup() {
  delay(1000);
  bot.inicio();

}

void loop() {
bot.obstaculos(15);  // Parametro de distancia maxima de deteccion
bot.read_gamepad(true, vibrate); 
}