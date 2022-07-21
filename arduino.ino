#include "BluetoothSerial.h"
#include <PWMOutESP32.h>


PWMOutESP32 pwm;
BluetoothSerial SerialBT;


#define led           2
#define mot_i         14
#define mot_ii        12
#define stb           32
#define mot_d         33
#define mot_dd        25
#define pin_pwm_i     27
#define pin_pwm_d     26


#define trig          5
#define echo          18


#define velocidadSonido 0.034


int velocidad = 255;
long duracion;
int distanciaCm;
char x;


void setup() {
  SerialBT.begin("Esclavo");
  pinMode(mot_i, OUTPUT);
  pinMode(mot_ii, OUTPUT);
  pinMode(stb, OUTPUT);
  pinMode(mot_d, OUTPUT);
  pinMode(mot_dd, OUTPUT);
  pinMode(pin_pwm_i, OUTPUT);
  pinMode(pin_pwm_d, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(stb, HIGH);
}


void loop() {
  if (SerialBT.available() > 0) {
    x = SerialBT.read();
  }


  if (x == 'w') {
    motores(velocidad, velocidad);
  }
  else if (x == 'a') {
    motores(-velocidad, velocidad);
  }
  else if (x == 's') {
    motores(-velocidad, -velocidad);
  }
  else if (x == 'd') {
    motores(velocidad, -velocidad);
  }
  else if (x == 'q') {
    motores(0,0);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duracion = pulseIn(echo, HIGH);
    distanciaCm = duracion * velocidadSonido / 2;


    SerialBT.println(distanciaCm);
  }
}


void motores(int motor_izq, int motor_der)
{
  if ( motor_izq >= 0 )
  {
    digitalWrite(mot_i,HIGH);
    digitalWrite(mot_ii,LOW); 
    pwm.analogWrite(pin_pwm_i,  motor_izq);
  }


  else if ( motor_izq == 0 )
  {
    digitalWrite(mot_i,HIGH);
    digitalWrite(mot_ii,HIGH); 
    pwm.analogWrite(pin_pwm_i,  0);
  }
  
  else
  {
    digitalWrite(mot_i,LOW); 
    digitalWrite(mot_ii,HIGH); 
    motor_izq = motor_izq*(-1); 
    pwm.analogWrite(pin_pwm_i,motor_izq); 
  }
 
  if ( motor_der >= 0 )
  {
    digitalWrite(mot_d,HIGH);
    digitalWrite(mot_dd,LOW);
    pwm.analogWrite(pin_pwm_d,motor_der);
  }


  else if ( motor_der == 0 )
  {
    digitalWrite(mot_d,HIGH);
    digitalWrite(mot_dd,HIGH); 
    pwm.analogWrite(pin_pwm_d,  0);
  }
  
  else
  {
    digitalWrite(mot_d,LOW);
    digitalWrite(mot_dd,HIGH);
    motor_der= motor_der*(-1);
    pwm.analogWrite(pin_pwm_d,motor_der);
  }  
}
