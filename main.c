
#include "STC15F104E.h"

#include "./public/inc/config.h" 
#include "./public/inc/Timer.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"


unsigned int idata guiTimer1S = 4000;



void main(void) 
{
	IO_Init();
	InitTime0();
	InitExtInterrupt();


	while(1) 
	{ 
		UV=~UV;

		delay_ms(100);	
	} //end of while
}

void isr_int0() interrupt 0
{
    guiTimer1S = 30000; 
}

void isr_int1() interrupt 2
{
    guiTimer1S = 30000; 
}


// 定时器0中断处理函数
void isr_timer0() interrupt 1
{
	guiTimer1S--;

	if (0 == guiTimer1S)
	{
		guiTimer1S = 1000;			
		
//		LED4 = ~LED4;
//		LED5 = ~LED5;
	}				   	
}

