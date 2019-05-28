//가스센서 입력을 위한 아날로그 핀
const int GasPin = A0;

void setup() {
  //아날로그 핀 A0를 입력모드로 설정
  pinMode(GasPin, INPUT);
  //시리얼통신 시작
  Serial.begin(9600);
}
 
void loop() {
  //가스센서로부터 아날로그 데이터를 받아와 시리얼 모니터로 출력
  analogRead(GasPin);
  if(analogRead(GasPin) > 500){
    //Serial.print(analogRead(GasPin));
    Serial.println("위험가스가 감지되었습니다.");
  }
  delay(1000);
} 

