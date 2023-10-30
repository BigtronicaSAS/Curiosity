#include <Curiosity.h>
#include <Servo.h>
Bot bot;

Servo servoBase;
Servo servoHombro;
Servo motor_3;
Servo motor_4;
Servo motor_5;

int servo1 = 70;
int servo2 = 180;
int servo3 = 40;
int servo4 = 50;
int servo5 = 90;

int bt_data;
void setup() {

  Serial.begin(9600);

  servoBase.attach(9);
  servoHombro.attach(8);
  motor_3.attach(10);
  motor_4.attach(11);
  motor_5.attach(12);

  servoBase.write(servo1);
  servoHombro.write(servo2);
  motor_3.write(servo3);
  motor_4.write(servo4);
  motor_5.write(servo5);
}

void loop() {


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
    if (servo3 > 0) {
      servo3 = servo3 - 1;
    }
    motor_3.write(servo3);
  }
  else if (bt_data == 13) {
    if (servo3 < 180) {
      servo3 = servo3 + 1;
    }
    motor_3.write(servo3);
  }

  else if (bt_data == 14) {
    if (servo4 < 180) {
      servo4 = servo4 + 1;
    }
    motor_4.write(servo4);
  }
  else if (bt_data == 15) {
    if (servo4 > 0) {
      servo4 = servo4 - 1;
    }
    motor_4.write(servo4);
  }

  else if (bt_data == 16) {
    if (servo5 > 90) {
      servo5 = servo5 - 1;     
    }
    motor_5.write(servo5);
  }
  else if (bt_data == 17) {
    if (servo5 < 150) {
      servo5 = servo5 + 1;
    }
    motor_5.write(servo5);
  }

}