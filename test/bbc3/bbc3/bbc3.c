/*
 * bbc3.c
 *
 * Created: 28-08-2018 16:49:55
 *  Author: juggermaut
 */ 

/*
 * bbtest01.c
 *
 * Created: 01-05-2018 20:56:57
 *  Author: hyperactive1011
 */ 
#define F_CPU 14745600


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h> //included to support power function

#include "i2c_lib.c"
#include "UART.c"
#include "lcd.c"

//Function to configure LCD port
void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; //all the LCD pin's direction set as output
	PORTC = PORTC & 0x80; // all the LCD pins are set to logic 0 except PORTC 7
	DDRC = DDRC | 0x08;		//Setting PORTC 3 as output for buzzer
	PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
}

//turns the buzzer ON by making PORTC3 high
void buzzer_on (void)
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore | 0x08;
	PORTC = port_restore;
}

//turns the buzzer OFF by making PORTC3 low
void buzzer_off (void)
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore & 0xF7;
	PORTC = port_restore;
}


void check_status(STAT status) 
{ 
	//lcd_print(2,1,status,5);
	if(status != OK) 
	{ 
		buzzer_on;
		while(1); //error in transmission using i2c
	} 
}

void ADXL345_accelero_init()
{
	buzzer_on();
	_delay_ms(150);
	buzzer_off();
	_delay_ms(150);
	i2c_sendbyte(0x53<<1,0x2c,0x0a);
	_delay_ms(1000);
	i2c_sendbyte(0x53<<1,0x31,0x41);
	_delay_ms(1000);
	i2c_sendbyte(0x53<<1,0x2d,0x08);
	_delay_ms(1000);
}

void L3G4200D_gyro_init()
{
	buzzer_on();
	_delay_ms(150);
	buzzer_off();
	_delay_ms(150);
	i2c_sendbyte(0x69<<1,0x20,0xff);
	_delay_ms(1000);
}

int main(void)
{
	lcd_port_config();
	lcd_set_4bit();
	lcd_init();
	
	unsigned int test;
	
	i2c_init();
	uart0_init();
	ADXL345_accelero_init();
	L3G4200D_gyro_init();
	lcd_cursor(1,1);
	lcd_wr_char('x');
	lcd_cursor(1,6);
	lcd_wr_char('y');
	lcd_cursor(1,11);
	lcd_wr_char('z');

	while (1)
	{			
		int K;
		K=i2c_getbyte(0x53<<1,0x32,&test);
		lcd_print(2,2,test,3);		
		K=i2c_getbyte(0x53<<1,0x34,&test);
		lcd_print(2,7,test,3);
		K=i2c_getbyte(0x53<<1,0x36,&test);
		lcd_print(2,12,test,3);
		K=i2c_getbyte(0x69<<1,0x28,&test);
		lcd_print(1,2,test,3);
		K=i2c_getbyte(0x69<<1,0x2a,&test);
		lcd_print(1,7,test,3);
		K=i2c_getbyte(0x69<<1,0x2c,&test);
		lcd_print(1,12,test,3);
		
	}	

}