#include <Servo.h>  
Servo servoBase;       
Servo servoAlejar;     
Servo servoAltura;       
Servo servoGarra;       
void armAutomatic()

void setup() {
  servoBase.attach(9);  
  servoAlejar.attach(3);  
  servoAltura.attach(5);  
  servoGarra.attach(2); 
}

void loop()
{
 armAutomatic();          
}


void armAutomatic(){
  servoAlejar.write(110); 
  delay(1000);
 //Cerrar Garra
 servoGarra.write(180);            
  delay(100);
  servoGarra.write(90); 

  //-----Modulo movimiento servo (derecho) (subir)

  for (int angulo2 = 110; angulo2 >= 70; angulo2 -= 1)  
  {
    servoAltura.write(angulo2);               
    delay(25);       
  }
  delay(1000);

  //-----Modulo movimiento servo (Base)

  for (int angulo0 = 120; angulo0 >= 50; angulo0 -= 1)    
  {
    servoBase.write(angulo0);         
    delay(25);                         
  }

  delay(1000);

  //-----Modulo movimiento servo (derecho) (bajar)

  for (int angulo2 = 70; angulo2 < 110; angulo2 += 1)   
  {
    servoAltura.write(angulo2);    
    delay(25);                       
  }
  delay(1000);     

  //-----Modulo movimiento servo ( derecho) (subir)

  for (int angulo2 = 110; angulo2 >= 70; angulo2 -= 1)   
  {
    servoAltura.write(angulo2);            
    delay(25);                   
  }
  delay(1000);

  //-----Modulo movimiento servo 2 (Base) (centrar)

  for (int angulo0 = 50; angulo0 < 120; angulo0 += 1)   
  {
    servoBase.write(angulo0);             
    delay(25);                        
  }
  delay(1000);              

  //-----Modulo movimiento servo (derecho) (bajar)

  for (int angulo2 = 70; angulo2 < 110; angulo2 += 1)  
  {
    servoAltura.write(angulo2);          
    delay(25);                       
  }
  delay(1000);   
}