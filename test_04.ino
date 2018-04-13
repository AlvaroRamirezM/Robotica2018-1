// Project 40 - Building and Controlling a Tank Robot

#define m2direction 4 // digital pins for direction control 
#define m2speed 5 // digital pins for speed control
#define m1speed 6 // digital pins for speed control  
#define m1direction 7 // digital pins for direction control 
#define TriggerPin 8 // digital pin for trigger
#define EchoPin_1  9 // digital pin for echo Left
#define EchoPin_2  10 // digital pin for echo Diag Left
#define EchoPin_3  11 // digital pin for echo Frente
#define EchoPin_4  12 // digital pin for echo Diag Right
#define EchoPin_5  13 // digital pin for echo Rigth

#define LedPin 13

int lecSens1;
int lecSens2;
int lecSens3;
int lecSens4;
int lecSens5;
void setup()
{
  pinMode(m1direction, OUTPUT);
  pinMode(m2direction, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin_1, INPUT);
  Serial.begin(9600);
  delay(3000);
}
int ping(int TriggerThePin, int echoThePin) {
  long duration, distanceCm;

  digitalWrite(TriggerThePin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerThePin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerThePin, LOW);
  duration = pulseIn(echoThePin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration * 10 / 292 / 2;  //convertimos a distancia, en cm
  //Serial.println(distanceCm);
  return distanceCm;
}
void goForward()
{
  digitalWrite(m1direction, HIGH); // forward
  digitalWrite(m2direction, HIGH); // forward
  analogWrite(m1speed, 105); // speed
  analogWrite(m2speed, 120);
  //delay(200);
}
void goBackward(int duration, int pwm)
{
  digitalWrite(m1direction, LOW); // backward
  digitalWrite(m2direction, LOW); // backward
  analogWrite(m1speed, pwm); // speed
  analogWrite(m2speed, pwm - 50);
  delay(duration);
  analogWrite(m1speed, 0); // speed
  analogWrite(m2speed, 0);
}
void rotateLeft(int duration, int pwm)
{
  digitalWrite(m1direction, HIGH); // forward
  digitalWrite(m2direction, LOW); // backward
  analogWrite(m1speed, 150); // speed
  analogWrite(m2speed, 100);
  delay(duration);
  //analogWrite(m1speed, 0); // speed
  //analogWrite(m2speed, 0);

}
void rotateRight(int duration, int pwm)
{
  digitalWrite(m1direction, LOW); // backward
  digitalWrite(m2direction, HIGH); // forward
  analogWrite(m1speed, 150); // speed
  analogWrite(m2speed, 100);
  delay(duration);
  //analogWrite(m1speed, 0); // speed
  //analogWrite(m2speed, 0);
}

void apagarMotores()
{
  analogWrite(m1speed, 0); // speed
  analogWrite(m2speed, 0);
}

void LecturaSensores()
{
  //lecSens1 = ping(TriggerPin, EchoPin_1);
  lecSens2 = ping(TriggerPin, EchoPin_2);
  lecSens3 = ping(TriggerPin, EchoPin_3);
  lecSens4 = ping(TriggerPin, EchoPin_4);
  //lecSens5 = ping(TriggerPin, EchoPin_5);
}

void loop()
{
  LecturaSensores();
  while (0 < lecSens2 && lecSens2 < 20)
  {
    rotateRight(300, 150);
    lecSens2 = ping(TriggerPin, EchoPin_2);
  }
  while (0 < lecSens4 && lecSens4 < 20)
  {
    rotateLeft(300, 150);
    lecSens4 = ping(TriggerPin, EchoPin_4);
  }
  LecturaSensores();
  while (0 < lecSens3 && lecSens3 < 20)
  {
    if (lecSens2 < lecSens4 && (lecSens4 != 0  || lecSens2 != 0)  )
    {
      rotateRight(300, 200);
      lecSens1 = ping(TriggerPin, EchoPin_1);
      lecSens2 = ping(TriggerPin, EchoPin_2);
      if ((0 < lecSens1 && lecSens1 < 20) || (0 < lecSens2 && lecSens2 < 20))
      {
        rotateRight(300, 200);
      }
    }
    else if (lecSens2 > lecSens4 && (lecSens4 != 0 || lecSens2 != 0) )
    {
      //apagarMotores();
      rotateLeft(300, 200);
      lecSens4 = ping(TriggerPin, EchoPin_4);
      lecSens5 = ping(TriggerPin, EchoPin_5);
      if ((0 < lecSens4 && lecSens4 < 20) || (0 < lecSens5 && lecSens5 < 20))
      {
        rotateLeft(300, 255);
      }
    }
    else
    {
       rotateLeft(300, 200);
    }
    LecturaSensores();
  }
  goForward();
}

