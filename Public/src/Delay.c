#include "./public/inc/config.h" 
#include "./public/inc/Timer.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"
void delay_ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MAIN_Fosc / 14000;
		  while(--i)	;   //14T per loop
     }while(--ms);
}