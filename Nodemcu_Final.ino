/*
Nodemcu Requirements
->Install ESP8266WiFi.h
->Install SoftwareSerial.h
->Install PubSubClient.h

If error arrise, install the following packages
->Install Wire.h
->Install Adafruit_Sensor.h
->Install Adafruit_ADXL345_U.h

Nodemcu Connections
1-Replace the WiFi_AP value with the SSID of the WiFi hotspot
2-Replace the WIFI_PASSWORD with the password of the WiFi hotspot
3-Replace TOKEN value with Access Token of the device from the Thingsboard account 
4-Connect the serial cable to D6 pin of the nodemcu 
ADXL345 Connections
1-Connect Vcc to 3V pin of the nodemcu
2-Connect GND to GND of th nodemcu
3-Connect SCL to D1 of the nodemcu
4-Connect SDA to D2 of the nodemcu
*/

#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

int flag = 0;
#define WIFI_AP "XXXXXXXXXXX"				          //SSID of the WiFi hotspot
#define WIFI_PASSWORD "XXXXXXXXXX"				  //WiFi password

#define TOKEN "FBrnr8e1ce5G8J6Mvw0c"				  //Device Token in Thingsboard

char thingsboardServer[] = "demo.thingsboard.io";

WiFiClient wifiClient;

PubSubClient client(wifiClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;

SoftwareSerial s(D6,D5);				           //Connect serial cable to D6 pin
String payload ="{";

void InitWiFi()
{
  Serial.println("Connecting to AP ...");


  WiFi.begin(WIFI_AP, WIFI_PASSWORD);     //Connecting to Wifi hotspot
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);   //Creating an instance for reading accelerometer data
int ax=1;
int ay=2;
int az=3;
void setup(void) 
{
  s.begin(9600);
  Serial.begin(9600);
  delay(10);
  InitWiFi();
  client.setServer( thingsboardServer, 1883 );      //Connecting to Thingsboard 
  lastSend = 0;
  
  if(!accel.begin())
  {
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}


void reconnect() 
{
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("ESP8266 Device", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
    } 
    else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );
      delay( 5000 );
    }
  }
}

int data[10];
int x=1;
void loop(void) 
{
  

    if ( !client.connected() ) 
    {
      reconnect();
    }
    if (s.available()>0)
    {
      if(x==7)
      {
         Serial.println("*********");
         x=0;
      }
      data[x]=s.read();
      if(x!=0)
      {
        Serial.println(data[x]);
        
      }
      x++;
    }
    
    if(flag==1);
    {
      String payload = "{";
      payload += "\"Pulse\":"; 
      payload += data[1]; 
      payload += ",";
      payload += "\"Temperature\":"; 
      payload += data[2];
      payload += ",";
      payload += "\"Beat\":"; 
      payload += data[3];
      payload += ",";
      payload += "\"Systolic\":"; 
      payload += data[4];
      payload += ",";
      payload += "\"Diastolic\":"; 
      payload += data[5];
      payload += ",";
      payload += "\"Pulse1\":"; 
      payload += data[6];
      payload += "}";
      flag=0;
      char attributes[100];
      payload.toCharArray( attributes, 100 );
      client.publish( "v1/devices/me/telemetry", attributes );      //Publishing data to Thingsboard database
      Serial.println( attributes );
    }
    if(flag==0)
    {
      sensors_event_t event;      //Creating an object to read accelerometer data
      accel.getEvent(&event);
      ax=event.acceleration.x;    //Reading data using objec and specified attributes
      ay=event.acceleration.y;
      az=event.acceleration.z;
      payload = "{";
      payload+= "\"X\":"; 
      payload += ax;
      payload += ",";
      payload += "\"Y\":"; 
      payload += ay;
      payload += ",";
      payload += "\"Z\":"; 
      payload += az;
      
      payload += "}";

      char attributes[100];
      payload.toCharArray( attributes, 100 );
      client.publish( "v1/devices/me/telemetry", attributes );
      Serial.println( attributes );
      flag=1;
    }
      
      lastSend = millis();
   
   client.loop();
  
   
   
}
