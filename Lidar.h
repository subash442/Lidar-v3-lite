/* 
* Lidar.h
*
* Created: 10/29/2017 12:13:18 AM
* Author: Prakash Chaudhary
*/


#ifndef __LIDAR_H__
#define __LIDAR_H__

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "Headers.h"

#define TRIGGER_PIN		D,2
#define RECEIVE_PIN		D,3

#define	TIME_PER_CM		10.0



class Lidar
{
	private:
		uint16_t ovfcnt;
	public:
		Lidar();
		void attach();
		void starttimer();
		void stoptimer();
		int ReadData();
		void Inc_OVFcount(){ovfcnt++;}
		void Reset_OVFcount(){ovfcnt = 0;}
		uint16_t Get_OVFcount(){return ovfcnt;}
		

}; 


#endif //__LIDAR_H__
