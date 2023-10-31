#include <Curiosity.h>
#include <Servo.h>
Bot bot; 
Servo LYservo;
Servo RXservo;
Servo RYservo;
Servo LXservo;

void setup(){
LYservo.attach(9);
RXservo.attach(6);
RYservo.attach(3);
LXservo.attach(5);
bot.setup();
}
void loop(){
bot.play();
bot.read_gamepad();
RXservo.write(map(bot.Analog(PSS_RX), 0, 255, 0, 179));
RYservo.write(map(bot.Analog(PSS_RY), 0, 255, 0, 179));
LXservo.write(map(bot.Analog(PSS_LX), 0, 255, 0, 179)); 
LYservo.write(map(bot.Analog(PSS_LY), 0, 255, 0, 179));
delay(50);
}