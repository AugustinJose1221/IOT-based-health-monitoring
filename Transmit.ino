#include <SoftwareSerial.h>
SoftwareSerial s(5,6);
void setup() 
{
  s.begin(9600);
  Serial.begin(9600);
}
 void loop() 
{
  int data=50;
  s.write(data);
  Serial.print("True");
}
