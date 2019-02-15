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
uint8_t position_x = 0;			  //��ǰ������
uint8_t position_y = 0;			  //��ǰ������
uint8_t orientation=positive_y ; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪy������
uint8_t target_position_x = 0;	//Ŀ�������
uint8_t target_position_y = 0;	//Ŀ��������
uint8_t IsHD=1;									//�Ƿ�ʹ��ģ��Ҷȡ�
uint8_t Obstacle=0;						//�ϰ���λ��
uint16_t Distance=0;					//�����״�����
uint8_t stopping=0;				  //�����Ƿ�ֹͣ
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
			TIM5_Int_Init(35, 999); //1000HZ		PID����
			TIM7_Int_Init(35,999);	//1000HZ,    ȷ���ٶ�		
			begin();
			OLED_SHOW_MANU();
			TIM6_Int_Init(359, 9999);  //10HZ		·���滮��ȷ��nextx,nexty
			if(position_x==1&&position_y==2)//�����ʼλ��
			{
			 while(1)
			 {
					//remoteAction();						//ң����ָ�������
				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��
				 if(patrolStatus!=19)					//Ѳ�ӳ��أ����ϰ���
					 patrol();
				 if(!stopping&&!IsRemote)
					 MOVE(nextx,nexty);
			 }
		 }
}


