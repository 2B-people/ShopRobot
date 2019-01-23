#include "include.h"

double required_vel = 0.3;
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


double K_P=2.475;
double K_I=0.029;
double K_D=0.02;


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
	TIM5_Int_Init(35, 999); //1000HZ		
	//TIM6_Int_Init(359,9999); //10HZ 
	OLED_Init(); 
	OLED_Clear();
	usart1_Init(115200);
	PID_init();
	KEY_Init();
	CAN_Mode_Init();
 while (1)
 {
	 usart1_print("%d\n",motor2.now_speed);
		OLED_ShowString(0, 0, "P", 16);
		OLED_ShowNum(16,0,s_PIDcm2.Kp*1000,4,16);
		OLED_ShowString(0, 2, "I", 16);
		OLED_ShowNum(16,2,s_PIDcm2.Ki*1000,4,16);
		OLED_ShowString(0, 4, "V", 16);
		OLED_ShowNum(16,4,required_vel*1000,4,16);
		OLED_ShowString(50, 0, "M1", 16);
	 	OLED_ShowNum(76,0,motor1.now_speed,4,16);
		OLED_ShowString(50, 2, "M2", 16);
	  OLED_ShowNum(76,2,motor2.now_speed,4,16);
		OLED_ShowString(0, 6, "S", 16);
	  OLED_ShowNum(16,6,motor2.target_speed,4,16);
	 	OLED_ShowString(50, 4, "T1", 16);
	 	OLED_ShowNum(76,4,(int32_t)s_PIDcm1.pid_out,4,16);
		OLED_ShowString(50, 6, "T2", 16);
	  OLED_ShowNum(76,6,(int32_t)s_PIDcm2.pid_out,4,16);
		switch(KEY_Scan(1))
		{
			case KEY1_PRES:required_vel+=0.005;break;
			case KEY2_PRES:required_vel-=0.005;break;
			case KEY3_PRES:s_PIDcm2.Kd+=0.01;break;
			case KEY4_PRES:K_P-=0.01;break;
			case KEY5_PRES:K_I-=0.01;break;
			case KEY6_PRES:K_D-=0.01;break;
		}
 }
}
