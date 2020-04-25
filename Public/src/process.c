
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
	if (UV_on==1)
	{
	
		if((Time_ms%2)==0) UV=0;
		   else UV=1;
	}
	else UV=0;

}

void Process_O3()
{
	switch (O3_level)
	{
		case 0:      O3=0;
									break;
		case 1:			 
									if ((Time_sec%3)==0) O3=~O3;			//enable every 1 out of 3sec
			
									break;
		case 2:				O3=1;
									break;
	}
}

void Process_BUZ()
{
	if ((key_holdtime>0)&&(key_holdtime<press_time))	Beep=1; else Beep=0;



	
	

}


void Process_LED()
{

switch (LED_type)
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

		//P35 as output
	//               			  P3M1   P3M0
	//P30(BUZ)->CMOS     			0      1
	//P31(LED/BUZ)->CMOS   		0      1
	//P32(SW)->INPUT     			1      0
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(FAN)->OUTPUT        0      0
				
			
				 P3M1 &=0xdf;                      //P3M1 &=0b11011111;
				 P3M0 &=0xdf;                      //P3M0 &=0b11011111;
	
	
	
	
	
	if (Fan_on==1) FAN=1;else FAN=0;
				

	
	
}

