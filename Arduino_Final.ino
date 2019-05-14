/*
Arduino Requirements
1-Connect serial cable to pin 6
->Install SoftwareSerial.h package

Blood Pressure Connections
1-Connect the Vcc and GND to the terminals of a 5v battery
2-Connect Tx-OUT of the blood pressure sensor to pin 9

Pulse Sensor Connections
1-Connect Vcc to 3.3v of the Arduino
2-Connect GND to GND of the Arduino
3-Connect the signal pin to A0 of the Arduino

LM35 Connections
1-Connect Vcc to 5v of the Arduino
2-Connect GND to GND of the Arduino
3-Connect the signal pin to A2 of the Arduino

Heartbeat Sensor Connections
1-Connect Vcc to 3.3v of the Arduino
2-Connect GND to GND of the Arduino
3-Connect the signal pin to A4 of the Arduino
*/

#include <SoftwareSerial.h>
int sensorvalue;
SoftwareSerial s(5, 6);				    //Connect serial out cable to pin 6
SoftwareSerial serial(9, 10);			    //Connect Tx-OUT of blood pressure sensor to pin 9
void setup() 
{
  Serial.begin(9600);
  s.begin(9600);
  serial.begin(9600);
  pinMode(A0,INPUT);				    //Connect signal pin of Pulse sensor to A0 pin
  pinMode(A2,INPUT);				    //Connect signal pin of LM35 to A2 pin
  pinMode(A4,INPUT);				    //Connect signal pin of heartbeat sensor to A4 pin
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
  /*
  Reading data from Blood Pressure Sensor.The data is send serially as ASCII values.The first bit is a start bit 
  and the last bit is a stop bit.The sensor data consist of Systolic pressure, Diastolic pressure and the pulse of the patient.
  Each data is represented by three ASCII characters of which the first character is the MSB and the last character is the LSB.
  */
  read1 = ((serialData[1]-'0')*100) + ((serialData[2]-'0')*10) +(serialData[3]-'0');    //The 2nd,3rd and 4th ASCII characters corresponds to the Systolic pressure
  read2 = ((serialData[6]-'0')*100) + ((serialData[7]-'0')*10) +(serialData[8]-'0');    //The 7th,8th and 9th ASCII characters corresponds to the Diastolic pressure 
  read3 = ((serialData[11]-'0')*100) + ((serialData[12]-'0')*10) +(serialData[13]-'0'); //The 12th,13th and 14th ASCII character corresponds to the pulse

  Serial.println(int(read1));
  Serial.println(int(read2));
  Serial.println(int(read3)); 
  Serial.println("*******");
  delay(500);
  
  Serial.println(pulse());
  Serial.println(temp());
  Serial.println(beat());
  s.write(int(read1));      //Sending data serially to Nodemcu
  s.write(int(read2));
  s.write(int(read3));

  Serial.flush();
  serial.flush();  
  
}

float pulse()       //Function to read pulse from the pulse sensor 
{
  delay(20);
  p = analogRead(A0);
  s.write(p);
  return p;
}
float temp()        //Function to read temperature from the LM35 sensor
{
  delay(10);
  t = analogRead(A2);
  t1=(5.0*t*1000.0)/(1024*10);    //Conversion factor to convert the analog values to Celcuis scale
  s.write(t1);
  return t1;
}
float beat()        //Function to read heart beats from beat sensor
{
  
  b = analogRead(A4);
  s.write(b);
  return b;
}
