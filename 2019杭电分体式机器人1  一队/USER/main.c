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
uint8_t IsFetch=0;
uint8_t position_x = 0;			  //��ǰ������
uint8_t position_y = 0;			  //��ǰ������
uint8_t orientation=positive_y ; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪy������
uint8_t target_position_x = 0;	//Ŀ�������
uint8_t target_position_y = 0;	//Ŀ��������
uint8_t IsHD=0;                                               ;                                                                                                                                                                                                                                                                                                                                                                                                 ;									//�Ƿ�ʹ��ģ��Ҷȡ�
uint8_t Obstacle=0;						//�ϰ���λ��
uint16_t Distance=0;					//�����״�����
uint8_t stopping=0;				  //�����Ƿ�ֹͣ
uint8_t mode=0;
uint8_t shelves[12];				//C����
uint8_t Goods_num;
void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);    
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		SystemInit();
		initialise();
		delay(1000);
		memset(shelves,0,sizeof(shelves));
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
			usart1_Init(115200);
			Arm_Init(7199,199);
			CAN_Mode_Init();			//��ʼ��CAN����
			Ledbeep_init();				//��ʼ��LED�ơ�������
			//RC_Init();	
			OLED_Init(); 					//��ʼ��OLED
			las_Init();						//��ʼ�����ģ��
			PID_init();						//��ʼ��PID����
			huiductrlinit();			//��ʼ��ģ��Ҷ�
			infrared_Init();			//��ʼ���ײ���⴫����
			KEY_Init();						//��ʼ������
			OLED_Clear();					//���OLED��
			path_Init();					//��ʼ��·���滮����
			TIM5_Int_Init(35, 999); //1000HZ		PID����
			TIM7_Int_Init(35,999);	//1000HZ,    ȷ���ٶ�		
			LED1=0;
			delay(500);
			LED1=1;
			delay(500);
			LED1=0;

			
			begin();								//�����Ӻ�ɫ��������
			OLED_SHOW_MANU();
			TIM6_Int_Init(71, 999);  //1000HZ		·���滮��ȷ��nextx,nexty 72m
			LED1=1;

			mode=1;	
			IsHD=1;
			 while(1)									//Ѳ��
			 {				
				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��				
				 patrol(); 										 //Ѳ�ӳ��أ����ϰ���
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 if(patrolStatus==19)
					 break;
			 }
			 mode=3;		

/********************************************************/			 
			 toFetch(100,1);
			 target_position_x=5;
			 target_position_y=7;
			 path_cal();			 
			 while(1)									//����
			 {					
				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��				
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 if(position_x==5&&position_y==7)
					 break;
			 }
			 toFetch(0,0);
			 while(1)
			 {
				 OLED_SHOW_MANU();
			 }
			 
/**********************************************************/	 
			 while(1)									//����
			 {					
				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��				
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 else if(IsFetch&&!stopping&&!IsRemote)
					 toFetch(Goods_num,1);									//ץȡ
			 }
}


