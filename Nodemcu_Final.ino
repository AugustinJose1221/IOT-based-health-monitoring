#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

int flag = 0;
#define WIFI_AP "LAPTOP-KDHU81SC 9862"
#define WIFI_PASSWORD "99999999"

#define TOKEN "FBrnr8e1ce5G8J6Mvw0c"

char thingsboardServer[] = "demo.thingsboard.io";

WiFiClient wifiClient;

PubSubClient client(wifiClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;

SoftwareSerial s(D6,D5);
String payload ="{";

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
int ax=1;
int ay=2;
int az=3;
void setup(void) 
{
  s.begin(9600);
  Serial.begin(9600);
  delay(10);
  InitWiFi();
  client.setServer( thingsboardServer, 1883 );
  lastSend = 0;
  
  if(!accel.begin())
  {
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}


void reconnect() 
{
  // Loop until we're reconnected
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
      // Wait 5 seconds before retrying
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
    
    //if ( millis() - lastSend > 1000 ) 
    //{ // Update and send only after 1 seconds
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
      client.publish( "v1/devices/me/telemetry", attributes );
      Serial.println( attributes );
    }
    if(flag==0)
    {
      sensors_event_t event; 
      accel.getEvent(&event);
      ax=event.acceleration.x;
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
   
  //}
   client.loop();
  
   
   
}
