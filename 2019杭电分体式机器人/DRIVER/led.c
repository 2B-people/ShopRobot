#include "led.h"
void Ledbeep_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED_PIN1|LED_PIN2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK3, ENABLE);
	GPIO_InitStructure.GPIO_Pin =LED_PIN3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT3, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(BEEP_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);
	
	LED_On_Off(False,LED_PIN1);
	LED_On_Off(False,LED_PIN2);
	LED_On_Off(False,LED_PIN3);
	Beep_On_Off(False);
}

void LED_On_Off(char status, uint16_t LED_Pin)
{
	if(LED_Pin!=LED_PIN3)
	{
		if (status == False)
		{
			GPIO_SetBits(LED_GPIO_PORT,LED_Pin); //�ߵ�ƽ����
		}
		else
		{
			GPIO_ResetBits(LED_GPIO_PORT, LED_Pin);
		}
	}
	else
	{
		if (status == False)
		{
			GPIO_SetBits(LED_GPIO_PORT3,LED_Pin); //�ߵ�ƽ����
		}
		else
		{
			GPIO_ResetBits(LED_GPIO_PORT3, LED_Pin);
		}
	}
}

void Beep_On_Off(char status)
{
	if (status == True)
	{
		GPIO_SetBits(BEEP_PORT,BEEP_PIN); //�ߵ�ƽ��
	}
	else
	{
		GPIO_ResetBits(BEEP_PORT, BEEP_PIN);
	}
}


