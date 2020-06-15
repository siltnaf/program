
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,switch_state;
volatile uint8   O3_level,LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min;
volatile bit Timer_update,Beep, UV_on,ION_on,switch_update;



void DCDC_enable(void)
{

	
//	
//	
//												//P35 as input
//		
//											P3M1 |=0x20;                      	// P3M1 |= 0b00100000;
//											P3M0 &=0xdf;												// P3M0 &= 0b11011111;          

////
//	if ((VCC_det==0)&&((Time_ms<500)==0)) VCC_EN=0; else VCC_EN=1;
	
	if ((Time_sec%10)==0) VCC_EN=0;else VCC_EN=1;
	
	
	
}



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
										
										state=ION_mode;
										break;
				case 2: 		
									
									
										state=UVION_mode;
										break;
			}	
			
//			if (state==standby_mode) state=ION_mode;
//			if (state==ION_mode) state=UVION_mode;
//			if (state==UVION_mode) state=standby_mode;
//			
			
			
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
										ION_on=0;
										O3_level  = 0;
										UV_on  = 0;
										 
										LED_type=0;
										next_state=standby_mode;
	
										 
	
	
										break;
	
	case ION_mode:				
										
									DCDC_enable();
											
									 LED_type=1;
									 O3_level=0;
										UV_on=0;
										ION_on=1;
										next_state=ION_mode;
										break;
	
	case UVION_mode:			
										
									DCDC_enable();
	
									 LED_type=2;
										O3_level=2;
										UV_on=1;
										ION_on=1;
										if (Time_min>=time_4min) next_state=UV_mode; else next_state=UVION_mode;
										break;
	
	
	case UV_mode:	
											
									DCDC_enable();
									LED_type=2;
										O3_level=0;
										UV_on=1;
										ION_on=1;
										
	
	
										ION_on=1;
										if (Time_min>=time_5min) 
										{
											ION_on=0;
											UV_on=0;
											LED_type=0;
											O3_level=0;
											
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
										BUZ=0;
										delay_ms(500);
										next_state=  standby_mode;
							
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
		Process_ION();
		Process_UV();
		Process_LED();
		Process_BUZ();
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
		
		//P32 as output
	//               			  P3M1   P3M0
	//P30(BUZ)->INPUT    			1      1
	//P31(LED)->CMOS   	    	0      1
	//P32(SW/BUZ)->INPUT   		0      1
	//P33(O3)->OUTPUT    			0      0
	//P34(UV)->CMOS      			0      1
	//P35(ION)->OUTPUT        0      0
				

	//P3M1 &=0b1111 1011;
	//P3M0 |=0b0000 0100;
	
	
		P3M1 &= 0xfb;               //P32 as CMOS output  
		P3M0 |= 0x04;
			
		BUZ=~BUZ;
}
		else BUZ=0;
}

