#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define WIFI_SSID "XXXXXXXXX"
#define WIFI_PASSWORD "XXXXXXXXX"

#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "XXXXXXXXXXXXXXXX"

int x =0;
void setup() 
{
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(A0, INPUT);
}
void loop()
{
  x =analogRead(A0);
  Firebase.pushString("/Pulse",String(x));
  Serial.println(x);
}
