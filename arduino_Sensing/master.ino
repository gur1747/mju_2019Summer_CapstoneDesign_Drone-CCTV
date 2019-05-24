//i2c Master Code(UNO)
#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{  
  Wire.requestFrom(5, 1);
  
  int tempC = Wire.read();
  Serial.println(tempC); 
  /*
  while(Wire.available())
  {
    int tempC = Wire.read();
    Serial.println(tempC);
  }
  */
  delay(500);
}