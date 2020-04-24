#ifndef _CONFIG_H
#define _CONFIG_H

#include "STC15F104E.h"

sbit BUZ       	=   P3^0;
sbit LED        =   P3^1;
sbit SW        	=   P3^2;
sbit O3      		=   P3^3;
sbit UV       	=   P3^4;
sbit FAN        =   P3^5;

#define MAIN_Fosc   12000000UL
#define counter_us  1000

#define uint8 unsigned char xdata
#define uint16 unsigned int xdata
#define uint32 unsigned long xdata
#define int16 signed int xdata


#define standby_mode 	0
#define O3_mode  			1
#define UVO3_mode 		2
#define UV_mode				3
#define BUZ_mode  		4


#define time_4min       4
#define time_5min				5
#define time_5s					5



 
extern volatile uint8 state,next_state,switch_state,switch_update;
extern volatile uint16 process_time,buz_time;
extern volatile uint8 BUZ_on, UV_on,Fan_on, LED_type, O3_level, USB_charge;



#endif