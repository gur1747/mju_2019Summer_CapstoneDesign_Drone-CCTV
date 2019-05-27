#include "_00_drone.h"

// 5. 함수 정의
void init(i2c_t& i2c) {	//i2c 장비를 사용하기 위해 포트 개방

	i2c.port = open("/dev/i2c-1", O_RDWR);	//읽기 쓰기로 열기
	if(i2c.port < 0) {
		fprintf (stderr,
			"Unable to open i2c-1 device: %s\n",
			strerror (errno));
		exit(-1);
	}
}//1
void init(	//i2c장비 자이로센서를 포트와 바인딩
	i2c_t& i2c,
	mpu6050_t& mpu6050) {

	mpu6050.i2c_port = i2c.port;

	ioctl(mpu6050.i2c_port, I2C_SLAVE, mpu6050.i2c_addr);	//자이로센서를 슬레이브로 열기

	wiringPiI2CWriteReg8(mpu6050.i2c_port, mpu6050.PWR_MGMT_1, 0);		//상태 비트를 0으로 설정(자이로센서 켜는 것 : 1 = on)
}//1
void read(
	mpu6050_t& mpu6050,
	gyro_raw_t& gyro_raw) {

	const int I2C_PORT = mpu6050.i2c_port;
	const int GYRO_XH = mpu6050.GYRO_XOUT_H;

	ioctl(I2C_PORT, I2C_SLAVE, mpu6050.i2c_addr);

	//원시 자이로 값 xyz 읽어옴
	gyro_raw.x=(wiringPiI2CReadReg8(I2C_PORT, GYRO_XH+0 )&0xFF)<<8;
	gyro_raw.x|=wiringPiI2CReadReg8(I2C_PORT, GYRO_XH+1 )&0xFF;
	gyro_raw.y=(wiringPiI2CReadReg8(I2C_PORT, GYRO_XH+2 )&0xFF)<<8;
	gyro_raw.y|=wiringPiI2CReadReg8(I2C_PORT, GYRO_XH+3 )&0xFF;
	gyro_raw.z=(wiringPiI2CReadReg8(I2C_PORT, GYRO_XH+4 )&0xFF)<<8;
	gyro_raw.z|=wiringPiI2CReadReg8(I2C_PORT, GYRO_XH+5 )&0xFF;
}//1
#define NSAMPLES 1000//2
void get(	//요동치는 원시 자이로 값에 대한 평균 값 구하는 함수
	mpu6050_t& mpu6050,
	gyro_offset_t& gyro_offset) {

	gyro_raw_t gyro_raw;
	int32_t sumGyX = 0, sumGyY = 0, sumGyZ = 0;

	for(int i=0;i<NSAMPLES;i++) {
		read(mpu6050, gyro_raw);

		sumGyX += gyro_raw.x;
		sumGyY += gyro_raw.y;
		sumGyZ += gyro_raw.z;

		delay(1);
	}

	gyro_offset.x = (double)sumGyX/NSAMPLES;
	gyro_offset.y = (double)sumGyY/NSAMPLES;
	gyro_offset.z = (double)sumGyZ/NSAMPLES;
}//2
void calc(	//원시 자이로 값 - 평균값 -> 보정 자이로 값
	gyro_adj_t& gyro_adj,
	gyro_raw_t& gyro_raw,
	gyro_offset_t& gyro_offset) {

	gyro_adj.x = gyro_raw.x - gyro_offset.x;
	gyro_adj.y = gyro_raw.y - gyro_offset.y;
	gyro_adj.z = gyro_raw.z - gyro_offset.z;
}//3
void calc(	//보정 자이로 값으로 pitch, roll, yaw 측정 (x, y, z)
	gyro_rate_t& gyro_rate,
	gyro_adj_t& gyro_adj) {

	gyro_rate.roll  = gyro_adj.y/131.0;
	gyro_rate.pitch = gyro_adj.x/131.0;
	gyro_rate.yaw   = gyro_adj.z/131.0;
}//4
void init(dt_t& dt)  {	//시간 주기 구하는 함수

	dt.t_prev = micros();
}//5
void calc(dt_t& dt)  {

  dt.t_now = micros();
  dt.t_period = (dt.t_now - dt.t_prev)/1000000.0;
  dt.t_prev = dt.t_now;
}//5
void calc(gyro_angle_t& gyro_angle, gyro_rate_t& gyro_rate, dt_t& dt)  {	//회전각 구하는 함수

	gyro_angle.roll  += gyro_rate.roll  * dt.t_period;
	gyro_angle.pitch += gyro_rate.pitch * dt.t_period;
	gyro_angle.yaw   += gyro_rate.yaw   * dt.t_period;

    extern throttle_t throttle;//9
    if(throttle.value==0) {
        gyro_angle.pitch = 0;
        gyro_angle.roll = 0;
        gyro_angle.yaw = 0;
    }//9
}//6
