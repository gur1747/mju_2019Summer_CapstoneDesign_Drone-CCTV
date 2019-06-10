#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  
}

void loop() {
  //감지온도는 28도로 설정한다.
  if(mlx.readObjectTempC() >= 28){
    //경고문출력
    Serial.println("Danger");
    //주변온도
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC()); 
    //물체온도
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
  }

  Serial.println();
  delay(1000);
}