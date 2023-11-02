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

class MotorDriver {
	public:
	void adelante(int velocidad);
	void atras(int velocidad);
	void girar_derecha(int velocidad);
	void girar_izquierda(int velocidad);
	void parar();
};
// Implementación de L298PDriver
class L298PDriver : public MotorDriver {
	public:
	L298PDriver() {
        MotorA_speed = 10;
        MotorA_direction = 12;
        MotorB_speed = 11;
        MotorB_direction = 13;
        pinMode(MotorA_direction, OUTPUT);
        pinMode(MotorA_speed, OUTPUT);
        pinMode(MotorB_speed, OUTPUT);
        pinMode(MotorB_direction, OUTPUT);
    }
	void adelante(int velocidad){
		digitalWrite(MotorA_direction, LOW);
		digitalWrite(MotorB_direction, LOW);
		analogWrite(MotorA_speed, (velocidad));
		analogWrite(MotorB_speed, (velocidad));
    }

    void atras(int velocidad) {
		digitalWrite(MotorA_direction, HIGH);
		digitalWrite(MotorB_direction, HIGH);
		analogWrite(MotorA_speed, (velocidad));
		analogWrite(MotorB_speed, (velocidad));
    }

    void parar() {
		analogWrite(MotorA_speed, 0);
		analogWrite(MotorB_speed, 0);
    }

    void girar_derecha(int velocidad) {
		digitalWrite(MotorA_direction, LOW);
		digitalWrite(MotorB_direction, HIGH);
		analogWrite(MotorA_speed, (velocidad));
		analogWrite(MotorB_speed, (velocidad));
    }

    void girar_izquierda(int velocidad) {
		digitalWrite(MotorA_direction, HIGH);
		digitalWrite(MotorB_direction, LOW);
		analogWrite(MotorA_speed, (velocidad));
		analogWrite(MotorB_speed, (velocidad));
    }
	private:
    int MotorA_speed;
    int MotorA_direction;
    int MotorB_speed;
    int MotorB_direction;

};

// Implementación de L298Driver
class L298Driver : public MotorDriver {
 public:
    void adelante(int velocidad) {
        // Lógica específica para la shield L298
    }

    void atras(int velocidad) {
        // Lógica específica para la shield L298
    }

    void parar() {
        // Lógica específica para la shield L298
    }

    void girar_derecha(int velocidad) {
        // Lógica específica para la shield L298
    }

    void girar_izquierda(int velocidad) {
        // Lógica específica para la shield L298
    }
};

// Implementación de L293DDriver
class L293DDriver : public MotorDriver {
 public:
    void adelante(int velocidad) {
        // Lógica específica para la shield L293D
    }

    void atras(int velocidad) {
        // Lógica específica para la shield L293D
    }

    void parar() {
        // Lógica específica para la shield L293D
    }

    void girar_derecha(int velocidad) {
        // Lógica específica para la shield L293D
    }

    void girar_izquierda(int velocidad) {
        // Lógica específica para la shield L293D
    }
};

class Bot : public PS2X {
  public:
    Bot();
	void driver(const String &driverName);
	void adelante(int velocidad);
	void atras(int velocidad);
	void girar_derecha(int velocidad);
	void girar_izquierda(int velocidad);
	void parar();
	float detectar_obstaculo();
	void obstaculos(int _distance);
	void setup();
	void car();
	void play();
  private:
    MotorDriver *motorDriver;
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