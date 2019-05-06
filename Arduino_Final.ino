
#include <SoftwareSerial.h>
int sensorvalue;
SoftwareSerial s(5, 6);				    //Connect serial out cable to pin 6
SoftwareSerial serial(9, 10);			       //Connect serial Tx-OUT of blood pressure sensor to pin 9
void setup() 
{
  Serial.begin(9600);
  s.begin(9600);
  serial.begin(9600);
  pinMode(A0,INPUT);				      //Connect signal pin of Pulse sensor to A0 pin
  pinMode(A2,INPUT);				      //Connect signal pin of LM35 to A2 pin
  pinMode(A4,INPUT);				      //Connect signal pin of heartbeat sensor to A4 pin
}
float p = 0.0;
float t = 0.0;
float t1 = 0.0;
float b = 0.0;
void loop() 
{
 

  s.write(-1);
  char serialData[30];
  int lf = 10;
  unsigned char read1,read2,read3; 
  serial.listen();
  while(serial.available())
  {
    serial.readBytesUntil(lf,serialData, 15);
  }
  read1 = ((serialData[1]-'0')*100) + ((serialData[2]-'0')*10) +(serialData[3]-'0');
  read2 = ((serialData[6]-'0')*100) + ((serialData[7]-'0')*10) +(serialData[8]-'0');
  read3 = ((serialData[11]-'0')*100) + ((serialData[12]-'0')*10) +(serialData[13]-'0');

  Serial.println(int(read1));
  Serial.println(int(read2));
  Serial.println(int(read3)); 
  Serial.println("*******");
  delay(500);
  
  Serial.println(pulse());
  Serial.println(temp());
  Serial.println(beat());
  s.write(int(read1));
  s.write(int(read2));
  s.write(int(read3));

  Serial.flush();
  serial.flush();  
  
}

float pulse()
{
  delay(20);
  p = analogRead(A0);
  s.write(p);
  return p;
}
float temp()
{
  delay(10);
  t = analogRead(A2);
  t1=(5.0*t*1000.0)/(1024*10);
  s.write(t1);
  return t1;
}
float beat()
{
  
  b = analogRead(A4);
  s.write(b);
  return b;
}
