
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
	//P33(USB_det)->I	    		1      0
	//P34(PWM_FAN)->CMOS      		0      1
	//P35(UVC)->CMOS       		0      1
	
	
	P3M1 = 0x0c;
  P3M0 = 0x32;
	
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
		AUXR &= ~(1<<4);    //stop counter
    IE2  |=  (1<<2);    //enable timer2 interrupt
    AUXR |=  (1<<2);    //set 1T
    AUXR &= ~(1<<3);    //set timer mode
    INT_CLKO |=  0x04;  //output clock

    T2H = 0;
    T2L = 0;
    AUXR |=  (1<<4);    //start timer2

                                                       
      	
	
	
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

	PWM_FAN=0;
	
	switch_update=0;
	key_holdtime=0;
	Timer_update=0;
	EA=1;
}
