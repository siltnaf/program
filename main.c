
#include "STC15F104E.h"

#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state,switch_update;
volatile uint8 BUZ_on, UV_on,Fan_on, LED_type, O3_level, USB_charge;
volatile uint16 process_time,buz_time;
volatile uint16 Time_ms,Time_sec,Time_min;
volatile uint8 Timer_update;

void Update_switch()
{
	
	if (switch_update==1)
		switch (switch_state)
			{
				case 0:			state=standby_mode;
										break;
				case 1:			state=O3_mode;
										break;
				case 2: 		
										Time_ms=0;
										Time_sec=0;
										Time_min=0;
										state=UVO3_mode;
										break;
			}	
	switch_update=0;
	if (switch_state>2) switch_state=0;
	
}
			
		
		
		
	
	
	

void State_process()
{
		switch (state)
		{
	
	case standby_mode:    
											
							
										BUZ_on = 0;
										LED_type = 0;
										O3_level  = 0;
										UV_on  = 0;
										Fan_on = 0;				
										next_state=standby_mode;
										break;
	
	case O3_mode:				
										BUZ_on=0;
										LED_type=1;
										O3_level=1;
										UV_on=0;
										if (USB_charge==1) Fan_on=1; else Fan_on=0;
										next_state=O3_mode;
										break;
	
	case UVO3_mode:			
										BUZ_on=0;
										LED_type=2;
										O3_level=2;
										UV_on=1;
										Fan_on=1;
										if (Time_min>time_4min) next_state=UV_mode; else next_state=UVO3_mode;
										break;
	
	
	case UV_mode:	
										BUZ_on=0;
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
											else next_state=UV_mode;
										break;
										
	case BUZ_mode:
										BUZ_on=1;
										if (Time_sec>time_5s) next_state=standby_mode;
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
	switch_state=2;
		Update_switch();
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
   if ((switch_update==0) && (SW==1))
	 {
			switch_state++;
			switch_update=1;
	 }
}

void int1() interrupt 2
{
   
}


// 定时器0中断处理函数
void timer0() interrupt 1
{


Timer_update=1;

}

