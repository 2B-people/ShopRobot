#include "include.h"
#include "math.h"




double required_vel = 0;
uint8_t IsControlFinsh;			  //�Ƿ����ָ������
uint8_t IsStop=0;					  //�Ƿ�ӵ���ͣ״̬�źŵı�־

uint8_t target_position=1;	//Ŀ������	
uint8_t position_x = -1;			  //��ǰ������
uint8_t position_y = -1;			  //��ǰ������
uint8_t orientation ; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪx������
uint8_t target_position_x = 0;	//Ŀ�������
uint8_t target_position_y = 2;	//Ŀ��������
uint8_t stopping=0;				  //�����Ƿ���Ȼ���ڼ�ͣ״̬�ı�־
uint8_t key;
uint8_t IsHD=0;
uint8_t Obstacle=0;
uint16_t Distance=0;
void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
    
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

		SystemInit();
		initialise();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
		usart1_Init(115200);
		CAN_Mode_Init();
		Ledbeep_init();
		//RC_Init();
		OLED_Init(); 
		las_Init();
		usart1_Init(115200);
		PID_init();
		//huiductrlinit();
		//infrared_Init();
		KEY_Init();
		OLED_Clear();
	//��	TIM5_Int_Init(35, 999); //1000HZ		PID����		
		//begin();		//����������ʼλ��
	//	TIM6_Int_Init(359, 9999);  //10HZ		·��
 while (1)
 {
	 if((!stopping)||required_vel==0)
	 {
			las_measure();
			OLED_ShowString(0, 0, "X", 16);
			OLED_ShowNum(16,0,position_x,3,16);		//X����
			OLED_ShowString(0, 2, "Y", 16);
			OLED_ShowNum(16,2,position_y,3,16);		//Y����
			OLED_ShowString(0, 4, "V", 16);	
			OLED_ShowNum(16,4,(abs)(required_vel*100),3,16);		//�����ٶ�	
			OLED_ShowString(0, 4, "D", 16);	
			OLED_ShowNum(16,4,Distance,3,16);		//�����ٶ�		
			OLED_ShowNum(0,6,las_mode,5,16);		//�����ٶ�		
			OLED_ShowString(50, 0, "M1", 16);
			OLED_ShowNum(76,0,(abs)(motor1.now_speed),4,16);//���1�ٶ�
			OLED_ShowString(50, 2, "M2", 16);
			OLED_ShowNum(76,2,(abs)(motor2.now_speed),4,16);//���2�ٶ�
			OLED_ShowString(50, 4, "H1", 16);
			OLED_ShowNum(76,4, ADC_JIHE[0],4,16);			//�Ҷ�1ֵ
			OLED_ShowString(50, 6, "H2", 16);
			OLED_ShowNum(76,6, ADC_JIHE[1],4,16);			//�Ҷ�2ֵ
			key=KEY_Scan(1);
			if(key==KEY1_PRES)
				required_vel=0;
			else if(key==KEY5_PRES)
				required_vel+=0.01;
			else if(key==KEY3_PRES)
				required_vel-=0.01;
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
	
	required_vel=0.5;
	while(infrared1==BLACK&&infrared2==BLACK&&infrared3==BLACK&&infrared4==BLACK);
	required_vel=0;
	IsRotate=1;
	motor1.target_speed=1000;
	motor2.target_speed=-1000;
	delay(30);
	while(ADC_JIHE[0]>1500&&ADC_JIHE[1]>1500&&ADC_JIHE[2]>1500&&ADC_JIHE[3]>1500);
	IsRotate=0;
	IsHD=1;
	orientation=positive_y;
	position_x=0;
	position_y=2;
	target_position_x=0;
	target_position_y=3;
	path_cal();
}
