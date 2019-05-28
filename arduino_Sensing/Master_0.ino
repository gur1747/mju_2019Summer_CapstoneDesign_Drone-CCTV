//i2c Master Code(UNO)
#include <SoftwareSerial.h>     //bluetooth communication library
#include <Wire.h>               //object sensing library
#include <Adafruit_MLX90614.h>  //object sensing library

SoftwareSerial mySerial(2, 3);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int GasPin = A0;
int tempC = 0;    // 위험온도가 감지되었음을 알리는 변수
int gas = 0;
int i = 2;

void setup()
{
  Serial.begin(9600);            // 시리얼 통신 시작
  mySerial.begin(9600);
  pinMode(GasPin, INPUT);
  mlx.begin();                   // 열 감지 센싱 시작
  Wire.begin();                 // Master 아두이노와 연결
  //Wire.onRequest(requestEvent);  // Master에 데이터 전달
}

void loop()
{ 
  if(mlx.readObjectTempC() >= 32){
    Serial.println("object");
    mySerial.println(0);
  }
  if(mlx.readObjectTempC() < 32){
    Serial.println("X");
  }

  analogRead(GasPin);
  if(analogRead(GasPin) >= 400){
    Serial.println("gas");
    mySerial.println(1);
  }
  if(analogRead(GasPin) < 400){
    Serial.println("X");
  }

  // 12 바이트 크기의 데이터 요청
  Wire.requestFrom(i, 1); 
  int c = Wire.read(); 
  mySerial.println(c);
  
  Serial.println(c);
  Serial.println("-----------------------------------------------");
  Serial.println();
 
  i++;
  
  if(i==5){
    i=2;
  }

  delay(300);
}