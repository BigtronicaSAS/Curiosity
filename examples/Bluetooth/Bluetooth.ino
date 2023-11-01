#include <Curiosity.h>
#include <Servo.h>
Bot bot;

Servo servoBase;
Servo servoHombro;
Servo servoCodo;
Servo servoGarra;


int servo1 = 70;
int servo2 = 70;
int servo3 = 60;
int servo4 = 90;

int bt_data;
void setup() {

  Serial.begin(9600);
  servoBase.attach(9);
  servoHombro.attach(6);
  servoCodo.attach(5);
  servoGarra.attach(2);
  servoBase.write(servo1);
  servoHombro.write(servo2);
  servoCodo.write(servo3);
  servoGarra.write(servo4);
}

void loop() {
  bot.obstaculos(10);
  if (Serial.available() > 0) {
    bt_data = Serial.read();
    Serial.println(bt_data);
  }

  if (bt_data == 1) {
    bot.adelante(255);
  }
  else if (bt_data == 2) {
    bot.atras(255); 
  }
  else if (bt_data == 3) {
    bot.girar_izquierda(255); 
  }
  else if (bt_data == 4) {
    bot.girar_derecha(255); 
  }
  else if (bt_data == 5) {
    bot.parar(); 
  }

  else if (bt_data == 8) {
    if (servo1 < 180) {
      servo1 = servo1 + 1;
    }
    servoBase.write(servo1);
  }
  else if (bt_data == 9) {
    if (servo1 > 0) {
      servo1 = servo1 - 1;
    }
    servoBase.write(servo1);
  }

  else if (bt_data == 10) {
    if (servo2 > 55) {
      servo2 = servo2 - 1;
    }
    servoHombro.write(servo2);
  }
  else if (bt_data == 11) {
    if (servo2 < 180) {
      servo2 = servo2 + 1;
    }
    servoHombro.write(servo2);
  }

  else if (bt_data == 12) {
    if (servo3 < 180) {
      servo3 = servo3 + 1;
    }
    servoCodo.write(servo3);

  }

  else if (bt_data == 13) {
    if (servo3 > 0) {
      servo3 = servo3 - 1;
    }
    servoCodo.write(servo3);
  }
  else if (bt_data == 16) {
    if (servo4 > 90) {
      servo4 = servo4 - 1;     
    }
    servoGarra.write(servo4);
  }
  else if (bt_data == 17) {
    if (servo4 < 150) {
      servo4 = servo4 + 1;
    }
    servoGarra.write(servo4);
  }

}