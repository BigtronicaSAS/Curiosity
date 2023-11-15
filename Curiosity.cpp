#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Curiosity.h"


Bot::Bot(){
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

void Bot::pitar() {
  digitalWrite(pin_buzzer, Button(PSB_CIRCLE) ? HIGH : LOW);
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

float Bot::detectar_obstaculo() {
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trigger, HIGH);
  unsigned long tiempoInicio = micros();

  while (digitalRead(pin_echo) == LOW) {
    if (micros() - tiempoInicio > 10000) { 
      Serial.println("Error: No se detectó el eco del sensor.");
      return -1; 
    }
  }

  tiempoInicio = micros();
  while (digitalRead(pin_echo) == HIGH) {
    if (micros() - tiempoInicio > 10000) { 
      Serial.println("Error: No se recibió el eco del sensor.");
      return -1; 
    }
  }

  unsigned long tiempoDiferencia = micros() - tiempoInicio;
  float distancia = (tiempoDiferencia / 2.0) * 0.0343;

  if (distancia == 0) {
    Serial.println("El sensor no está conectado.");
  }

  return distancia;
}


void Bot::obstaculos(int _distance){
  int distance = detectar_obstaculo();
  if(distance < _distance){
     digitalWrite(pin_buzzer, HIGH);
  } else if (distance >= _distance) {
     digitalWrite(pin_buzzer, LOW);
    }
}

void Bot::controlPS2(int pin_clock , int pin_command, int pin_attention, int pin_data){
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

void Bot::carPS2(){
  byte vibrate = 0;
  read_gamepad(false, vibrate); 
  int temp;
  pitar();
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

void Bot::seguidor(int Left, int Center, int Right, int velocidad){
  int blanco = 0;
  int negro = 1;
  bool IR_centro = digitalRead(Center);
  bool IR_izquierda = digitalRead(Left);
  bool IR_derecha = digitalRead(Right);
  Serial.print(IR_izquierda);
  Serial.print(IR_centro);
  Serial.print(IR_derecha);
  Serial.println("");
  
if ((IR_izquierda == blanco) && (IR_centro == negro) && (IR_derecha == blanco)){
  adelante(velocidad);
  Serial.println("Adelante");
}
else if ((IR_izquierda == negro) && (IR_centro == negro) && (IR_derecha == blanco)){
  girar_derecha(velocidad);
  Serial.println("derecha");
}
else if ((IR_izquierda == negro) && (IR_centro == blanco) && (IR_derecha == blanco)){
  girar_derecha(velocidad);
  Serial.println("derecha");
}

else if ((IR_izquierda == blanco) && (IR_centro == negro) && (IR_derecha == negro)){
  girar_izquierda(velocidad);
  Serial.println("Izquierda");
}
else if ((IR_izquierda == blanco) && (IR_centro == blanco) && (IR_derecha == negro)){
  girar_izquierda(velocidad);
  Serial.println("Izquierda");
}
else if ((IR_izquierda == blanco) && (IR_centro == blanco) && (IR_derecha == blanco)){
  parar();
  Serial.println("parar");
}
else if ((IR_izquierda == negro) && (IR_centro == negro) && (IR_derecha == negro)){
  adelante(velocidad);
  Serial.println("Adelante");
}

}



