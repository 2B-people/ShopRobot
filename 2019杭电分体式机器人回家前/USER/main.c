#include "include.h"
#include "math.h"

//////////key_PIN1   	//��
//////////key_PIN2  	//��
//////////key_PIN3  	//��
//////////key_PIN4  	//��
//////////key_PIN5  	//��
//////////key_PIN6  	//����


double required_vel = 0;
uint8_t IsControlFinsh;			  //�Ƿ����ָ������
uint8_t IsStop=0;					  //�Ƿ�ӵ���ͣ״̬�źŵı�־

uint8_t target_position=1;	//Ŀ������	
uint8_t position_x = 6;			  //��ǰ������
uint8_t position_y = 1;			  //��ǰ������
uint8_t orientation=positive_y ; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪy������
uint8_t target_position_x = 6;	//Ŀ�������
uint8_t target_position_y = 9;	//Ŀ��������
uint8_t stopping=0;				  //�����Ƿ���Ȼ���ڼ�ͣ״̬�ı�־
uint8_t IsHD=1;
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
		RC_Init();
		OLED_Init(); 
		las_Init();
		PID_init();
		huiductrlinit();
		infrared_Init();
		KEY_Init();
		OLED_Clear();
		
		path_Init();
		if(target_position_x!=position_x||target_position_y!=position_y)
			path_cal();
		nextx=position_x;
		nexty=position_y;
   	TIM5_Int_Init(35, 999); //1000HZ		PID����		
		//begin();		//����������ʼλ��
		TIM6_Int_Init(359, 9999);  //10HZ		·��
	
	 while(1)
	 {
		 
	 
			if(RC_CtrlData.ch0>=364&&RC_CtrlData.ch0<=1684)
			{
				
				required_vel=(double)(RC_CtrlData.ch1 -1024)*0.00092;	
				motor1.target_speed=get_RPM(required_vel);
				motor2.target_speed=get_RPM(required_vel);
				if(RC_CtrlData.s1==3)
				{
					ROTATE(1);
				}
				if(RC_CtrlData.s2==3)
				{
					ROTATE(0);
				}
			}
			
			
				move_base();
			
			
		 
			if((!stopping)||required_vel==0)
			{
				OLED_SHOW_MANU();
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
