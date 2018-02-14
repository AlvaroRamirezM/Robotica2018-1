// Project 40 - Building and Controlling a Tank Robot

#include <Wire.h>

int m1speed=6; // digital pins for speed control
int m2speed=5;
int m1direction=7; // digital pins for direction control
int m2direction=4;
int tiempo = 250;
int delayP = 1000;
int Comando_0;
int poscicionIzquierdo = 0;
int poscicionDerecho = 0;
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
  leerIzquierdo();
  leerDerecho();
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
  goForward(tiempo, 255);
 delay(delayP);
 rotateLeft(tiempo, 255);
 delay(delayP);
 rotateRight(tiempo, 255);
 delay(delayP);
 goBackward(tiempo, 255);
 delay(delayP);
}
/**
 * Realiza el movimiento hacia adelante, hace escritura digital a partir de los pines impuestos como variables m1direction, m2direction con valor High (forward)
 * Luego escribe analogicamente en los pines de control de velocidad m1speed y m2speed con una velocidad como parametro (pwm)
 * mantiene esa velocidad por una duración puesta como parámetro 
 * escribe en velocidad 0 para detener los motores. 
 */
void goForward(int duration, int pwm)
{
 digitalWrite(m1direction,HIGH); // forward
 digitalWrite(m2direction,HIGH); // forward
 analogWrite(m1speed, pwm); // speed
 analogWrite(m2speed, pwm);
 delay(duration);
 analogWrite(m1speed, 0); // speed
 analogWrite(m2speed, 0);
}
/**
 * Realiza el movimiento hacia adelante, hace escritura digital a partir de los pines impuestos como variables m1direction, m2direction con valor LOW (backward)
 * Luego escribe analogicamente en los pines de control de velocidad m1speed y m2speed con una velocidad como parametro (pwm)
 * mantiene esa velocidad por una duración puesta como parámetro 
 * escribe en velocidad 0 para detener los motores. 
 */
void goBackward(int duration, int pwm)
{
 digitalWrite(m1direction,LOW); // backward
 digitalWrite(m2direction,LOW); // backward
 analogWrite(m1speed, pwm); // speed
 analogWrite(m2speed, pwm);
 delay(duration);
 analogWrite(m1speed, 0); // speed
 analogWrite(m2speed, 0);
}
/**
 * Realiza el movimiento hacia la derecha, hace escritura digital a partir de los pines impuestos como variables m1direction, m2direction con valor HIGH en m1 y LOW en m2 (forward)
 * Luego escribe analogicamente en los pines de control de velocidad m1speed y m2speed con una velocidad como parametro (pwm)
 * mantiene esa velocidad por una duración puesta como parámetro 
 * escribe en velocidad 0 para detener los motores. 
 */
void rotateRight(int duration, int pwm)
{
 digitalWrite(m1direction,HIGH); // forward
 digitalWrite(m2direction,LOW); // backward
 analogWrite(m1speed, pwm); // speed
 analogWrite(m2speed, pwm);
 delay(duration);
 analogWrite(m1speed, 0); // speed
 analogWrite(m2speed, 0);
}
/**
 * Realiza el movimiento hacia la derecha, hace escritura digital a partir de los pines impuestos como variables m1direction, m2direction con valor LOW en m1 y HIGH en m2 (forward)
 * Luego escribe analogicamente en los pines de control de velocidad m1speed y m2speed con una velocidad como parametro (pwm)
 * mantiene esa velocidad por una duración puesta como parámetro 
 * escribe en velocidad 0 para detener los motores. 
 */
void rotateLeft(int duration, int pwm)
{
 digitalWrite(m1direction,LOW); // backward
 digitalWrite(m2direction,HIGH); // forward
 analogWrite(m1speed, pwm); // speed
 analogWrite(m2speed, pwm);
 delay(duration);
 
 analogWrite(m1speed, 0); // speed
 analogWrite(m2speed, 0);
}
/**
 * Se entiende como izquiero el sensor del lado izquierdo con robot mirando hacia el frente
 * Tiene direccion 7
 * realiza la lectura en cada uno de los pines, calcula el ángulo e imprime en el serial
 */
 void leerIzquierdo()
 {
  // Solicitar dos bytes de 7
  int d1 = 0;
  int d0 = 0;
  Wire.requestFrom(7, 2);
  while (Wire.available())// slave may send less than requested
  { 
    d0 = Wire.read()-'0';
    d1 = Wire.read()-'0';
    poscicionIzquierdo = d1*10 + d0;
    Serial.print("Izquierdo: ");
    Serial.println(poscicionIzquierdo);
  }  
 }
 /**
 * Se entiende como derecho el sensor del lado izquierdo con robot mirando hacia el frente
 * Tiene direccion 8
 * realiza la lectura en cada uno de los pines, calcula el ángulo e imprime en el serial
 */
 void leerDerecho()
 {
  // Solicitar dos bytes de 8
  int d1 = 0;
  int d0 = 0;
  Wire.requestFrom(8, 2);
  while (Wire.available())// slave may send less than requested
  { 
    d0 = Wire.read()-'0';
    d1 = Wire.read()-'0';
    poscicionDerecho = d1*10 + d0;
    Serial.print("Derecho: ");
    Serial.println(poscicionDerecho);
  }
 }

