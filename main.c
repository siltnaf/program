
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min,Time_cnt;
volatile bit Timer_update,Beep, UV_on, ion_on,switch_update;



void DCDC_enable(void)
{

	
	
	
	SET_INPUT(IO_VCC_det);								
	if ((VCC_det==0)&&(Time_ms<500)==0) VCC_EN=0; else 	VCC_EN=1;
		
	
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
									
										state=standby_mode;
										break;
				case 1:			
										
										state=ion_mode;
										break;
				case 2:			
										
										state=uv_mode;
										break;
					}	
	
			
			
				switch_update=0;
				key_holdtime=0;
				delay_ms(250);
				}		
			}
   
		


	
}
			
		

//	
//void Check_switch()
//{
//	if (scan_sec>5)
//	{
//		unlock=0; 
//		scan=0;
//		scan_sec=0;
//	}
//		if (key_holdtime>press_200ms) 
//		{
//			
//			
//				if ((key_holdtime>press_3s)&&(SW1==1))
//				{
//					state=standby_mode;
//					unlock=0;
//					SW1_state=0;
//					key_holdtime=0;
//					SW1_pressed=0;
//					switch_update=0;
//				
//				}
//				else if ((key_holdtime<press_3s)&&(SW1==0))
//				{
//		
//				else if ((key_holdtime<press_3s)&&(SW1==0))
//				{
//		
//					if (unlock==1) SW1_state++;
//							else 
//							{
//							
//								unlock=1;
//							
//							}
//							
//				   if ((SW1_state==0)&& (unlock==1))
//							SW1_state=1;
//					 
//				if (SW1_state>3) SW1_state=0;
//			
//					switch (SW1_state)
//					{
//					case 0:			
//									
//										state=standby_mode;
//										break;
//					case 1:			
//										
//										state=ION_mode;
//										break;
//					case 2: 		
//									
//									
//										state=UVION_mode;
//										break;
//					case 3: 		
//									
//									
//										state=O3_mode;
//										break;
//				
//				
//					}	
//		 
//					scan=1;
//					scan_sec=0;
//					
//					key_holdtime=0;
//					SW1_pressed=0;
//					switch_update=0;
//					delay_ms(250);
//				}
//		}		
//	
//   
//		


//	

//	
//   if ((Time_ms%100)<10)
//	 {
//		 SW2=0;
//		 SET_INPUT(IO_SW2);
//		 if ((Time_ms%100)>5) 
//		 {
//			 EX1=1;
//			 EX0=1;
//		 }
//	 }
//	 else 
//	 {
//		 EX1=0;
//		 EX0=0;
//		 SET_CMOS(IO_SW2);
//		 if (O3_on==1) SW2=1; else SW2=0;
//	 }
//		 
//		


//	
//}
					
		
	
	
	

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

