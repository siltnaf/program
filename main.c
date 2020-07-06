
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min;
volatile bit Timer_update,UV_on,switch_update;






void Check_switch()
{
		if (key_holdtime>press_time) 
		{
			switch_state++;
			if (switch_state>4) switch_state=0;
		 
			FAN=0;
			switch (switch_state)
			{
				case 0:			
									
										state=standby_mode;
										break;
//				case 1:			
//										
//										state=speed0_mode;
//										break;
				case 1: 		
									
										UV_on=0;
										state=speed1_mode;
										break;
				case 2: 		
									
										UV_on=1;
				
										state=speed1_mode;
										break;
				
				case 3: 		
									
										UV_on=0;
										state=speed2_mode;
										break;
				
				
				case 4: 		
									
										UV_on=1;
										state=speed2_mode;
										break;
				
				
//				case 4: 		
//									
//									
//										state=speed3_mode;
//										break;
				
			}	
			
	
			Time_ms=0;
			Time_sec=0;
			Time_min=0;
			switch_update=0;
			key_holdtime=0;
			delay_ms(250);
		}		
	
   
		


	
}
			
		
		
		
	
	
	

void State_process()
{
		switch (state)
		{
	
	case standby_mode:    
										
								 
										UV_on  = 0;
										LED_type=0;
										FAN=0;
										SET_INPUT(IO_SPEED1);
										SET_INPUT(IO_SPEED2);
										next_state=standby_mode;
	
										 
	
	
										break;
	
	case speed0_mode:				
										
										
										LED_type=1;
										UV_on=1;
										SET_INPUT(IO_SPEED1);
										SET_INPUT(IO_SPEED2);
										
									  FAN=1;
										next_state=speed0_mode;
										break;
	
	case speed1_mode:			
										
//										LED_type=2;
										LED_type=3;
//										UV_on=1;
										SET_INPUT(IO_SPEED2);
										SET_CMOS(IO_SPEED1);
										SPEED1=0;

									 FAN=1;
										
									 next_state=speed1_mode;
										break;
	
	
	case speed2_mode:	
											
//										LED_type=3;
										LED_type=4;
//										UV_on=1;
										SET_INPUT(IO_SPEED1);
										SET_CMOS(IO_SPEED2);
										SPEED2=0;
									 	FAN=1;
									  next_state= speed2_mode;

										break;
	case speed3_mode:	
											
										
										LED_type=4;
										UV_on=1;
										SET_CMOS(IO_SPEED1);
										SET_CMOS(IO_SPEED2);
										SPEED1=0;
										SPEED2=0;
										FAN=1;
									 
										next_state= speed3_mode;

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

		Process_UV();
		Process_LED();
	 
	
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

