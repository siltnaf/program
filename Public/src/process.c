
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
		
	}	


}




void Process_UV()
{
	if (UV_on==1)
	{
	
		if((Time_us%2)==0) UV=0;
		   else UV=1;
	}
	else UV=0;

}

void Process_O3()
{
	switch (O3_level)
	{
		case 0:      
									
									O3=0;
									break;
		case 1:			 
									switch (Time_sec%4)
									{
										case 0,1:						
																				O3=1;
																				break;
										
										case 2:							
																				O3=1;	           	//enable every 1 out of 3sec				
																				break;
										
										case 3:						 
																				O3=0;
																				break;
									}									
									break;
		case 2:				
								
									O3=1;
									break;
	}
}

void Process_BUZ()
{
 
	
if (Beep==0) 
{
	
	
		//P32 as input
	//               			  P3M1   P3M0
	//P30(BUZ)->INPUT    			1      1
	//P31(LED)->CMOS   	    	0      1
	//P32(SW/BUZ)->INPUT   		1      0
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(ION)->OUTPUT        0      0
				

	//P3M1 |=0b0000 0100;
	//P3M0 &=0b1111 1011;
	
	
		P3M1 |= 0x04;               //P32 as input  
		P3M0 &= 0xfb;
}

	



}


void Process_LED()
{
if (Beep==0)
{
	switch (LED_type)
			{
				case 0:			LED=1;
										break;
				case 1:			LED=0;
										break;
				case 2: 		
										if (Time_sec%2==0) LED=1;else LED=0;
										break;
			}	
}
}


void Process_ION()
	
{

		//P35 as output
	//               			  P3M1   P3M0
	//P30(BUZ)->INPUT    			1      1
	//P31(LED/BUZ)->CMOS   		0      1
	//P32(SW)->INPUT     			1      0
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(ION)->OUTPUT         0     0
				
			
				 P3M1 &=0xdf;                      //P3M1 &=0b11011111;
				 P3M0 &=0xdf;                      //P3M0 |=0b00100000;
	
	
	
	
	
	if (ION_on==1) ION=1; else ION=0;
				

	
	
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



