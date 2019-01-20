#include "include.h"

double required_vel = 0.0;
uint8_t IsControlFinsh;			  //�Ƿ����ָ������
uint8_t IsStop;					  //�Ƿ�ӵ���ͣ״̬�źŵı�־
uint8_t position;				  //��ǰ���򣬷�Ϊ�˿�
uint8_t position_x = 0;			  //��ǰ������
uint8_t position_y = 2;			  //��ǰ������
uint8_t orientation = positive_x; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪx������
uint8_t target_position_x = 0;	//Ŀ�������
uint8_t target_position_y = 3;	//Ŀ��������
uint8_t stopping;				  //�����Ƿ���Ȼ���ڼ�ͣ״̬�ı�־
uint8_t isHd = 1;

//uint32_t publish_las_time = 0;
//uint32_t publish_vel_time = 0;
//uint32_t publish_remote_time = 0;
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻�ر�jtag������swd��

	SystemInit();
	initialise();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	CAN_Mode_Init();
	TIM5_Int_Init(71, 9999); //100HZ		
	TIM6_Int_Init(719,9999); //10HZ 
	OLED_Init(); 
	OLED_Clear();
	usart1_Init(115200);
	PID_init();
	KEY_Init();

 while (1)
 {
		OLED_ShowNum(0,0,K_P*100,3,16);
		OLED_ShowNum(0,1,K_I*100,3,16);
		OLED_ShowNum(0,2,K_D*100,3,16);
	 	OLED_ShowNum(0,3,motor1.now_speed*100,3,16);
	  OLED_ShowNum(0,4,motor2.now_speed*100,3,16);
		switch(KEY_Scan(0))
		{
			case KEY1_PRES:K_P+=0.01;break;
			case KEY2_PRES:K_I+=0.01;break;
			case KEY3_PRES:K_D+=0.01;break;
			case KEY4_PRES:K_P-=0.01;break;
			case KEY5_PRES:K_I-=0.01;break;
			case KEY6_PRES:K_D-=0.01;break;
		}
 }
}
