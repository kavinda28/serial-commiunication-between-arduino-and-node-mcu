#include <SoftwareSerial.h>

SoftwareSerial nodemcu(3,2);


int sdata1 = 0; // sensor1 data
int sdata2 = 0; // sensor2 data
int sdata3 = 0; // sensor3 data
int sdata4 = 0;

String cdata; // complete data, consisting of sensors values

void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);

}

void loop()
{
  
    sdata1 = 100;
    sdata2 = 200;
    sdata3 = 400;
      sdata4 = 500;
    
   cdata = cdata + sdata1+","+sdata2+","+sdata3+","+sdata4; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(100); // 100 milli seconds
   cdata = ""; 

}
