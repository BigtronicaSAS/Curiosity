#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Curiosity.h"


Bot::Bot(){
  pin_clock = A3; //Pin Clock
  pin_command = A1; // Pin comando
  pin_attention = A0; // Pin Atencion
  pin_data = A2; // Pin Data 
  pin_echo = 8;
  pin_trigger = 7;
  pin_buzzer = 4;
  MotorA_speed = 10;
  MotorA_direction = 12;
  MotorB_speed = 11;
  MotorB_direction = 13;
  Serial.begin(9600);
  pinMode(pin_echo, INPUT);
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(MotorA_direction , OUTPUT);
  pinMode(MotorA_speed , OUTPUT);
  pinMode(MotorB_speed ,OUTPUT);
  pinMode(MotorB_direction , OUTPUT);
  digitalWrite(pin_trigger, LOW);
  digitalWrite(pin_buzzer, LOW);
}


void Bot::girar_derecha(int velocidad){

  digitalWrite(MotorA_direction, LOW);
  digitalWrite(MotorB_direction, HIGH);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
	
}

void Bot::girar_izquierda(int velocidad){
  digitalWrite(MotorA_direction, HIGH);
  digitalWrite(MotorB_direction, LOW);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::adelante(int velocidad){
  digitalWrite(MotorA_direction, LOW);
  digitalWrite(MotorB_direction, LOW);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));

}

void Bot::atras(int velocidad){
  digitalWrite(MotorA_direction, HIGH);
  digitalWrite(MotorB_direction, HIGH);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::parar(){
  analogWrite(MotorA_speed, 0);
  analogWrite(MotorB_speed, 0);
}

float Bot::detectar_obstaculo(){
	digitalWrite(pin_trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
	float distancia = pulseIn(pin_echo, HIGH)*0.034/2;
	Serial.println(distancia);
	if (distancia == 0){
		Serial.println("El sensor no esta conectado");
	}else{
		return distancia;		
	}
	
}

void Bot::pitar() {
  digitalWrite(pin_buzzer, Button(PSB_CIRCLE) ? HIGH : LOW);
}



void Bot::servo(int angulo, int tiempo){
  attach(9);
  write(angulo);
  delay(tiempo);
}


void Bot::setup(){
  int error = 0; 
  error = config_gamepad(pin_clock , pin_command, pin_attention, pin_data, true, true);
  if(error == 0)
  {
    Serial.println("Controlador encontrado y configurado");
  }
  else
  {
    Serial.println("Error, mando no encontrado");
  }
  Serial.begin(9600);
}


void Bot::obstaculos(int _distance){
  delay(50);
  int distance = detectar_obstaculo();
  if(distance < _distance){
    parar();
    servo(10, 600);
    int servoReadRight = detectar_obstaculo();
    servo(170, 600);
    int servoReadLeft = detectar_obstaculo();
    servo(90, 600);
    if (servoReadLeft > servoReadRight) {
        girar_izquierda(255);
      } else {
        girar_derecha(255);
      }
  } else if (distance >= _distance) {
      adelante(255);
    }
}

void Bot::curiosity(){
  int temp;
  byte vibrate = 0;
  read_gamepad(false, vibrate); 
  pitar();
  
  if(Button(PSB_PAD_UP))
  {
    temp = Analog(PSAB_PAD_UP);    
    adelante(255);
    Serial.print("Presionaste el boton arriba: ");
    Serial.println(temp);
  }
  
  else if(Button(PSB_PAD_RIGHT))
  {
    temp = Analog(PSAB_PAD_RIGHT);
    girar_derecha(255);
    Serial.print("Presionaste el boton derecha: ");
    Serial.println(temp);
  }
  
  else if(Button(PSB_PAD_LEFT))
  {
    temp = Analog(PSAB_PAD_LEFT);
    girar_izquierda(255);
    Serial.print("Presionaste el boton izquierda: ");
    Serial.println(temp);    
  } 
  else if(Button(PSB_PAD_DOWN))
  {
    temp = Analog(PSAB_PAD_DOWN);
    atras(255);
    Serial.print("Presionaste el boton abajo: ");
    Serial.println(temp);    
   
  }

  else
  {
   parar();
  }
  
  delay(50);
};