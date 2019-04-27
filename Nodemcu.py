#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "XXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXXXX"

#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "XXXXXXXXXXXXX"

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

SoftwareSerial s(D6,D5);

int accelX=0;
int accelY=0;
int accelZ=0;
int data = 0;
void setup()
{
  Serial.begin(9600);
  Wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");//To be deleted from real program
  while(WiFi.status() != WL_CONNECTED) //To be deleted
  {
     Serial.print(".");
     delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  if(!accel.begin())
  {
     while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  s.begin(9600);
}

void loop()
{
  sensors_event_t event;
  accel.getEvent(&event);
  accelX = event.acceleration.x;
  accelY = event.acceleration.y;
  accelZ = event.acceleration.z;

  if(s.available()>0)
  {
     data = s.read();
  }
  Firebase.pushString("/Accelerometer/X_axis",String(accelX));
  Firebase.pushString("/Accelerometer/Y_axis",String(accelY));
  Firebase.pushString("/Accelerometer/Z_axis",String(accelZ));
  Firebase.pushString("/Sensor",String(data));//Need to be segregated
}


  
