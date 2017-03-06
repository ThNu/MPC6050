#include "MPU6050.h"

void init_MPU6050(void){

	i2c_start(MPU6050_write);
	i2c_write(0x6B); // set pointer to CRA
	i2c_write(0x00); // write 0x70 to CRA
	i2c_stop();
}

uint16_t MPU_read(){
	uint16_t raw_x,raw_y,raw_z;
	long long int avgx;
	avgx=0;
	for(int x=0;x<10;x++){
		i2c_start(MPU6050_write);
		i2c_write(0x3B); // set pointer to X axis MSB
		i2c_stop();

		i2c_start(MPU6050_read);

		
		raw_x = ((uint8_t)i2c_read_ack())<<8;
		raw_x |= i2c_read_ack();

		raw_y = ((uint8_t)i2c_read_ack())<<8;
		raw_y |= i2c_read_nack();

		raw_z = ((uint8_t)i2c_read_ack())<<8;
		raw_z |= i2c_read_ack();

		i2c_stop();

		avgx+=raw_x;
	}
	
	avgx=avgx/10;
	avgx-=550;
	return (uint16_t)avgx;
}