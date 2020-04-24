#ifndef _TIMER_H
#define _TIMER_H


#define TMOD_TIMER0_MODE_0	0x00
#define TMOD_TIMER0_MODE_1	0x01
#define TMOD_TIMER0_MODE_2	0x02
#define TMOD_TIMER0_MODE_3  0x03
#define TMOD_TIMER1_MODE_0	0x00
#define TMOD_TIMER1_MODE_1	0x10
#define TMOD_TIMER1_MODE_2	0x20
#define TMOD_TIMER1_MODE_3  0x30  

#define TIME0_INITIAL       0x06

#define MAIN_Fosc   12000000UL

#define counter_us   1000


extern void timer0_initial(void);
extern void timer1_initial(void);

#endif