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

void Bot::play(){
  byte vibrate = 0;
  read_gamepad(false, vibrate); 
};

void Bot::car(){
  int temp;
  if(Button(PSB_PAD_UP))
  {  
    adelante(255);
    Serial.print("adelante");
  }
  
  else if(Button(PSB_PAD_RIGHT))
  {
    girar_derecha(255);
    Serial.print("derecha");
  }
  
  else if(Button(PSB_PAD_LEFT))
  {
    girar_izquierda(255);
    Serial.print("izquierda"); 
  } 
  else if(Button(PSB_PAD_DOWN))
  {
    atras(255);
    Serial.print("atras");
  }

  else
  {
   parar();
  }
  
  delay(15);
};




