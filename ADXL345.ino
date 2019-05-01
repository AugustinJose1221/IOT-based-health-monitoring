#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup(void) 
{
  Serial.begin(9600);
  if(!accel.begin())
  {
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop(void) 
{

  sensors_event_t event; 
  accel.getEvent(&event);

  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");

}
