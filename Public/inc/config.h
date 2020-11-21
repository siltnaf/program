#ifndef _CONFIG_H
#define _CONFIG_H

#include "STC15F104E.h"

#define VCC_EN		    (P30)           //relay normal open 
#define BUZ       		(P32)						//AC output for BUZ
#define LED       		(P31)           //DC output for LED
#define SW1 						(P32)
#define O3    				(P33)
//#define SW2 						(P33)
#define UV       			(P34)
#define ION 					(P35)          //output for ION


#define IO_LED          P3_1
#define IO_BUZ          P3_2
#define IO_SW1					P3_2
#define IO_O3           P3_3
//#define IO_SW2					P3_3
#define IO_UV           P3_4
#define IO_ION          P3_5



#define MAIN_Fosc   12000000L
#define T0_25MS        (65536- MAIN_Fosc/4000)     //1T mode Timer0
#define T2KHZ       (65536- MAIN_Fosc/12/6000)     //Timer2


#define uint8 unsigned char idata
#define uint16 unsigned int idata
#define uint32 unsigned long idata
#define int16 signed int idata


#define standby_mode 		0
#define ION_mode	  		1
#define O3_mode					2	
#define O3_saving_mode 	3
#define UVION_mode 			4
#define ozone_mode			5
#define wait_mode     	6
#define BUZ_mode  			7


#define time_1min       1
#define time_T1         5
#define time_T2			    10
#define time_T3				  15
#define time_5s					5
#define time_1s         1

#define press_200ms     200
#define press_3s        3000
#define scan_3s         300
#define O3_SEL					1
#define ION_SEL         0
 
 
#define SET_INPUT(P3_n)  P3M1 |=(1<<(P3_n)) ; 	P3M0 &=~((1)<<(P3_n)) 
#define SET_OUTPUT(P3_n) P3M1 &=~((1)<<(P3_n)); P3M0 &=~((1)<<(P3_n))
#define SET_OD(P3_n)     P3M1 |=(1<<(P3_n)); 		P3M0 |=(1<<(P3_n))
#define SET_CMOS(P3_n)   P3M1 &=~((1)<<(P3_n)); P3M0 |=(1<<(P3_n))

 #define P3_5 5
 #define P3_4 4
 #define P3_3 3
 #define P3_2 2
 #define P3_1 1
 #define P3_0 0
 
 
extern volatile uint8 state,next_state,SW1_state,next_SW1_state;
extern volatile uint16 process_time,buz_time,key_holdtime,power_refresh;
extern volatile uint8  LED_type, O3_level;
extern volatile uint16 Time_us,Time_ms,Time_sec,Time_min,scan_sec;
extern volatile bit Timer_update,Beep, UV_on,ION_on,O3_on,switch_update,SW1_pressed,SW2_pressed,scan,unlock;

#endif