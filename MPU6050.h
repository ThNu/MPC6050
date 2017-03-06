#ifndef MPU6050_H
#define MPU6050_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "i2c_master.h"


#define MPU6050_write 0b11010000
#define MPU6050_read 0b11010001

void init_MPU6050(void);

uint16_t MPU_read();

#endif