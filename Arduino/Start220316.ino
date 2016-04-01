#include "IRremote.h"
#include <extEEPROM.h> 
#include <TimerOne.h>
#include <SoftwareSerial.h>
extEEPROM eep(kbits_4, 1, 16,0x50); //For 24c02 extEEPROM eep(kbits_2, 1, 8,0x50);For 24c04 extEEPROM eep(kbits_4, 1, 16,0x50);
SoftwareSerial esp8266(9,12);
int receiver = 11;
char c;
volatile int i=0;
volatile boolean zero_cross=0;
int dim = 128;
//int dim2 = 0;
int pas = 8;
int freqStep = 75; 
int on1;
int on2;
int on3;
int on4;
int on5;
int on6;
int on7;
int on8;
int Relay1 =8;
int Relay2 =7;
int Relay3 =3;
int Relay4 =4;
int Relay5 =20;
int Relay6 =21;
int Relay7 =5;
int Relay8 =6;
int AC_pin = 10;
int cpuled = 13;
IRrecv irrecv(receiver);            
decode_results results; 
void setup() {
  // put your setup code here, to run once:

pinMode(Relay1, OUTPUT);
pinMode(Relay2, OUTPUT);
pinMode(Relay3, OUTPUT);
pinMode(Relay4, OUTPUT);
pinMode(Relay5, OUTPUT);
pinMode(Relay6, OUTPUT);
pinMode(Relay7, OUTPUT);
pinMode(Relay8, OUTPUT);
pinMode(AC_pin, OUTPUT);
pinMode(cpuled, OUTPUT);
attachInterrupt(0, zero_cross_detect, RISING);
Timer1.initialize(freqStep);
Timer1.attachInterrupt(dim_check, freqStep);
irrecv.enableIRIn(); 
esp8266.begin(9600);
delay(500);

eep.begin(twiClock400kHz);
on1 = eep.read(1);
digitalWrite(Relay1, on1 ? HIGH : LOW);
if (on1==1)
{
  esp8266.print("A");
}
on2 = eep.read(2);
digitalWrite(Relay2, on2 ? HIGH : LOW);
if (on2==1)
{
  esp8266.print("B");
}
on3 = eep.read(3);
digitalWrite(Relay3, on3 ? HIGH : LOW);
if (on3==1)
{
  esp8266.print("C");
}
on4 = eep.read(4);
digitalWrite(Relay4, on4 ? HIGH : LOW);
if (on4==1)
{
  esp8266.print("D");
}
on5 = eep.read(5);
digitalWrite(Relay5, on5 ? HIGH : LOW);
if (on5==1)
{
  esp8266.print("E");
}
on6 = eep.read(6);
digitalWrite(Relay6, on6 ? HIGH : LOW);
if (on6==1)
{
  esp8266.print("F");
}
on7 = eep.read(7);
digitalWrite(Relay7, on7 ? HIGH : LOW);
if (on7==1)
{
  esp8266.print("G");
}
on8 = eep.read(8);
digitalWrite(Relay8, on8 ? HIGH : LOW);
if (on8==1)
{
  esp8266.print("H");
}
dim = eep.read(9);

delay(100);
}

void zero_cross_detect() {
zero_cross = true;
digitalWrite(AC_pin, LOW);  
}
void dim_check() { 
 if(zero_cross == true) { 
  if(i>=dim) {
    digitalWrite(AC_pin, HIGH);
    i=0;
    zero_cross=false;
    }
    else {
      i++;
  }
 }
}

void loop() {
  // put your main code here, to run repeatedly:
 
   if (irrecv.decode(&results)) 
  {
    translateIR(); 
    irrecv.resume(); 
  } 
  if(esp8266.available())
  {
    //while(esp8266.available())
    //{
       c = esp8266.read();
     // Serial.write(c);
      translateWIFI();
   // }
  }

  digitalWrite(cpuled, HIGH);
delay(100);
digitalWrite(cpuled, LOW);
delay(100);
  
}

