#include "_00_drone.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8088

i2c_t i2c;//1
mpu6050_t mpu6050 = {
        .i2c_addr = 0x68,
        .PWR_MGMT_1 = 0x6b,
        .GYRO_XOUT_H = 0x43,
};//1
gyro_raw_t gyro_raw;//1
gyro_offset_t gyro_offset;//2
gyro_adj_t gyro_adj;//3
gyro_rate_t gyro_rate;//4
dt_t dt;//5
gyro_angle_t gyro_angle;//6
target_angle_t target_angle;//7
balancing_force_t balancing_force;//7
throttle_t throttle = { .value = 0, };//8
motor_speed_t motor_speed;//8
hm10_t hm10;//9
motor_t motor = { .a = 0, .b = 2, .c = 1, .d = 3, };//10
pca9685_t pca9685 = { .i2c_addr = 0x40, };//10

void myfunc();
int kbhit(void);
void command();

int main() {

        //1. 초기화 단계
        wiringPiSetup();//1
        init(i2c);//1  //i2c 포트 개방
        init(i2c, mpu6050);//1 //자이로센서 초기화
        get(mpu6050, gyro_offset);//2  //자이로 값 평균 구하기 위해 합을 구하는 곳
        init(dt);//5 //시간 주기 구하기
        init(hm10);//9 //블루투스 모듈 쪽 초기화
        init(i2c, pca9685);//10  //모터 초기화


        //2. 라즈베리파이 3b+ 메인기판 명령 수신 대기
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                printf("\n Socket creation error \n");
                return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);
        if(inet_pton(AF_INET, "192.168.43.151", &serv_addr.sin_addr)<=0)
        {
                printf("\nInvalid address/ Address not supported \n");
                return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
                printf("\nConnection Failed \n");
                return -1;
        }
        //메시지 수신 대기
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );


        //3. 경로 주행
        int i, j, k, l;
        if(atoi[buffer] == 1){

          for(i = 0; i <= 160; i++){
                  command();
                  throttle.value = i;
                  myfunc();
                  delay(10);
          }
          //t -> 160
          for(j = 0 ; j < 30; j++){
                  command();
                  throttle.value -= 1;
                  myfunc();
                  delay(10);
          }
          target_angle.pitch = 2;
          //t -> 130
          for(k = 0; k < 150; k++){
                  command();
                  myfunc();
                  delay(10);
          }
          //t -> 130
          target_angle.pitch = 0;
          for(l = 0; l < 26; l++){
                  command();
                  throttle.value -= 5;
                  myfunc();
                  delay(10);
          }
          throttle.value = 0;
        }else if(atoi[buffer] == 2){

          for(i = 0; i <= 160; i++){
                  command();
                  throttle.value = i;
                  myfunc();
                  delay(10);
          }
          //t -> 160
          for(j = 0 ; j < 30; j++){
                  command();
                  throttle.value -= 1;
                  myfunc();
                  delay(10);
          }
          target_angle.pitch = 5;
          //t -> 130
          for(k = 0; k < 300; k++){
                  command();
                  myfunc();
                  delay(10);
          }
          target_angle.pitch = 0;
          //t -> 130
          for(l = 0; l < 26; l++){
                  command();
                  throttle.value -= 5;
                  myfunc();
                  delay(10);
          }
          throttle.value = 0;
        }else if(atoi[buffer] == 3){

          for(i = 0; i <= 160; i++){
                  command();
                  throttle.value = i;
                  myfunc();
                  delay(10);
          }
          //t -> 160
          target_angle.pitch = 2;
          for(j = 0 ; j < 30; j++){
                  command();
                  throttle.value -= 1;
                  myfunc();
                  delay(10);
          }
          target_angle.pitch = 0;
          target_angle.roll = 5;
          //t -> 130
          for(k = 0; k < 150; k++){
                  command();
                  myfunc();
                  delay(10);
          }
          target_angle.roll = 0;
          //t -> 130
          for(l = 0; l < 26; l++){
                  command();
                  throttle.value -= 5;
                  myfunc();
                  delay(10);
          }
          throttle.value = 0;
        }else if(atoi[buffer] == 4){
          for(i = 0; i <= 160; i++){
                  command();
                  throttle.value = i;
                  myfunc();
                  delay(10);
          }
          //t -> 160
          target_angle.pitch = 2;
          for(j = 0 ; j < 30; j++){
                  command();
                  throttle.value -= 1;
                  myfunc();
                  delay(10);
          }
          target_angle.pitch = 0;
          //t -> 130
          for(k = 0; k < 150; k++){
                  command();
                  myfunc();
                  delay(10);
          }
          //t -> 130
          for(l = 0; l < 26; l++){
                  command();
                  throttle.value -= 5;
                  myfunc();
                  delay(10);
          }
          throttle.value = 0;
          }
        return 0;
}

void myfunc(){    //모터 속도 업데이트 루틴

        read(mpu6050, gyro_raw);//1 //원시 자이로 값 읽기
        calc(gyro_adj, gyro_raw, gyro_offset);//3 //원시 자이로 편차 평균 구하기
        calc(gyro_rate, gyro_adj);//4 //회전 각속도 계산
        calc(dt);//5  //시간 주기 측정
        calc(gyro_angle, gyro_rate, dt);//6 //회전각 구하기
        calc(balancing_force, target_angle, gyro_angle);//7 //드론균형 보정값 구하기
        add(balancing_force, gyro_rate);//11  //보정값 추가 보정
        add(balancing_force, target_angle, gyro_angle, dt);//12 //추가 보정
        distribute(motor_speed, throttle, balancing_force);//8  //모터 속도 도출
        update(pca9685, motor, motor_speed);//10  //도출 된 모터 속도 적용
}

int kbhit(void){    //키보드 입력감지 함수 -> 감지 된 문자를 저장해둠

        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if(EOF != ch) {
                ungetc(ch, stdin);
                return 1;
        }
        return 0;
}

void command(){   //경로 주행 간 보정 오차값을 키 입력을 통해 추가 보정
        char c;
        if(kbhit()){
                c = getchar();
                if(c == 'w'){
                        target_angle.pitch -= 2;
                }else if(c == 's'){
                        target_angle.pitch += 2;
                }else if(c == 'a'){
                        target_angle.roll -= 2;
                }else if(c == 'd'){
                        target_angle.roll += 2;
                }
        }
}
