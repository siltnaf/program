#ifndef _CONFIG_H
#define _CONFIG_H

#include "STC15F104E.h"

sbit BUZ       	=   P3^0;
sbit LED        =   P3^1;
sbit SW        	=   P3^2;
sbit O3      		=   P3^3;
sbit UV       	=   P3^4;
sbit FAN 			  =   P3^5;
sbit USB_det		=   P3^5;

#define MAIN_Fosc   12000000L
#define T1MS        (65536- MAIN_Fosc/1000)     //1T mode

#define uint8 unsigned char idata
#define uint16 unsigned int idata
#define uint32 unsigned long idata
#define int16 signed int idata


#define standby_mode 	0
#define O3_mode  			1
#define UVO3_mode 		2
#define UV_mode				3
#define BUZ_mode  		4


#define time_4min       4
#define time_5min				5
#define time_5s					5

#define press_time     100

 
extern volatile uint8 state,next_state,switch_state,switch_update;
extern volatile uint16 process_time,buz_time,key_holdtime;
extern volatile uint8 BUZ_on, UV_on,Fan_on, LED_type, O3_level, USB_charge;
extern volatile uint16 Time_ms,Time_sec,Time_min;
extern volatile uint8 Timer_update;

#endif