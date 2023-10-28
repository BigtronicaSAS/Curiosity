/*
  Curiosity.h - Librería de plataforma curiosity con control play 2.
  Creado por Juan Camilo Alvarez.
  Version: 1.0V
*/
#ifndef Curiosity_h
#define Curiosity_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "PS2X_lib.h"


class Bot : public PS2X {
  public:
    Bot();
	void adelante(int velocidad);
	void atras(int velocidad);
	void girar_derecha(int velocidad);
	void girar_izquierda(int velocidad);
	void parar();
	float detectar_obstaculo();
	void setup();
	void car();
	void play();
  private:
	int MotorA_speed;
    int MotorA_direction;
    int MotorB_speed;
    int MotorB_direction;
	int pin_echo;
	int pin_trigger;
	int pin_buzzer;
	int pin_clock;
    int pin_command;
    int pin_attention; 
    int pin_data; 
};

#endif