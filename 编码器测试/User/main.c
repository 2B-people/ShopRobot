#include "STM32F1.h"

u16	Parameter = 512;																	//�������������
int32_t position;
uint16_t last_timer;
int16_t last_timer_diff;
volatile uint32_t _counter;
unsigned long prev_update_time_; 
long prev_encoder_ticks_; 
int counts_per_rev_ = 15000;
int rpm;
void SysTick_Handler(void) 
{
	_counter++;
}
uint32_t millis(void) 
{
	return _counter;
}
void updateSpeed(long encoder_ticks)
{
	//this function calculates the motor's RPM based on encoder ticks and delta time
	unsigned long current_time = millis();
	unsigned long dt = current_time - prev_update_time_;

	//convert the time from milliseconds to minutes
	double dtm = (double)dt / 60000;
	double delta_ticks = encoder_ticks - prev_encoder_ticks_;

	//calculate wheel's speed (RPM)
	rpm = (delta_ticks / counts_per_rev_) / dtm;

	prev_update_time_ = current_time;
	prev_encoder_ticks_ = encoder_ticks;
}
int main(void)
{
	delay_init();	    	 																//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	LCD_Init();			   																	//��ʼ��LCD  
	TIM4_Init();																				//��ʼ��TIM4Ϊ���������ģʽ
	_counter = 0;
	SysTick_Config(SystemCoreClock / 1000);
	
	
  while(1)
	{
		uint16_t timer_value = TIM_GetCounter(TIM4);
		last_timer_diff = timer_value - last_timer;
		last_timer = timer_value;
		position += (int32_t) last_timer_diff;
			
		updateSpeed(position);
		if(rpm<=0)
		{
			LCD_ShowString(10,20,1,1,16,"-");
			LCD_ShowNum(20,20,abs(rpm),8,16);
			LCD_ShowNum(20,40,0,8,16);
		}
		else
		{
			LCD_ShowNum(20,20,0,8,16);
			LCD_ShowNum(20,40,rpm,8,16);
		}
			
		LCD_ShowNum(20,80,_counter,10,16);	

		}		
}


/*------------End line - Lx ------------*/
