
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
				Time_sec++;
			}
		if (Time_sec>=60)
			{
		
				Time_sec=0;
				Time_min++;
			}
		 if (Time_min>=60)
			{
				Time_min=0;
			}
			
	}	


}




void Process_UV()
{
	if (UV_on==1)
	{
	
//		if((Time_us%2)==0) UV=0;
		 UV=1;
	}
	else UV=0;;

}

void Process_ION()
{
	SET_CMOS(IO_ION);	
	if (ion_on==1) ION=1;else ION=0;
	
	
	
}

 

void Process_LED()
{
if (Beep==0)
{
	switch (LED_type)
			{
				case 0:			
					
										
										SET_INPUT(IO_LED);
										
										break;
				case 1:			
										SET_CMOS(IO_LED);
										LED=1;
										break;
				case 2:			
										SET_CMOS(IO_LED);
										LED=0;
										break;
				case 3: 		
										 
										if (Time_ms<500==0) 
										{
											SET_CMOS(IO_LED);
											LED=1;
										}
										else 
										{
											SET_INPUT(IO_LED);
										}
										break;
			
										
			}	
}
}


 


void Process_sleep()
	
{

	
	if ((Time_min>=time_1min) && (state==standby_mode))
	{
		
		UV=0;
		ION=0;
		SET_INPUT(IO_LED);
		VCC_EN=1;
		switch_state=0;
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
		
		
	
	
//	

		
	}
	
	
}



