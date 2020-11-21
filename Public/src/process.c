
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
				if (scan==1) scan_sec++;
				power_refresh++;
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
	if ((UV_on==1))
	{
		UV=1;
	
//		if((Time_us%2)==0) UV=0;
//		   else UV=1;
	}
	else UV=0;

}

void Process_O3()
{
	switch (O3_level)
	{
		case 0:      
									
									O3_on=0;
									break;
		case 1:			 
									switch (Time_sec%4)
									{
										case 0,1:						
																				O3_on=1;
																				break;
										
										case 2:							
																				O3_on=1;	           	//enable every 1 out of 3sec				
																				break;
										
										case 3:						 
																				O3_on=0;
																				break;
									}									
									break;
		case 2:				
								
									O3_on=1;
									break;
	}
}

void Process_BUZ()
{
 
	
if (Beep==0) 
{
	
	
	
	
	 SET_INPUT(IO_BUZ);
		
}

	



}


void Process_LED()
{
if ((Beep==0))
{
	switch (LED_type)
			{
				case 0:			
					
										
										SET_INPUT(IO_LED);
										
										break;
				case 1:			
										SET_CMOS(IO_LED);
										LED=0;
										break;
				case 2:			
										SET_CMOS(IO_LED);
										LED=1;
										break;
				case 3: 		
										 
										if (Time_sec%2==0) 
										{
											SET_CMOS(IO_LED);
											LED=0;
										}
										else 
										{
											SET_INPUT(IO_LED);
										}
										break;
				case 4: 		
										 
										if (((Time_us%512)==0) && ((Time_sec%4)==0))
										{
											SET_CMOS(IO_LED);
											LED=0;
										}
										else 
										{
											SET_INPUT(IO_LED);
										}
										break;			
										
			}	
}
}


void Process_ION()
	
{

	SET_OUTPUT(IO_ION);
				
			
	
	
	
	
	if (ION_on==1) ION=1; else ION=0;
				

	
	
}


void Process_sleep()
	
{

	
	if ((Time_min>=time_1min) && (state==standby_mode))
	{
		EX1=1;
		EX0=1;
		SW1=0;
		SW2=0;
		SET_INPUT(IO_SW2);
		SET_INPUT(IO_SW1);
		
	 
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



