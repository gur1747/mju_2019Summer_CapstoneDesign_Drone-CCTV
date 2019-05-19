#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(){
        wiringPiSetup();

        int serial_port;
        if((serial_port = serialOpen("/dev/ttyS0", 115200)) < 0){
                fprintf(stderr, "Unable to open serial device : %s\n", strerror(errno));
                return 1;
        }

        while(1){
                static int cnt_msg;


                if(serialDataAvail(serial_port)){
                        while(serialDataAvail(serial_port)){
                                char dat = serialGetchar(serial_port);
                                if(dat == '$'){
                                        cnt_msg = 0;
                                }else{
                                        cnt_msg++;
                                }

                                if(cnt_msg == 4) printf("Type = %d | ", dat);
                                else if(cnt_msg == 5) printf("R = %d | ", dat);
                                else if(cnt_msg == 6) printf("P = %d | ", dat);
                                else if(cnt_msg == 7) printf("Y = %d | ", dat);
                                else if(cnt_msg == 8) printf("T = %d\n | ", dat);
                        }
                }
        }
}