void translateWIFI()
{
  switch(c)
  {
    case 'A':  
         on1 = !on1;
         digitalWrite(Relay1, on1 ? HIGH : LOW);
         eep.write(1, on1); 
         delay(100);
       break;
       case 'B':  
         on2 = !on2;
         digitalWrite(Relay2, on2 ? HIGH : LOW);
         eep.write(2, on2);
         delay(100);
       break;
       
 case 'C':  
         on3 = !on3;
         digitalWrite(Relay3, on3 ? HIGH : LOW);
         eep.write(3, on3); 
         delay(100);
       break;
       
 case 'D':  
         on4 = !on4;
         digitalWrite(Relay4, on4 ? HIGH : LOW);
         eep.write(4, on4);
         delay(100);
       break;   
       
 case 'E':  
         on5 = !on5;
         digitalWrite(Relay5, on5 ? HIGH : LOW);
         eep.write(5, on5);
         delay(100);
       break; 

 case 'F':  
         on6 = !on6;
         digitalWrite(Relay6, on6 ? HIGH : LOW);
         eep.write(6, on6); 
         delay(100);
       break; 

 case 'G':  
         on7 = !on7;
         digitalWrite(Relay7, on7 ? HIGH : LOW);
         eep.write(7, on7); 
         delay(100);
       break; 
       
 case 'H':  
         on8 = !on8;
         digitalWrite(Relay8, on8 ? HIGH : LOW);
         eep.write(8, on8); 
         delay(100);
       break;

case 'N':  
   if(on2==1){      
  if (dim<127)  
  {
    dim = dim + pas;
    if (dim>127) 
    {
      dim=128;
    }
  }
  eep.write(9, dim);
   }
   delay(100);
    break;

case 'U':
if(on2==1) {
    if (dim>5)  
  {
     dim = dim - pas;
  if (dim<0) 
    {
      dim=0;
    }
   }
   eep.write(9, dim);
}
   delay(100);
   break;

    
 case 'I':  
         on1 = 0;
         on2 = 0;
         on3 = 0;
         on4 = 0;
         on5 = 0;
         on6 = 0;
         on7 = 0;
         on8 = 0;
         digitalWrite(Relay1, LOW);
         eep.write(1, on1);
         digitalWrite(Relay2, LOW);
         eep.write(2, on2);
         digitalWrite(Relay3, LOW);
         eep.write(3, on3);
         digitalWrite(Relay4, LOW);
         eep.write(4, on4);
         digitalWrite(Relay5, LOW);
         eep.write(5, on5);
         digitalWrite(Relay6, LOW);
         eep.write(6, on6);
         digitalWrite(Relay7, LOW);
         eep.write(7, on7);
         digitalWrite(Relay8, LOW);
         eep.write(8, on8);
         delay(100);
       break;   
       
    
  }
  
}


void translateIR() 


{

  switch(results.value)

  {

  case 0xE0E020DF:  
         on1 = !on1;
         digitalWrite(Relay1, on1 ? HIGH : LOW);
         eep.write(1, on1); 
         esp8266.print("A");
         delay(100);
       break;
       
 case 0xE0E0A05F:  
         on2 = !on2;
         digitalWrite(Relay2, on2 ? HIGH : LOW);
         eep.write(2, on2);
         esp8266.print("B");
         delay(100);
       break;
       
 case 0xE0E0609F:  
         on3 = !on3;
         digitalWrite(Relay3, on3 ? HIGH : LOW);
         eep.write(3, on3); 
         esp8266.print("C");
         delay(100);
       break;
       
 case 0xE0E010EF:  
         on4 = !on4;
         digitalWrite(Relay4, on4 ? HIGH : LOW);
         eep.write(4, on4);
         esp8266.print("D");
         delay(100);
       break;   
       
 case 0xE0E0906F:  
         on5 = !on5;
         digitalWrite(Relay5, on5 ? HIGH : LOW);
         eep.write(5, on5);
         esp8266.print("E");
         delay(100);
       break; 

 case 0xE0E050AF:  
         on6 = !on6;
         digitalWrite(Relay6, on6 ? HIGH : LOW);
         eep.write(6, on6);
         esp8266.print("F"); 
         delay(100);
       break; 

 case 0xE0E030CF:  
         on7 = !on7;
         digitalWrite(Relay7, on7 ? HIGH : LOW);
         eep.write(7, on7); 
         esp8266.print("G");
         delay(100);
       break; 
       
 case 0xE0E0B04F:  
         on8 = !on8;
         digitalWrite(Relay8, on8 ? HIGH : LOW);
         eep.write(8, on8);
         esp8266.print("H");
         delay(100);
       break;
       
        
case 0xE0E0D02F:  
   if(on2==1){      
  if (dim<127)  
  {
    dim = dim + pas;
    if (dim>127) 
    {
      dim=128;
    }
  }
  eep.write(9, dim);
  esp8266.print("N");
   }
   delay(100);
    break;

    case 0xE0E0E01F:
if(on2==1) {
    if (dim>5)  
  {
     dim = dim - pas;
  if (dim<0) 
    {
      dim=0;
    }
   }
   eep.write(9, dim);
   esp8266.print("U");
}
   delay(100);
   break;
          
       
 case 0xE0E040BF:  
         on1 = 0;
         on2 = 0;
         on3 = 0;
         on4 = 0;
         on5 = 0;
         on6 = 0;
         on7 = 0;
         on8 = 0;
         digitalWrite(Relay1, LOW);
         eep.write(1, on1);
         digitalWrite(Relay2, LOW);
         eep.write(2, on2);
         digitalWrite(Relay3, LOW);
         eep.write(3, on3);
         digitalWrite(Relay4, LOW);
         eep.write(4, on4);
         digitalWrite(Relay5, LOW);
         eep.write(5, on5);
         digitalWrite(Relay6, LOW);
         eep.write(6, on6);
         digitalWrite(Relay7, LOW);
         eep.write(7, on7);
         digitalWrite(Relay8, LOW);
         eep.write(8, on8);
         esp8266.print("I");
         delay(100);
       break;   

default:
break;    
  }
  delay (100);
  }
