extern "C"
{
#include "delay.h"
#include "sys.h"
#include "usart.h"
}
#include "lcd.h"
#include "remote.h"
/************************************************
 ALIENTEK ս��STM32F103������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
 extern REMOTE RC_CtrlData;
int count;
double required_angular_vel;
double required_vel_x;
double required_vel_y;
 int main(void)
 {	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LCD_Init();
	RC_Init();	 
	 LCD_Clear(WHITE);
  	while(1) 
	{		 
		LCD_ShowNum(10,10,RC_CtrlData.ch0,5,16); 
		LCD_ShowNum(10,40,RC_CtrlData.ch1,5,16); 
		LCD_ShowNum(10,70,RC_CtrlData.ch2,5,16); 
		LCD_ShowNum(10,100,RC_CtrlData.ch3,5,16); 
		LCD_ShowNum(10,130,RC_CtrlData.s1,5,16); 
		LCD_ShowNum(10,160,RC_CtrlData.s2,5,16); 
		LCD_ShowNum(10,190,(int)required_angular_vel,3,16); 
		LCD_ShowNum(10,220,(int)required_vel_x,3,16); 
		LCD_ShowNum(10,250,(int)required_vel_y,3,16); 
		count++;
	} 
}
