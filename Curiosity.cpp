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
  Serial.begin(9600);
  pinMode(pin_echo, INPUT);
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
 
  digitalWrite(pin_trigger, LOW);
  digitalWrite(pin_buzzer, LOW);
}

void Bot::driver(const String &driverName){
    if (driverName == "L298P") {
        motorDriver = new L298PDriver();
    } else if (driverName == "L298") {
        motorDriver = new L298Driver();
    } else if (driverName == "L293D") {
        motorDriver = new L293DDriver();
    } else {
       Serial.println("Driver no encontrado");
    }
}


void Bot::girar_derecha(int velocidad){
 motorDriver->girar_derecha(velocidad);
}

void Bot::girar_izquierda(int velocidad){
  motorDriver->girar_izquierda(velocidad);
}

void Bot::adelante(int velocidad){
 motorDriver->adelante(velocidad); 
}

void Bot::atras(int velocidad){
 motorDriver->atras(velocidad); 
}

void Bot::parar(){
 motorDriver->parar(); 
}

float Bot::detectar_obstaculo() {
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trigger, HIGH);
  unsigned long tiempoInicio = micros();

  while (digitalRead(pin_echo) == LOW) {
    if (micros() - tiempoInicio > 10000) { // Esperar un máximo de 10 ms
      Serial.println("Error: No se detectó el eco del sensor.");
      return -1; // Valor de error
    }
  }

  tiempoInicio = micros();
  while (digitalRead(pin_echo) == HIGH) {
    if (micros() - tiempoInicio > 10000) { // Esperar un máximo de 10 ms
      Serial.println("Error: No se recibió el eco del sensor.");
      return -1; // Valor de error
    }
  }

  unsigned long tiempoDiferencia = micros() - tiempoInicio;
  float distancia = (tiempoDiferencia / 2.0) * 0.0343; // Velocidad del sonido en el aire a 20 °C

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




