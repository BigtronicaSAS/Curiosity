#include <Curiosity.h>

Bot bot;

void setup() {
  bot.setup();

}

void loop() {
bot.obstaculos(20);
bot.play();
bot.car(); 
}