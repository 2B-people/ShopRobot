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
	//TIM5_Int_Init(71, 9999); //100HZ		PID����
	// TIM6_Int_Init(71, 999);  //10HZ		·���滮

	RC_Init();
	OLED_Init(); 
	OLED_Clear();
	//las_Init();
	usart1_Init(115200);
	PID_init();
	huiductrlinit();

	while (1)
	{

	}

	// while (1)
	// {
	// 	if (IsStop)
	// 	{
	// 		TIM_Cmd(TIM6, DISABLE);
	// 		required_vel -= 0.005;
	// 		if (required_vel <= 0)
	// 			required_vel = 0;
	// 		stopping = 1;
	// 	}
	// 	else
	// 	{
	// 		if (stopping)
	// 		{
	// 			TIM_Cmd(TIM6, ENABLE);
	// 			stopping = 0;
	// 		}
	// 	}
	// }
}
