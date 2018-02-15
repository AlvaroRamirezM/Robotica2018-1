// Project 40 - Building and Controlling a Tank Robot

#include <Wire.h>

int m1speed=6; // digital pins for speed control
int m2speed=5;
int m1direction=7; // digital pins for direction control
int m2direction=4;
int tiempo = 250;
int delayP = 1000;
int Comando_0;
int poscicion = 0;
/**
 * Configuración inicial, se seleccionan los pines de salida para las ruedas y se hace begin al wire y al serial 
 */
void setup()
{
 pinMode(m1direction, OUTPUT);
 pinMode(m2direction, OUTPUT);
 Wire.begin();
 Serial.begin(9600);
 delay(5000);
}
/**
 * Loop de funcionamiento
 * 1. Espera al comando de inicio via serial
 * 2. Realizar movimientos hacia adelante, izquierda, derecha y reversa
 * 3. Lectura del ángulo izquierdo
 * 4. Lectura del ángulo derecho
 */
void loop()
{
  esperarComando();
  ejecutarMovimientos();
  leer(7);
  leer(8);
}
/**
 * Realiza espera activa sobre el serial 
 * Al escribir el comando 0 se inicia la secuencia y se procede al siguiente método, de lo contrario sigue realizando la espera
 */
void esperarComando()
{
  espera:
  Serial.flush();
 while (Serial.available() == 0)
 {
  //buffer
 } 
 Comando_0 = Serial.read() - '0';
 if(Comando_0 != 0)
 {
  goto espera;
 } 
}
/**
 * Llama a los métodos correspondientes para el movimiento hacia adelante, izquierda, derecha y reversa con un tiempo variable tiempo y una velocidad máxima de 255 (2^8-1), con un delay asignado con la variable delayP
 */
void ejecutarMovimientos()
{
 
 avance(tiempo, 255, HIGH, HIGH);
 delay(delayP);
 avance(tiempo, 255, LOW, HIGH);
 delay(delayP);
 avance(tiempo, 255, HIGH,LOW);
 delay(delayP);
 avance(tiempo, 255, LOW,LOW);
 delay(delayP);
}
/**
 * Realiza el movimiento hacia la derecha, hace escritura digital a partir de los pines impuestos como variables m1direction, m2direction con valor izq en m1 y der en m2 como parámetro 
 * Luego escribe analogicamente en los pines de control de velocidad m1speed y m2speed con una velocidad como parametro (pwm)
 * mantiene esa velocidad por una duración puesta como parámetro 
 * escribe en velocidad 0 para detener los motores. 
 */
void avance(int duration, int pwm,int izq, int der)
{
 digitalWrite(m1direction,izq); 
 digitalWrite(m2direction,der); 
 analogWrite(m1speed, pwm); // speed
 analogWrite(m2speed, pwm);
 delay(duration);
 analogWrite(m1speed, 0); // speed
 analogWrite(m2speed, 0);
}
/**
 * Se entiende como izquiero el sensor del lado izquierdo con robot mirando hacia el frente con dirección 7
 * Se entiende como derecho el sensor del lado izquierdo con robot mirando hacia el frente con dirección 8
 * realiza la lectura en cada uno de los pines, calcula el ángulo e imprime en el serial
 */
void leer(int pin)
{
// Solicitar dos bytes del pin por parámetro
  int d1 = 0;
  int d0 = 0;
  Wire.requestFrom(pin, 2);
  while (Wire.available())// slave may send less than requested
  { 
    d0 = Wire.read()-'0';
    d1 = Wire.read()-'0';
    poscicion = d1*10 + d0;
    if (pin == 7)
    {
      Serial.print("Izquierdo: ");
    }
    if (pin == 8)
    {
      Serial.print("Derecho: ");
    }
    Serial.println(poscicion);
  }
}
 
