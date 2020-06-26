
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   O3_level,LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min;
volatile bit Timer_update,Beep, UV_on, sleep_on,switch_update;



void DCDC_enable(void)
{

	
	
	
	SET_INPUT(IO_VCC_det);								
	if ((VCC_det==0)&&(Time_ms<500)==0) VCC_EN=0; else 	VCC_EN=1;
		
	
}



void Check_switch()
{
		if (key_holdtime>press_time) 
		{
			switch_state++;
			if (switch_state>1) switch_state=0;
		 
			
			switch (switch_state)
			{
				case 0:			
									
										state=standby_mode;
										break;
				case 1:			
										
										state=uv_mode;
										break;
		
				
			}	
	
			
			
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
										
										VCC_EN=1;
								 
										O3_level  = 0;
										UV_on  = 0;
										 
										LED_type=0;
										next_state=standby_mode;
	
										 
	
	
										break;
	
	 	case uv_mode:				
										
										DCDC_enable();	
										LED_type=2;
										O3_level=1;
										UV_on=1;
										
										if (Time_min>=time_T0) 
										{
											Time_min=0;
											next_state=O3_saving_mode; 
										}else next_state=O3_mode;
										break;
	
	
		case O3_mode:				
										
										DCDC_enable();	
										LED_type=2;
										O3_level=1;
										UV_on=1;
										
										if (Time_min>=time_T1) 
										{
											Time_min=0;
											next_state=O3_saving_mode; 
										}else next_state=O3_mode;
										break;
		
		case O3_saving_mode:
										
										DCDC_enable();
										LED_type=4;
										O3_level=1;
										UV_on=0;
										
										if (Time_min>=time_T2) 
										{
											LED_type=0;
											Time_min=0;
											next_state=O3_off_mode; 
										}else next_state=O3_saving_mode;
										
										break;
			
		
		
		
		case O3_off_mode:
										UV_on=0;
										LED_type=0;
										O3_level=0;
									 next_state=O3_off_mode;
										
										break;								
		 
	
		case O3_LED_mode:
										UV_on=0;
										LED_type=2;
										O3_level=0;
										
										if (Time_sec>=1)
											{
											LED_type=0;
											next_state=O3_off_mode;
											} else next_state=O3_LED_mode;
										if (Time_min>=time_T3) 
											{
											Time_min=0;
											next_state=O3_saving_mode; 
											}
		}
		
state=next_state;


}








void main(void) 
{
	IO_Init();
	InitTime0();
	 
	InitExtInterrupt();

	InitParameter()	;
	


	while(1) 
	{ 
	

	
  	Check_switch();
		State_process();
		

		Process_Timer();
	 
		Process_UV();
		Process_LED();
	 
		Process_O3();
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
 if (RC==0) Time_min++;

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

