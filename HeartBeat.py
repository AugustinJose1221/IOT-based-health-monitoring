int x=0;
int y=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
}
void loop() 
{              
  x=analogRead(A0); 
  delay(1000);
  y = map(x ,950 ,1024,72 , 96);
  Serial.print(y);
  Serial.print(" ");
  Serial.println(x);               
}
