#ifndef _CONFIG_H
#define _CONFIG_H

#include "STC15F104E.h"

#define VCC_EN			  (P30)           //relay normal open 
#define LED       		(P31)           //DC output for LED
#define SW 						(P32)
#define FAN					 	(P33)
#define VUSB      		(P34)
#define ION   				(P35)          //output for ION



#define IO_VCC_EN       P3_0
#define IO_LED          P3_1
#define IO_SW						P3_2
#define IO_FAN		   	  P3_3
#define IO_VUSB         P3_4
#define IO_ION		  P3_5



#define MAIN_Fosc   12000000L
#define T0_25MS        (65536- MAIN_Fosc/4000)     //1T mode Timer0
#define T2KHZ       (65536- MAIN_Fosc/12/6000)     //Timer2


#define uint8 unsigned char idata
#define uint16 unsigned int idata
#define uint32 unsigned long idata
#define int16 signed int idata


#define standby_mode 				0
#define speed0_mode  				1
#define speed1_mode 				2
#define speed2_mode					3




#define time_1min       1
#define time_T1         5
#define time_T2			    10
#define time_T3				  15
#define time_5s					5
#define time_1s         1

#define press_200ms     200
#define press_3s    		3000
 
 
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
 
 
extern volatile uint8 state,next_state,switch_state ;
extern volatile uint16 process_time,key_holdtime;
extern volatile uint8  LED_type ;
extern volatile uint16 Time_us,Time_ms,Time_sec,Time_min,power_refresh;
extern volatile bit Timer_update,ION_on,switch_update;

#endif