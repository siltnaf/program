
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"
#include "STC15F104E.h"


void IO_Init(void)
{
  
	//               			  P3M1   P3M0
	//P30(BUZ)->CMOS     			0      1
	//P31(LED)->OUTPUT   			0      0
	//P32(SW)->INPUT     			1      0
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(FAN)->open drain    1      1
	
	
	P3M1 = 0x24;
  P3M0 = 0x31;
	
}


void InitTime0(void)
{
	
	TMOD &= 0xf0;              //clear timer0 mode 

	
	AUXR =0x00 ;           //timer 0 as 12T mode
	
	TH0 =(65536-counter_us)/256;
  TL0 = (65536-counter_us)%256;
	
	TR0 =1;			
	ET0 =1;			 
	
	
	
}
     


void InitExtInterrupt (void)
{

	IT0=0;  	//detect both falling and rising edge of signal (AC signal)
	EX0=1;
	PX0=1;
	IT1=0;  	//detect both falling and rising edge of signal  (H1 signal) only rising edge 
	EX1=1;	  //enable INT1
	PX1=1;
	INT_CLKO |= 0x10;  //enable INT2, falling edge 
	
}




void InitParameter(void )
{
	UV=0;
	state=standby_mode;
	switch_state=0;
	process_time=0;
	buz_time=0;
}
