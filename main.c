
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min,Time_cnt,power_refresh;
volatile bit Timer_update,Beep, USPRAY_on, O3H2O_on,switch_update,status_update;



void DCDC_enable(void)
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
					status_update=0;
				}
				else if ((key_holdtime<press_3s)&&(SW==0))
				{
				switch_state++;
				
				if (switch_state>2) switch_state=0;
				switch (switch_state)
				{
				case 0:			
									
										state=standby_mode;
										LED_type=0;
										break;
				case 1:			
										
										state=O3H2O_mode;
										power_refresh=0;
										LED_type=2;
										break;
				case 2:			
										
										state=USPRAY_mode;
										power_refresh=0;
										LED_type=1 ;
										break;
					}	
	
			
			  EX0=0;
				switch_update=0;
				status_update=0;	
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
								 
										O3H2O_on=0;
										USPRAY_on  = 0;
										switch_state=0;
									
										next_state=standby_mode;
	
										 
	
	
										break;
	
	 	case USPRAY_mode:				
										
									
										
										O3H2O_on=0;
										USPRAY_on=1;
										
										if (Time_min>=time_T0) 
										{
											Time_min=0;
											next_state=standby_mode; 
										}else next_state=USPRAY_mode;
										if (USB==1) next_state=standby_mode;
										break;
	
	
		case O3H2O_mode:				
										
									
										
										O3H2O_on=1;
										USPRAY_on=1;
										
									
										next_state=O3H2O_mode;
										if (USB==1) next_state=standby_mode;
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
	
		if (USPRAY_on==0) USPRAY=0;
		if (status_update==1)
			{
				SET_INPUT(IO_LED);
				Check_switch();
				State_process();
				Process_USPRAY();
				Process_O3H2O(); 
				Process_sleep();
				EX0=1;                   //complete the process and enable external SW interrupt
			}
		if  (switch_state==1) DCDC_enable();
		Process_Timer();
		Process_LED();
		
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
			status_update=1;
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
	if (key_holdtime>5000) status_update=0;
	
	
	
		
		}
	 
	Timer_update=1;
}




void timer2() interrupt 12  
{
  
//	if (USPRAY_on==1)
//	{
		USPRAY=~USPRAY;
		
//	}
//	else USPRAY=0;
	
}

