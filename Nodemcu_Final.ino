#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#define WIFI_AP "XXXXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXXX"

#define TOKEN "XXXXXXXXXXXXXXX"

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

void setup() 
{
  s.begin(9600);
  Serial.begin(9600);
  delay(10);
  InitWiFi();
  client.setServer( thingsboardServer, 1883 );
  lastSend = 0;
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
void loop() 
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
    if ( millis() - lastSend > 1000 ) 
  { // Update and send only after 1 seconds
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

      char attributes[100];
      payload.toCharArray( attributes, 100 );
      client.publish( "v1/devices/me/telemetry", attributes );
      Serial.println( attributes );

      }
    lastSend = millis();
   
  }
   client.loop();
   
}



