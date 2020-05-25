#ifndef _CONFIG_H
#define _CONFIG_H

#include "STC15F104E.h"

#define VCC_EN		    (P30)           //relay normal open 
#define BUZ       		(P32)						//AC output for BUZ
#define LED       		(P31)           //DC output for LED
#define SW 						(P32)
#define O3    				(P33)
#define UV       			(P34)
#define ION 					(P35)          //output for ION
#define VCC_det	  		(P35)          //input for USB detect

#define MAIN_Fosc   12000000L
#define T1MS        (65536- MAIN_Fosc/1000)     //1T mode Timer0
#define T2KHZ       (65536- MAIN_Fosc/12/6000)     //Timer2


#define uint8 unsigned char idata
#define uint16 unsigned int idata
#define uint32 unsigned long idata
#define int16 signed int idata


#define standby_mode 	0
#define ION_mode  		1
#define UVION_mode 		2
#define UV_mode				3
#define BUZ_mode  		4


#define time_1min       1
#define time_4min       4
#define time_5min				5
#define time_5s					5
#define time_1s         1

#define press_time     200
#define O3_SEL					1
#define ION_SEL         0
 
extern volatile uint8 state,next_state,switch_state ;
extern volatile uint16 process_time,buz_time,key_holdtime;
extern volatile uint8  LED_type, O3_level;
extern volatile uint16 Time_ms,Time_sec,Time_min;
extern volatile bit Timer_update,Beep, UV_on,ION_on,switch_update;

#endif