
#include "./public/inc/config.h"  
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"
#include "STC15F104E.h"





void Process_Timer()
{
	
	
	if (Timer_update==1)
	{
		Time_ms++;
		Timer_update=0;	
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
	

}

void Process_O3()
{

}

void Process_BUZ()
{

}


void Process_LED()
{

switch (switch_state)
			{
				case 0:			LED=0;
										break;
				case 1:			LED=1;
										break;
				case 2: 		
										if (Time_sec%2==0) LED=1;else LED=0;
										break;
			}	
	
}


void Process_FAN()
	
{
	
	switch (switch_state)
			{
				case 0:			
	//               			  P3M1   P3M0
	//P30(BUZ)->CMOS     			0      1
	//P31(LED)->OUTPUT   			0      0
	//P32(SW)->INPUT     			1      0
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(FAN)->INPUT         1      0
				
				
				
											P3M1 = 0x24;
											P3M0 = 0x11;
											FAN=0;
										break;
				case 1:			
	//               			  P3M1   P3M0
	//P30(BUZ)->CMOS     			0      1
	//P31(LED)->OUTPUT   			0      0
	//P32(SW)->INPUT     			1      0
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(FAN)->OUTPUT        0      0
				
				
										if (USB_det==1)
										{
											P3M1=0x04;
											P3M0=0x11;
											FAN=1;
										}
										break;
				case 2: 		
										P3M1=0x04;
										P3M0=0x11;
										FAN=1;
										break;
			}	
	
	
	
	
}

