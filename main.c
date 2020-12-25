
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min,power_refresh;
volatile bit Timer_update,ION_on,switch_update,refresh;


void Enable_power()
{
	

	if (((power_refresh%20)==0)&&((Time_ms<500)==0)) 
	{
		
		VCC_EN=0;
	} else VCC_EN=1;
		 
	
	
}



void Check_switch()
{
	
	
	if (key_holdtime>press_200ms) 
		{
				if ((key_holdtime>press_3s)&&(SW==1))
				{
					state=standby_mode;
					switch_state=0;
					key_holdtime=0;
					switch_update=0;
				}
				else if ((key_holdtime<press_3s)&&(SW==0))
				{
				switch_state++;
				if (switch_state>2) switch_state=0;
	
	
	
	

			switch (switch_state)
			{
				case 0:			
					
										LED_type=0;
										state=standby_mode;
										break;

				case 1: 		
										power_refresh=0;
									 	LED_type=1;
										state=speed0_mode;
										break;
				case 2: 		
										power_refresh=0;
									 	LED_type=2;
				
										state=speed1_mode;
										break;
				
				
				
			
			
				
			}	
			
	
			Time_ms=0;
			Time_sec=0;
			Time_min=0;
			switch_update=0;
			key_holdtime=0;
			delay_ms(250);
		}		
	
   
		


	
}
	
}
		
		
		
	
	
	

void State_process()
{
		switch (state)
		{
	
	case standby_mode:    
										
										FAN=0;
										LED_type=0;
									  switch_state=0;
 
										ION_on=0;
										next_state=standby_mode;
	
										 
	
	
										break;
	
	case speed0_mode:				
 
										 	
//										if (VCC_det==1) FAN=0; else FAN=1;   //wait until VCC return to 0
//										if ((Time_min%5)==0) 
//										{
//											Enable_power();
//											
//										}
										
										if (((Time_min%2)==0)&&(Time_sec<30)) FAN=1; else FAN=0;
										ION_on=1;
									  if (VUSB==1) next_state=standby_mode; else next_state=speed0_mode;
										break;
	
	case speed1_mode:				
										
										Enable_power();
										FAN=1;
										ION_on=1;
										 
									 
										if (VUSB==1) next_state=standby_mode; else next_state=speed1_mode;
										break;
	
	 
	
	
	



	
		}
		
state=next_state;


}








void main(void) 
{
	IO_Init();
	InitTime0();
	InitTime2();
	InitExtInterrupt();

	InitParameter()	;

	while(1) 
	{ 
	

		
		Check_switch();
		State_process();
		

		Process_Timer();
 
		Process_LED();
	 
		Process_ION();
		Process_sleep();


		
	} 
}

void int0() interrupt 0
{

   if ((switch_update==0)&&(SW==1)) 
	 {
			Time_us=0;
			Time_ms=0;
			Time_sec=0;
			Time_min=0;
			
			key_holdtime=0;
			switch_update=1;
	 }
}

void int1() interrupt 2
{
   
}


 
void timer0() interrupt 1
{

if (switch_update==1) 
{
	key_holdtime++;
	
	
	
		
		}
	 
	Timer_update=1;
}




void timer2() interrupt 12  
{

		 
}

