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

void init_uart(uint16_t baudrate){

	uint16_t UBRR_val = (F_CPU/16)/(baudrate-1);

	UBRR0H = UBRR_val >> 8;
	UBRR0L = UBRR_val;

	UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0); // UART TX (Transmit - senden) einschalten
	UCSR0C |= (1<<USBS0) | (3<<UCSZ00); //Modus Asynchron 8N1 (8 Datenbits, No Parity, 1 Stopbit)
}

void uart_putc(unsigned char c){

	while(!(UCSR0A & (1<<UDRE0))); // wait until sending is possible
	UDR0 = c; // output character saved in c
}

void uart_puts(char *s){
	while(*s){
		uart_putc(*s);
		s++;
	}
}


void init_MPU6050(void){

	i2c_start(MPU6050_write);
	i2c_write(0x6B); // set pointer to CRA
	i2c_write(0x00); // write 0x70 to CRA
	i2c_stop();
}





int main(void){
	char buffer[10];
	uint16_t raw_x,raw_y,raw_z;

	init_uart(9600);
	i2c_init();
	init_MPU6050();
	
	while(1){
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
		//avgx=(avgx*981)/795000;

		//sprintf(buffer,"%f",avgx);
	    itoa(avgx, buffer, 10);
		uart_puts("x=");
		uart_puts(buffer);
		uart_puts("  ");
		
		//itoa(raw_y, buffer, 10);
		//uart_puts("y=");
		//uart_puts(buffer);
		//uart_puts("  ");
		//
		//itoa(raw_z, buffer, 10);
		//uart_puts("z=");
		//uart_puts(buffer);
		//uart_puts("  ");
		
		uart_putc('\n');
		
		
		_delay_ms(200);
	}
	
	return 0;
}
