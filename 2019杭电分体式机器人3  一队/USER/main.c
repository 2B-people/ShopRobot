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
void begin(void);
int main()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);    
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		SystemInit();
		initialise();
		memset(shelves,0,sizeof(shelves));
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			
			usart1_Init(115200);
			CAN_Mode_Init();
			Ledbeep_init();
			//RC_Init();
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
			LED1=0;
			delay(500);
			LED1=1;
			delay(500);
			LED1=0;
			begin();
			OLED_SHOW_MANU();
			TIM6_Int_Init(35, 999);  //10HZ		·���滮��ȷ��nextx,nexty
			LED1=1;
			
//			
//			position_x=2;
//			position_y=4;
//			orientation=positive_y ;		//����ץȡ
//			toFetch();
			
			 
			mode=1;
			while(1)								//��ʼ
			{
				waitingStop();
				if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				if(position_x==0&&position_y==3)
					break;
			}
			IsHD=1;
			mode=2;
			 while(1)									//Ѳ��
			 {
					//remoteAction();						//ң����ָ�������
				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��				
				 patrol(); 										 //Ѳ�ӳ��أ����ϰ���
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 if(patrolStatus==19)
					 break;
			 }
			 while(1)
			 {
				 OLED_SHOW_MANU();
			 }
			 mode=4;
			 while(1)									//����
			 {
				 	//remoteAction();						//ң����ָ�������
				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��				
				 if(!stopping&&!IsRemote&&!IsFetch)
					 MOVE(nextx,nexty);
				 else if(IsFetch&&!stopping&&!IsRemote)
					 toFetch();
			 }
}


