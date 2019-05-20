#include <SoftwareSerial.h>     //bluetooth communication library
#include <Wire.h>               //object sensing library
#include <Adafruit_MLX90614.h>  //object sensing library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SoftwareSerial mySerial(2, 3);  // RX, TX
const int GasPin = A0;          // Analog pin for gas sensor input

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.setTimeout(200);

  Serial.println("Hello?");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello?");

  //Serial.println("Adafruit MLX90614 test");  
  mlx.begin(); 

  // Set analog pin A0 to input mode
  pinMode(GasPin, INPUT);
}

void loop() {
  
  // Receive analog data from gas sensor and output to serial monitor
  //analogRead(GasPin);
  if(analogRead(GasPin) > 500){
    int gas = analogRead(GasPin);
    mySerial.println(gas);
    
    Serial.println("*********Dangerous gas detected.*********");
    Serial.println(gas);
    Serial.println();
  }

  // Set the sensing temperature to 28 degrees.
  if(mlx.readObjectTempC() >= 28){
    float tempC = mlx.readObjectTempC();
    mySerial.println(tempC);
    
    Serial.println("*****************Danger*****************");
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = "); Serial.println(tempC); Serial.println("*C");
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
    Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
    Serial.println();
  }

  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  //delay(500);

}