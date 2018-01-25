/*
 * Lidar-test.cpp
 *
 * Created: 10/29/2017 12:12:36 AM
 * Author : Prakash Chaudhary
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Lidar.h"


Lidar L1;
int main(void)
{ 
	sei();
   L1.attach();
   DDRB |= (1<<PB7);
  initUART0();
   UART0TransmitString("Hello\n\r");
   
    while (1) 
    {
		int temp = L1.ReadData();
		UART0Transmit('\t');
		UART0TransmitData( temp);
		UART0TransmitString("\n\r");
    }
}

ISR(TIMER1_OVF_vect)
{
	PORTB ^= (1<<PB7);
	L1.Inc_OVFcount();
	TCNT1 = 0;
}