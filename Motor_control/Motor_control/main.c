/*
 * Motor_control.c
 *
 * Created: 28/12/2018 17:08:49
 * Author : hyper
 */ 
#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timer5_init()
{
	TCCR5B = 0x00; //stop
	TCNT5H = 0x00; //Counter higher 8 bit value
	TCNT5L = 0x00; //Counter lower 8 bit value
	OCR5AH = 0x00; //Output Compair Register (OCR)
	OCR5AL = 0x00; //Output Compair Register (OCR)
	OCR5BH = 0x00; //Output Compair Register (OCR)
	OCR5BL = 0x00; //Output Compair Register (OCR)
	OCR5CH = 0x00; //Output Compair Register (OCR)
	OCR5CL = 0x00; //Output Compair Register (OCR)
	TCCR5A = 0xA9; //
	TCCR5C = 0x00;
	TCCR5B = 0x0B; //start Timer, prescaler 64,Fast PWM 8-bit
}

void init_timer()
{
	cli(); //Clears the global interrupts
	timer5_init();
	TIMSK5 = 0x01; //timer4 overflow interrupt enable
	sei();   //Enables the global interrupts
}

ISR (TIMER5_OVF_vect)
{
	
}

void motor_init(void)
{
	DDRK = 0xFF;
	PORTK = 0x00;
	DDRL = 0xFF;
}

// Function for robot motor-a velocity control
void a_velocity(unsigned char a_motor)
{
	OCR5AL = (unsigned char)a_motor;
}

// Function for robot motor-a velocity control
void b_velocity(unsigned char b_motor)
{
	OCR5BL = (unsigned char)b_motor;
}

// Function for robot motor-a velocity control
void c_velocity(unsigned char c_motor)
{
	OCR5CL = (unsigned char)c_motor;
}

void all_in_one_velocity (unsigned char a_motor1, unsigned char b_motor1, unsigned char c_motor1)
{
	OCR5AL = (unsigned char)a_motor1;
	OCR5BL = (unsigned char)b_motor1;
	OCR5CL = (unsigned char)c_motor1;
}

void rotate_anticlock(void)
{
	PORTK = 0x2A;
}

void rotate_clock (void)
{
	PORTK = 0x15;
}

void forward (void)
{
	PORTK = 0x24;
	b_velocity(255);
	c_velocity(255);
}

void backward (void)
{
	PORTK = 0x18;
	b_velocity(255);
	c_velocity(255);
}

void right (void)
{
	PORTK = 0x29;
	a_velocity(255);
	b_velocity(155);
	c_velocity(155);
}

void left (void)
{
	PORTK = 0x16;
	a_velocity(255);
	b_velocity(155);
	c_velocity(155);
}


int main(void)
{
	init_timer();
	motor_init();
	
    /* Replace with your application code */

		rotate_anticlock();
		
		all_in_one_velocity(255,255,255);
		_delay_ms(2000);
		all_in_one_velocity(0,0,0);
		_delay_ms(2000);
		
		
		forward();
		_delay_ms(3000);
		all_in_one_velocity(0,0,0);
		_delay_ms(2000);
		
		backward();
		_delay_ms(3000);
		all_in_one_velocity(0,0,0);
		_delay_ms(2000);
		
		right();
		_delay_ms(3000);
		all_in_one_velocity(0,0,0);
		_delay_ms(2000);
		
		left();
		_delay_ms(3000);
		all_in_one_velocity(0,0,0);
		_delay_ms(2000);
		
		

}

