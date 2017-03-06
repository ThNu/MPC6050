#include "MPU6050.h"

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


int main(void){
	char buffer[10];

	init_uart(9600);
	i2c_init();
	init_MPU6050();
	
	while(1){
		
		//avgx=(avgx*981)/795000;

		//sprintf(buffer,"%f",avgx);
		uint16_t avgx=MPU_read();
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
