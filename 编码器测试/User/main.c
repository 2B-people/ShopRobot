#include "STM32F1.h"

u16	Parameter = 512;																	//�������������
u16 Count,OldCNT;

int main(void)
{
	delay_init();	    	 																//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 																//���ڳ�ʼ��Ϊ115200
	LCD_Init();			   																	//��ʼ��LCD  
	TIM4_Init();																				//��ʼ��TIM4Ϊ���������ģʽ
	POINT_COLOR=BLUE;																		//������ɫ
	LCD_ShowString(75,150,200,16,16,"Count:");

  while(1)
	{
		 u16 NewCNT=0;
        int CNT;
        NewCNT=TIM4->CNT;
        CNT=NewCNT-OldCNT;
      
 
                
        OldCNT=NewCNT;  
			if((int)CNT<=0)
       LCD_ShowNum(125,150,abs((int)CNT),5,16); 
			else
				LCD_ShowNum(125,250,(int)CNT,5,16); 
		}		
}


/*------------End line - Lx ------------*/
