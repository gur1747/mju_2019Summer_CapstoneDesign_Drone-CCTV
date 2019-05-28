//i2c Slave Code(Leonardo)
#include <SoftwareSerial.h>     //bluetooth communication library
#include <Wire.h>               //object sensing library
#include <Adafruit_MLX90614.h>  //object sensing library

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int GasPin = A0;
int tempC = 0;    // 위험온도가 감지되었음을 알리는 변수
int gas = 9;
void setup()
{
  Serial.begin(9600);            // 시리얼 통신 시작
  pinMode(GasPin, INPUT);
  mlx.begin();                   // 열 감지 센싱 시작
  Wire.begin(2);                 // Master 아두이노와 연결
  Wire.onRequest(requestEvent);  // Master에 데이터 전달
}

void loop()
{
  //가스센서로부터 아날로그 데이터를 받아와 시리얼 모니터로 출력
  analogRead(GasPin);
  if(analogRead(GasPin) > 400){
    gas = 2;
  }
  else{
    gas = 9;
  }
  
  Serial.println(analogRead(GasPin));
  Serial.println(gas);
  Serial.println();

  //delay(500);

}

void requestEvent()
{
  Wire.write(gas);
  Serial.println("ok");
}