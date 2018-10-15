/********************************SCILAB_LIBRARY*****************************/
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "UART.h"	//provided this is the location where you saved your uart library file
#include "gyro.h"
#include "accel.h"

//#include "scilab.h"


void timer1_init()
{
	TCCR1B = 0x00; //stop
	TCNT1H = 0x00; //Counter higher 8 bit value
	TCNT1L = 0x00; //Counter lower 8 bit value
	OCR1AH = 0x00; //Output Compair Register (OCR)- Not used
	OCR1AL = 0x00; //Output Compair Register (OCR)- Not used
	OCR1BH = 0x00; //Output Compair Register (OCR)- Not used
	OCR1BL = 0x00; //Output Compair Register (OCR)- Not used
	OCR1CH = 0x00; //Output Compair Register (OCR)- Not used
	OCR1CL = 0x00; //Output Compair Register (OCR)- Not used
	ICR1H  = 0x00; //Input Capture Register (ICR)- Not used
	ICR1L  = 0x00; //Input Capture Register (ICR)- Not used
	TCCR1A = 0x00;
	TCCR1C = 0x00;
	TCCR1B = 0x04; //start Timer, prescaler 256
}

void init_timer()
{
	cli(); //Clears the global interrupts
	timer1_init();
	TIMSK1 = 0x01; //timer4 overflow interrupt enable
	sei();   //Enables the global interrupts
}

