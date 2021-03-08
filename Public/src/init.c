
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"
#include "STC15F104E.h"


void IO_Init(void)
{
  
	//               			  P3M1   P3M0
	//P30(USB_det)->OD         1      1
	//P31(LED)->CMOS  				0      1
	//P32(SW)->I				   		1    	 0        
	//P33(RC)->CMOS	   				0      1
	//P34(UV)->CMOS      			0      1
	//P35(O3/VCC_det)->CMOS   0      1
	
	
	P3M1 = 0x05;
  P3M0 = 0x3b;                                                                                                                                                           ;
	
}


void InitTime0(void)
{
	TMOD &= 0x00;              //clear timer0 mode 
	AUXR =0x80 ;           			//1T mode
	TL0 =T0_25MS;
  TH0 =T0_25MS>>8;

	TR0 =1;			  
	ET0 =1;		 

}
    
 




void InitExtInterrupt (void)
{

	IT0=0;  	//detect both falling and rising edge of signal 
	EX0=1;
	PX0=1;
	IT1=1;  	//detect falling  of signal  
	EX1=1;	  //enable INT1
	PX1=1;
//	INT_CLKO |= 0x10;  //enable INT2, falling edge 
	
}




void InitParameter(void )
{
	UV=0;
	RC=1;
	O3=0;
	LED=0;
	state=standby_mode;
	switch_state=0;
	process_time=0;
 
	
	Time_us=0;
  Time_ms=0;
	Time_sec=0;
	Time_min=0;

	switch_update=0;
	key_holdtime=0;
	Timer_update=0;
	EA=1;
}
