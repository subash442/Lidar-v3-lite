/* 
* Lidar.cpp
*
* Created: 10/29/2017 12:13:18 AM
* Author: Prakash Chaudhary
*/

#include "Lidar.h"


Lidar::Lidar()
{
	ovfcnt = 0;
}



void Lidar::attach()
{
	
		sei();
	//For trigger pin
		OUTPUT(TRIGGER_PIN);
		SET(TRIGGER_PIN);
		
	//For receive pin
		INPUT(RECEIVE_PIN);
		TIMSK1 |= (1<<TOIE1); //overflow interrupt enabled	
}

void Lidar::starttimer()
{
	
	TCCR1B |= (1<<CS10);	//start timer
	TCNT1 = 0;				//clear counter
}

void Lidar::stoptimer()
{
	TCNT1 = 0;
	TCCR1B = 0X00;		//stop counter
}

int Lidar::ReadData()
{
	uint32_t distance = 0;
	CLEAR(TRIGGER_PIN);
	while(!(PIND & (1<<PD3)));
	Reset_OVFcount();
	
	starttimer();
	while((PIND & (1<<PD3)));
	stoptimer();
	
	//calculation
	uint32_t time = ((ovfcnt * 65535 + TCNT1)/16.0);//*(1000000.0/F_CPU);
	UART0TransmitData(time);
	distance = (time/(TIME_PER_CM));
	
	return distance;
}