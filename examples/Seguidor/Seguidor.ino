#include <Curiosity.h>
#define Right    A0
#define Center   A1
#define Left     A2
Bot bot;
void setup() {
bot.configSeguidor(Right, Center, Left);
}

void loop() {
	bot.seguidor();
}