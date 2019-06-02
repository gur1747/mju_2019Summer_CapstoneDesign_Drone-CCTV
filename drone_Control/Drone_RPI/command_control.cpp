#include "_00_drone.h"
#include <stdio.h>      //이하 헤더 4개는 kbhit 함수를 위함
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

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
target_angle_t target_angle = { .roll = 0.0, .pitch = 1.0, .yaw = 10.0,};//7
balancing_force_t balancing_force;//7
throttle_t throttle = { .value = 0, };//8
motor_speed_t motor_speed;//8
hm10_t hm10;//9
motor_t motor = { .a = 0, .b = 2, .c = 1, .d = 3, };//10
pca9685_t pca9685 = { .i2c_addr = 0x40, };//10

int kbhit(void);

int main() {

        wiringPiSetup();//1
        init(i2c);//1  //i2c 포트 개방
        init(i2c, mpu6050);//1 //자이로센서 초기화
        get(mpu6050, gyro_offset);//2  //자이로 값 평균 구하기 위해 합을 구하는 곳(1000번 측정값 더함)
        init(dt);//5 //시간 주기 구하기
        init(hm10);//9 //블루투스 모듈 쪽 초기화
        init(i2c, pca9685);//10  //모터 초기화

        //throttle.value = 140;
        char c;
        bool exit = false;
        while( true ) {
                if  ( kbhit() ){
                  c = getchar();
                  if(c == 'w'){
                    throttle.value += 5;
                  }else if(c == 's'){
                    throttle.value -= 5;
                  }else if(c == 'a'){
                    target_angle.yaw += 3;
                  }else if(c == 'd'){
                    target_angle.yaw -= 3;
                  }else if(c == 'i'){
                    target_angle.pitch -= 3;
                  }else if(c == 'k'){
                    target_angle.pitch += 3;
                  }else if(c == 'j'){
                    target_angle.roll -= 3;
                  }else if(c == 'l'){
                    target_angle.roll += 3;
                  }else if ( c == ' ' ){
                    throttle.value = 0;
                    exit = true;
                  }
                }
                read(mpu6050, gyro_raw);//1 //원시 자이로 값 읽기
                calc(gyro_adj, gyro_raw, gyro_offset);//3 //원시 자이로 편차 평균 구하기
                calc(gyro_rate, gyro_adj);//4 //회전 각속도 계산
                calc(dt);//5  //시간 주기 측정
                calc(gyro_angle, gyro_rate, dt);//6 //회전각 구하기
                calc(balancing_force, target_angle, gyro_angle);//7 //드론균형 보정값 구하기
                add(balancing_force, gyro_rate);//11  //보정값 추가 보정
                add(balancing_force, target_angle, gyro_angle, dt);//12 //추가 보정
                distribute(motor_speed, throttle, balancing_force);//8  //모터 속도 도출
                //check(hm10, throttle, target_angle);//9         //명령 수신 확인
                update(pca9685, motor, motor_speed);//10  //도출 된 모터 속도 적용

                if ( exit ){
                  return 0;
                }
                static int cnt_loop;//1
                cnt_loop++;//1
                if( cnt_loop%300 != 0) continue;//1

                //print(gyro_raw);//1
                //print(gyro_offset);//2
                //print(gyro_adj);//3
                //print(gyro_rate);//4
                //print(dt);//5
                //print(gyro_angle);//6
                //print(balancing_force);//7
                //print(motor_speed);//8
                //println();//1

        }
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
