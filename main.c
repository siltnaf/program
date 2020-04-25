
#include "STC15F104E.h"

#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state,switch_update;
volatile uint8   UV_on,Fan_on, O3_level,LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_ms,Time_sec,Time_min;
volatile uint8 Timer_update,Beep;


void Check_switch()
{
		if (key_holdtime>press_time) 
		{
			switch_state++;
			if (switch_state>2) switch_state=0;
		 
			
			switch (switch_state)
			{
				case 0:			
										
										state=standby_mode;
										break;
				case 1:			
										
										state=O3_mode;
										break;
				case 2: 		
									
										Time_ms=0;
										Time_sec=0;
										Time_min=0;
										state=UVO3_mode;
										break;
			}	
			
			
			
			
			
			switch_update=0;
			key_holdtime=0;
		}		
	
 
		


	
}
			
		
		
		
	
	
	

void State_process()
{
		switch (state)
		{
	
	case standby_mode:    
											
	
										Fan_on=0;
	
								
								 
										O3_level  = 0;
										UV_on  = 0;
										 
										LED_type=0;
										next_state=standby_mode;
										break;
	
	case O3_mode:				
					

//												//P35 as input
//		
											P3M1 |=0x20;                      	// P3M1 |= 0b00100000;
											P3M0 &=0xdf;												// P3M0 &= 0b11011111;          
											if (USB_det==1)	Fan_on=1; else Fan_on=0;
							
									
											
										LED_type=1;
										O3_level=1;
										UV_on=0;
										
										next_state=O3_mode;
										break;
	
	case UVO3_mode:			
							 
										LED_type=2;
										O3_level=2;
										UV_on=1;
										Fan_on=1;
										if (Time_min>time_4min) next_state=UV_mode; else next_state=UVO3_mode;
										break;
	
	
	case UV_mode:	
								 
										LED_type=2;
										O3_level=0;
										UV_on=1;
										Fan_on=1;
										if (Time_min>time_5min) 
										{
											buz_time=0;
											Time_ms=0;
											Time_sec=0;
											next_state=BUZ_mode; 
										}
											else 	next_state=UV_mode;
											
										break;
										
	case BUZ_mode:
 
										Beep=1;
										delay_ms(250);
										Beep=0;
										delay_ms(250);
										Beep=1;
										delay_ms(250);
										Beep=0;
										next_state=standby_mode;
											
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
		Process_FAN();
		Process_UV();
		Process_LED();
		Process_BUZ();
		Process_O3();
		
	} 
}

void int0() interrupt 0
{

   if ((switch_update==0)&&(SW==1)) 
	 {
			
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
 if (Beep==1) 
		{
			
	
			
			BUZ=~BUZ;
			if (BUZ==1) LED=0;else LED=1;
		}
		else 
		{	
			BUZ=0;

		}
}
