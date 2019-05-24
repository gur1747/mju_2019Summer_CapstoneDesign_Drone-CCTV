//i2c Slave Code(Leonardo)
#include <SoftwareSerial.h>     //bluetooth communication library
#include <Wire.h>               //object sensing library
#include <Adafruit_MLX90614.h>  //object sensing library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int tempC = 0;

void setup()
{
  Serial.begin(9600);
  mlx.begin();
  Wire.begin(5); 
  Wire.onRequest(requestEvent);
}

void loop()
{
  //Serial.println(mlx.readObjectTempC());
  // Set the sensing temperature to 28 degrees.
  if(mlx.readObjectTempC() >= 30){
    //Wire.onRequest(requestEvent);
    tempC = 1;
  }
  else{
    tempC = 0;
  }
  
  Serial.println(mlx.readObjectTempC());
  Serial.println(tempC);
  
  delay(500);
}

void requestEvent()
{
  //Wire.beginTransmission(5);
  Wire.write(tempC);
  //Wire.endTransmission(); 
}