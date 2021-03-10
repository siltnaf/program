#ifndef _CONFIG_H
#define _CONFIG_H

#include "STC15F104E.h"

#define VCC_EN		    (P30)           //relay normal open 
#define LED       		(P31)           //DC output for LED
#define SW 						(P32)
#define USPRAY        (P33)
#define O3H2O 				(P34)
#define USB			    	(P35)


#define IO_VCC_EN       P3_0
#define IO_LED          P3_1
#define IO_SW						P3_2
#define IO_USPRAY				P3_3
#define IO_O3H2O        P3_4
#define IO_USB		      P3_5


#define MAIN_Fosc   35000000L
#define T0_25MS        (65536- MAIN_Fosc/4000)     //1T mode Timer0
#define T113KHz     (65536- MAIN_Fosc/113000/2)     //Timer2


#define uint8 unsigned char idata
#define uint16 unsigned int idata
#define uint32 unsigned long idata
#define int16 signed int idata


#define standby_mode 		0
#define USPRAY_mode					1
#define O3H2O_mode				2
 


#define time_1min       1
#define time_T0         5
#define time_T1         50
#define time_T2			    5
#define time_T3				  53   //every 17.5 s for 0necycle so every 3 Time_cnt will account for 1 min


#define time_5s					5
#define time_1s         1

#define press_200ms     200
#define press_3s				3000
#define O3H2O_SEL         0
 
 
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
extern volatile uint16 process_time,buz_time,key_holdtime;
extern volatile uint8  LED_type;
extern volatile uint16 Time_us,Time_ms,Time_sec,Time_min,Time_cnt;
extern volatile bit Timer_update,Beep, USPRAY_on,O3H2O_on,switch_update,status_update;

#endif