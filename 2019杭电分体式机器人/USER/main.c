#include "include.h"

double required_vel = 0.0;
uint8_t IsControlFinsh;			  //�Ƿ����ָ������
uint8_t IsStop=0;					  //�Ƿ�ӵ���ͣ״̬�źŵı�־
uint8_t position=1;				  //��ǰ���򣬷�Ϊ�˿�
uint8_t target_position=1;	//Ŀ������	
uint8_t position_x = 0;			  //��ǰ������
uint8_t position_y = 2;			  //��ǰ������
uint8_t orientation = positive_x; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪx������
uint8_t target_position_x = 0;	//Ŀ�������
uint8_t target_position_y = 2;	//Ŀ��������
uint8_t stopping=0;				  //�����Ƿ���Ȼ���ڼ�ͣ״̬�ı�־


void begin(void);
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻�ر�jtag������swd��

	SystemInit();
	initialise();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
		CAN_Mode_Init();
		Ledbeep_init();
		RC_Init();
		OLED_Init(); 
		las_Init();
		usart1_Init(115200);
		PID_init();
		huiductrlinit();
		infrared_Init();
		KEY_Init();
		OLED_Clear();
		TIM5_Int_Init(35, 999); //1000HZ		PID����
		TIM6_Int_Init(359, 9999);  //10HZ		·���滮
		begin();		//����������ʼλ��

 while (1)
 {
	 if(!(stopping&&required_vel!=0))
	 {
			OLED_ShowString(0, 0, "X", 16);
			OLED_ShowNum(16,0,position_x,3,16);		//X����
			OLED_ShowString(0, 2, "Y", 16);
			OLED_ShowNum(16,2,position_y,3,16);		//Y����
			OLED_ShowString(0, 4, "P", 16);	
			OLED_ShowNum(16,4,position,3,16);			//�ֿ���
			OLED_ShowString(0, 4, "V", 16);	
			if(required_vel>0)
				OLED_ShowNum(16,4,required_vel*100,3,16);		//�����ٶ�	 
			else
				OLED_ShowNum(16,4,-(required_vel*100),3,16); //�����ٶ�
			OLED_ShowString(50, 0, "M1", 16);
			if(motor1.now_speed>0)
				OLED_ShowNum(76,0,motor1.now_speed,4,16);//���1�ٶ�
			else
				OLED_ShowNum(76,0,-motor1.now_speed,4,16);//���1�ٶ�
			OLED_ShowString(50, 2, "M2", 16);
			if(motor2.now_speed>0)
				OLED_ShowNum(76,0,motor2.now_speed,4,16);//���2�ٶ�
			else
			 OLED_ShowNum(76,0,-motor2.now_speed,4,16);//���2�ٶ�
			OLED_ShowString(50, 4, "H1", 16);
			OLED_ShowNum(76,4, ADC_JIHE[0],4,16);			//�Ҷ�1ֵ
			OLED_ShowString(50, 6, "H2", 16);
			OLED_ShowNum(76,6, ADC_JIHE[1],4,16);			//�Ҷ�2ֵ
	 }
		if (IsStop)
		{
			TIM_Cmd(TIM6, DISABLE);
			if(required_vel>0)
				required_vel -= down_vel;
			else if(required_vel<0)
				required_vel += down_vel;
			stopping = 1;
		}
		else
		{
			if (stopping)
			{
				TIM_Cmd(TIM6, ENABLE);
				stopping = 0;
			}
		}
 }
}


void begin(void)
{
	
}
