/*
 * bbc4.c
 *
 * Created: 08-09-2018 15:25:51
 * Author : juggermaut
 */ 
#define F_CPU 14745600

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "i2c_lib.h"
#include "timer1.h"
#include "UART.h"
#include "accel.h"
#include "gyro.h"
#include "lcd.h"

char pitch[32];
char roll[32];
char gyro[32];
float pitchf, rollf, gyrof;
long int countedovf=0;

ISR(TIMER1_OVF_vect)
{
	//TIMER4 has overflowed
	//TCNT1H = 0x1F; //reload counter high value
	//TCNT1L = 0x01; //reload counter low value
	countedovf++;
	
}


void init_devices()
{
	i2c_init();
	uart0_init();
	accel_init();
	gyro_init();
	lcd_port_config();
	lcd_init();
	init_timer();
}

int main(void)
{

	init_devices();
    /* Replace with your application code */
    while (1) 
    {
			
		pitchf = read_pitch();
		rollf = read_roll();
		unsigned long timenow = (countedovf*65535 + TCNT1)/57600;
		gyrof = read_gyro(); //timenow,pitchf);
		
		itoa(pitchf,pitch,10);
		itoa(gyrof,gyro,10);
		
		uart_tx_string(pitch);
		uart_tx(',');
		uart_tx_string(gyro);
		uart_tx('\n');
		_delay_ms(500);
		
    }
}

