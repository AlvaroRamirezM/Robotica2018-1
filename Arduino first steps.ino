// Project 16 – Creating an LED Binary Number Display
#define DATAIN 6 // digital 6 to pin 14 on the 74HC595
#define LATCHIN 8 // digital 8 to pin 12 on the 74HC595
#define CLOCKIN 10 // digital 10 to pin 11 on the 74HC595

#define DATAOUT 7 // digital 6 to pin 14 on the 74HC595
#define LATCHOUT 9 // digital 8 to pin 12 on the 74HC595
#define CLOCKOUT 11 // digital 10 to pin 11 on the 74HC595

int numeros[8] = {1, 2, 4, 8, 16, 32, 64, 128}; 
byte a1,2;
byte b;
void setup()
{
 Serial.begin(9600);
 pinMode(LATCHIN, INPUT);
 pinMode(CLOCKIN, INPUT);
 pinMode(DATAIN, INPUT);
 
 pinMode(LATCHOUT, OUTPUT);
 pinMode(CLOCKOUT, OUTPUT);
 pinMode(DATAOUT, OUTPUT);
}
void loop()
{
  esperaComandoInicial();
  ejecucionDeMovimientos(); 
}
//---------------
void esperaComandoInicial()
{
  while(Serial.available() == 0)
  {
    //esperar    
  }
}
//---------------
void ejecucionDeMovimientos()
{
  leer();
 //
 escribir();
}
void leer()
{
 digitalWrite(LATCHIN, LOW);
 a1 = shiftIn(DATAIN, CLOCKIN, MSBFIRST);
 a2 = shiftIn(DATAIN, CLOCKIN, MSBFIRST);
 digitalWrite(LATCHIN, HIGH);
 delay(200);
}
void escribir()
{
  int i;
 for ( i = 0; i < 256; i++ )
 {
 digitalWrite(LATCHOUT, LOW);
 shiftOut(DATAOUT, CLOCKOUT, MSBFIRST, b);
 digitalWrite(LATCHOUT, HIGH);
 delay(200);
 }
}