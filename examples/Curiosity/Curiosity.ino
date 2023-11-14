#include <Curiosity.h>

Bot bot;

void setup() {
  bot.setup();

}

void loop() {
bot.obstaculos(10);
bot.play();
bot.car(); 
}