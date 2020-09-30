
#include "STC15F104E.h"

 
#include "./public/inc/config.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
#include "./public/inc/process.h"

volatile uint8 state,next_state,SW1_state,next_SW1_state;
volatile uint8   O3_level,LED_type;
volatile uint16 process_time,buz_time,key_holdtime;
volatile uint16 Time_us, Time_ms,Time_sec,Time_min,scan_sec;
volatile bit Timer_update,Beep, UV_on,ION_on,O3_on,switch_update,SW1_pressed,SW2_pressed,scan,unlock;



void DCDC_enable(void)
{

	
	
	
												//P35 as input
		
											P3M1 |=0x20;                      	// P3M1 |= 0b00100000;
											P3M0 &=0xdf;												// P3M0 &= 0b11011111;          

//
 	if ((VCC_det==0)&&((Time_ms<500)==0)) VCC_EN=0; else VCC_EN=1;
	
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
			
			
			
			if ((key_holdtime>press_3s)&&(SW1==1))
				{
					state=standby_mode;
					unlock=0;
					SW1_state=0;
					key_holdtime=0;
					SW1_pressed=0;
					switch_update=0;
				
				}
				else if ((key_holdtime<press_3s)&&(SW1==0))
				{
		
					if (unlock==1) SW1_state++;
							else 
							{
							
								unlock=1;
							
							}
							
				   if ((SW1_state==0)&& (unlock==1))
							SW1_state=1;
					 
				if (SW1_state>3) SW1_state=0;
			
					switch (SW1_state)
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
					case 3: 		
									
									
										state=O3_mode;
										break;
				
				
					}	
		 
					scan=1;
					scan_sec=0;
					
					key_holdtime=0;
					SW1_pressed=0;
					switch_update=0;
					delay_ms(250);
				}
		}		
	
   
		


	

	
   if ((Time_ms%100)<10)
	 {
		 SW2=0;
		 SET_INPUT(IO_SW2);
		 if ((Time_ms%100)>5) 
		 {
			 EX1=1;
			 EX0=1;
		 }
	 }
	 else 
	 {
		 EX1=0;
		 EX0=0;
		 SET_CMOS(IO_SW2);
		 if (O3_on==1) SW2=1; else SW2=0;
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
										next_SW1_state=1;
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
	
	case O3_mode:				
										
										DCDC_enable();	
										LED_type=2;
										O3_level=2;
										UV_on=0;
										ION_on=0;
										if (Time_min>=59) 
										{
											
											next_state=O3_saving_mode; 
										}else next_state=O3_mode;
										 
										break;
		
		case O3_saving_mode:
										
										
										LED_type=2;
		
										
										UV_on=0;
										ION_on=0;
										if (Time_min<=5) 
										{
											DCDC_enable();
												O3_level=2;
										}else 	O3_level=0;
											
		
		
										next_state=O3_saving_mode;
									 
										break;
										
		
	
	case UVION_mode:			
										
									DCDC_enable();
	
									 LED_type=1;
										O3_level=2;
										UV_on=1;
										ION_on=0;
										
										if (Time_min>=time_T1) next_state=ozone_mode; else next_state=UVION_mode;
	
					
									 
										break;
	
	
	case ozone_mode:	
											
									DCDC_enable();
									LED_type=3;
										O3_level=2;
										UV_on=0;
										ION_on=0;
										
	
	 
										if (Time_min>=time_T2) next_state=wait_mode; else 	next_state=ozone_mode;
											
								 
										break;
			


	case wait_mode:	
											
									DCDC_enable();
								   	LED_type=3;
										O3_level=2;
										UV_on=0;
										ION_on=1;
										
	
	
					 
										if (Time_min>=time_T3) 
										{
											
											
											buz_time=0;
											Time_ms=0;
											Time_sec=0;
											next_state=BUZ_mode; 
										}
											else 	next_state=wait_mode;
									 
										
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
										LED_type=0;
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

   if ((switch_update==0)&&(SW1==1)) 
	 {
			Time_us=0;
			Time_ms=0;
			Time_sec=0;
			Time_min=0;
			SW1_pressed=1;
			key_holdtime=0;
			 
			switch_update=1;
	 }
}

void int1() interrupt 2
{

    if ((switch_update==0)&&(SW2==1)) 
	 {
		 
			Time_us=0;
			Time_ms=0;
			Time_sec=0;
			Time_min=0;
			SW2_pressed=1;
			key_holdtime=0;
			 
			switch_update=1;
	 }
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
	//P32(SW1/BUZ)->INPUT   		0      1
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

