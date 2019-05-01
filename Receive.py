#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
int data;
void setup() 
{
s.begin(9600);
Serial.begin(9600);
}
int x=1;
void loop() 
{
  //s.write("s");
  if (s.available()>0)
  {
    if(x%7==1)
    {
      data=s.read();
      Serial.println(data);
    }
    if(x%7==2)
    {
      data=s.read();
      Serial.println(data);
    }
    if(x%7==3)
    {
      data=s.read();
      Serial.println(data);
    }
    if(x%7==4)
    {
      data=s.read();
      Serial.println(data);
    }
    if(x%7==5)
    {
      data=s.read();
      Serial.println(data);
    }
    if(x%7==6)
    {
      data=s.read();
      Serial.println(data);
    }
    if(x%7==0)
    {
      Serial.println("**********");
      x=1;
    }
    x++;
  }
  
 
}
