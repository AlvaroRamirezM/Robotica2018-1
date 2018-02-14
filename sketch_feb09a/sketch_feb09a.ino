// Project 40 - Building and Controlling a Tank Robot
int m1speed=6; // digital pins for speed control
int m2speed=5;
int m1direction=7; // digital pins for direction control
int m2direction=4;
int tiempo = 250;
int delayP = 1000;
int Letra;
void setup()
{
 pinMode(m1direction, OUTPUT);
 pinMode(m2direction, OUTPUT);
 Serial.begin(9600);
 delay(5000);
}
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
void loop()
{
  esperarComando();
  ejecutarMovimientos();
}
void esperarComando()
{
  espera:
  Serial.flush();
 while (Serial.available() == 0)
 {
  //buffer
 } 
 Letra = Serial.read() - '0';
 if(Letra != 0)
 {
  goto espera;
 } 
}
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


