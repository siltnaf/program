#include "./public/inc/config.h" 
#include "./public/inc/Timer.h" 
#include "./public/inc/delay.h"  
#include "./public/inc/init.h"


// AT89S51�ж�
// �ж�����				�жϺ�				�ж���ڵ�ַ			 
// �ⲿ�ж�0(INT0)		0					0003H
// ��ʱ/������0(T1)		1					000BH
// �ⲿ�ж�1(INT1)		2					0013H
// ��ʱ/������1(T1)		3	 				001BH
// ���п��ж�(RI/TI)	4  					0023H
// AT89S52�����ж�
// ��ʱ/������2(T2)		5					002BH



#if 0
void timer1_initial()
{
	// ��ʱ��1������ģʽ2
	TMOD &= 0x0F;
	TMOD |= TMOD_TIMER1_MODE_2;

	// 167us
	TH1 = 0x66; 
	TL1 = 0xFF;	
	
	// �����ж�
	EA = 1;		
	ET1 = 1;

	// ������ʱ��1
	TR1= 1;
}
#endif