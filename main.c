
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min,Time_cnt,scan_sec;
volatile bit Timer_update,Beep, UV_on, ion_on,switch_update,scan,unlock;



void DCDC_enable(void)
{

	
	
//	
//	SET_INPUT(IO_VCC_det);								
//	if ((VCC_det==0)&&(Time_ms<500)==0) VCC_EN=0; else 	VCC_EN=1;
//		
	
}



void Check_switch()
{
	
	
	if (scan_sec>5)
	{
		unlock=0; 
		scan=0;
		scan_sec=0;


	}
	

			if (key_holdtime>press_200ms) 
		{
				if ((key_holdtime>press_3s)&&(SW==1))
				{
					unlock=0;
					state=standby_mode;
					switch_state=0;
					key_holdtime=0;
					switch_update=0;
				}
				else if ((key_holdtime<press_3s)&&(SW==0))
				{
					if (unlock==1) switch_state++;
							else 
							{		
								unlock=1;
							}
							
				  if ((switch_state==0)&& (unlock==1))
							switch_state=1;
					
					
					
					
					
				if (switch_state>2) switch_state=0;
				switch (switch_state)
				{
				case 0:			
									
										state=standby_mode;
										break;
				case 1:			
										
										state=ion_mode;
										break;
				case 2:			
										
										state=uv_mode;
										break;
					}	
	
				scan=1;
				scan_sec=0;
			  EX0=0;
				switch_update=0;
				delay_ms(200);
				key_holdtime=0;
				}		
			}

	
}
			
		

	
	
	

void State_process()
{
		switch (state)
		{
	
	case standby_mode:    
										
										VCC_EN=1;
								 
										ion_on=0;
										UV_on  = 0;
										switch_state=0;
										LED_type=0;
										next_state=standby_mode;
	
										 
	
	
										break;
	
	 	case uv_mode:				
										
										DCDC_enable();	
										LED_type=2;
										ion_on=0;
										UV_on=1;
										
										if (Time_min>=time_T0) 
										{
											Time_min=0;
											next_state=standby_mode; 
										}else next_state=uv_mode;
										if (USB==1) next_state=standby_mode;
										break;
	
	
		case ion_mode:				
										
										DCDC_enable();	
										LED_type=2;
										ion_on=1;
										UV_on=0;
										
									
										next_state=ion_mode;
										if (USB==1) next_state=standby_mode;
										break;
		
	
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
	 
	  Process_ION(); 
		Process_sleep();
		EX0=1;                   //complete the process and enable external SW interrupt

		
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

