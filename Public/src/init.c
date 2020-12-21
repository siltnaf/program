
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"
#include "STC15F104E.h"


void IO_Init(void)
{
  
	//               			  P3M1   P3M0
	//P30(VCC_EN)->IO       	0      0
	//P31(LED)->CMOS  				0      1
	//P32(SW)->I	   					1			 0       
	//P33(FAN)->CMOS	    		0      1
	//P34(VUSB)->I      			1      0
	//P35(ION)->CMOS	    		0      1
	
	P3M1 = 0x14;
  P3M0 = 0x2a;
	
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
    
void InitTime2(void)
{
		T2L=T2KHZ;			 	
		T2H=T2KHZ>>8;      

    AUXR|=0X10;			
		IE2|=0X04;       	                                                            
      	
	
	
}




void InitExtInterrupt (void)
{

	IT0=0;  	//detect both falling and rising edge of signal (AC signal)
	EX0=1;
	PX0=1;
//	IT1=0;  	//detect both falling and rising edge of signal  (H1 signal) only rising edge 
//	EX1=1;	  //enable INT1
//	PX1=1;
//	INT_CLKO |= 0x10;  //enable INT2, falling edge 
	
}




void InitParameter(void )
{
 
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
