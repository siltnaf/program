
#include "./public/inc/config.h"  
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"
#include "STC15F104E.h"
#include <intrins.h>




void Process_Timer()
{

	if (Timer_update==1)
	{
		
		Time_us++;		
		Timer_update=0;	
		if (Time_us>=4)
			{
				Time_us=0;
				Time_ms++;
			}
		

		if (Time_ms>=1000) 
			{
				
				Time_ms=0;
				power_refresh++;
				Time_sec++;
			}
		if (Time_sec>=60)
			{
		
				Time_sec=0;
				Time_min++;
			}
		
	}	


}




//void Process_UV()
//{
//	if (UV_on==1)
//	{
//	
//		UV=1;
//	}
//	else UV=0;

//}


 


void Process_LED()
{

	switch (LED_type)
			{
				case 0:			
										SET_INPUT(IO_LED);
									 
										break;

				case 1: 		SET_CMOS(IO_LED);
										LED=0;
										break;
				
				case 2: 		SET_CMOS(IO_LED);
										if (Time_ms%2==0) LED=1;else LED=0;
										break;
				
				case 3: 		SET_CMOS(IO_LED);
									  LED=1;
										break;
				
				case 4: 		
										if (Time_ms%4==0) 
										{
											SET_CMOS(IO_LED);
											LED=0;
											
										}
											else 
											{
											SET_INPUT(IO_LED);
											LED=1;
											}
										if (Time_ms<50) 
										{
											SET_CMOS(IO_LED);
											LED=1;
											
										}
										
											
										break;
				
		
			}
}




void Process_sleep()
	
{

	
	if ((Time_min>=time_1min) && (state==standby_mode))
	{
		PCON|=0x02;
		_nop_ ();
		
		
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		_nop_ ();
		
		
		
	}

	
	
}



