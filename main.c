																								
/* http://zq281598585.taobao.com/  
启光电子	  ELH    enlighten  sunny

定时器0 16位自动重装载定时器
程序采用16位全位来控制LED灯
T0工作在1T模式（AUXR.7/T0x12=0）时的输出时钟频率=(SYSclk)/(65536-[RL_TH0,RL_TL0])/2
T0工作在1T模式（AUXR.7/T0x12=1）时的输出时钟频率=(SYSclk)/12/(65536-[RL_TH0,RL_TL0])/2
*/



#include "stc15f2k60s2.h"

//真对 IAP15W4K61S4   STC15W4K56S4 系列 IO口初始化
//io口初始化 P0 P1 P2 P3 P4 为准双向IO口   
//注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
//      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
//相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
void IO_init(void)
{
  P0M0 = 0X00;
  P0M1 = 0X00;

  P1M0 = 0X00;
  P1M1 = 0X00;

  P2M0 = 0X00;
  P2M1 = 0X00;

  P3M0 = 0X00;
  P3M1 = 0X00;

  P4M0 = 0X00;
  P4M1 = 0X00;  
}

void main() 			 //主函数
{
	   IO_init();				   //真对 IAP15W4K61S4  IO口初始化
//	   AUXR|=0X80;		 //定时器0 为1T模式			//这里屏掉 采用12T分频
	   TMOD=0X00;		 //模式0 16位自动重装载
	   TL0 =0;		     //初始化计时值		 16位 为65535  这里相当于65535的数清零然后在重复加
	   TH0 =0;
	   TR0 =1;			 //定时器开始工作
	   ET0 =1;			 //使能定时器中断
	   EA  =1;			 //开总中断

	   while(1);
}


void tm0() interrupt 1 using 1
{
 P55=~P55;				  //控制P3.5口LED闪烁
}





 



