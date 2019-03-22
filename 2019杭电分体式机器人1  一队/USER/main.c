#include "include.h"
#include "math.h"
#define car1
//////////key_PIN1   	//��
//////////key_PIN2  	//��
//////////key_PIN3  	//��
//////////key_PIN4  	//��
//////////key_PIN5  	//��
//////////key_PIN6  	//����

float required_vel = 0;
uint8_t IsControlFinsh; //�Ƿ����ָ������
uint8_t IsStop = 0;		//�Ƿ�ӵ���ͣ״̬�źŵı�־
uint8_t IsFetch = 0;
uint8_t position_x = 0;			  //��ǰ������
uint8_t position_y = 0;			  //��ǰ������
uint8_t orientation = positive_x; //��ǰ���ĳ���Ĭ�Ͽ�ʼΪy������
uint8_t target_position_x = 0;	//Ŀ�������
uint8_t target_position_y = 0;	//Ŀ��������
uint8_t target_orientation = positive_x;
uint8_t IsHD = 0;
;
;					   //�Ƿ�ʹ��ģ��Ҷȡ�
uint8_t Obstacle = 0;  //�ϰ���λ��
uint16_t Distance = 0; //�����״�����
uint8_t stopping = 0;  //�����Ƿ�ֹͣ
uint8_t mode = 0;
uint8_t shelves[12]; //C����
uint8_t Goods_num;
float pitch,roll,yaw; 		//ŷ����
void begin(void);

int main()
{
	mainCAMERA(); //����ͷ��  ��ʼ����(1,2) ��ʼ����+y
 //mainNOCAMERA(); //������ͷ��
	
}

void mainNOCAMERA(void)
{
	u8 success = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	SystemInit();
	//initialise();
	delay_init();
	memset(shelves, 0, sizeof(shelves));
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	Arm_Init(7199, 199);
	CAN_Mode_Init(); //��ʼ��CAN����
	Ledbeep_init();  //��ʼ��LED�ơ�������
	//RC_Init();
	OLED_Init();			//��ʼ��OLED
	las_Init();				//��ʼ�����ģ��
	PID_init();				//��ʼ��PID����
	huiductrlinit();		//��ʼ��ģ��Ҷ�
	infrared_Init();		//��ʼ���ײ���⴫����
	KEY_Init();				//��ʼ������
	OLED_Clear();			//���OLED��
	path_Init();			//��ʼ��·���滮����
	TIM5_Int_Init(35, 999); //1000HZ		PID����
	TIM7_Int_Init(35, 999); //1000HZ,    ȷ���ٶ�
	M8266HostIf_Init();
	success = M8266WIFI_Module_Init_Via_SPI();
	LED1 = 0;
	delay(500);
	LED1 = 1;
	delay(500);
	LED1 = 0;
	wifi_wait_begin();
	
	begin1(); //�����Ӻ�ɫ��������
//	MPU_Init();					//��ʼ��MPU6050
//	while(mpu_dmp_init());
	OLED_SHOW_MANU();
	TIM6_Int_Init(71, 99); //1000HZ		·���滮��ȷ��nextx,nexty 72m
	LED1 = 1;

	mode = 1;
	IsHD = 1;
	
	
	/*********************************************/
//	Arm_run();
//	orientation=positive_y;
//	position_x=7;
//	position_y=3;
//	toFetch(0,2);
//	toCoordinate(9,0);
//	while(1)
//	{
//		MOVE(nextx,nexty);
//		OLED_SHOW_MANU();
//		if(IsMoveFinsh==1)
//			break;
//	}
//	toFetch(100,0);
//	
	/************************************************/
	
	
	
	
	
	
	
	while (1) //Ѳ��
	{
		waitingStop(); //OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��
		patrol1();	 //Ѳ�ӳ��أ����ϰ���
		if (!stopping && !IsFetch && !IsMoveFinsh)
		{
			MOVE(nextx, nexty);
		}
		if (patrolStatus == 100)
			break;
	}
	
	
	success = wifi_finish();

	mode = 3;
	

	
	/******************************************/
//				toCoordinate(2,4);
//				while(1)
//			 {
//				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��
//				 if(!stopping&&!IsFetch)
//				 {
//					 MOVE(nextx,nexty);
//						OLED_SHOW_MANU();
//				 }
//				 if(position_x==2&&position_y==4)
//				 {
//					 LED3=0;
//					 break;
//				 }
//			 }
//			 toFetch(0,2);
//			 toCoordinate(0,0);
//			 while(1)
//			 {
//				 waitingStop();								//OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��
//				 if(!stopping&&!IsFetch)
//				 {
//					 MOVE(nextx,nexty);
//						OLED_SHOW_MANU();
//				 }
//				 if(position_x==0&&position_y==0)
//					 break;
//			 }
//			 toFetch(100,1);
	/*******************************/
	while (1) //����
	{
		wifi_connect();
		waitingStop(); //OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��
		if (!stopping && !IsFetch)
		{
			MOVE(nextx, nexty);
			sifi_send();
		}
		else if (IsFetch && !stopping)
		{
			toFetch(Goods_num, 1); //ץȡ
			wifi_finish();
		}
		if (IsMoveFinsh)
		{
			if (target_orientation != orientation)
			{
				switch (target_orientation)
				{
				case positive_x:
					while (orientation != positive_x)
					{
						if (orientation == negative_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case positive_y:
					while (orientation != positive_y)
					{
						if (orientation == positive_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_x:
					while (orientation != negative_x)
					{
						if (orientation == positive_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_y:
					while (orientation != negative_y)
					{
						if (orientation == negative_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				}
			}
		}
	}
}

void mainCAMERA(void)
{
	u8 success = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	SystemInit();
	//initialise();
	delay_init();
	memset(shelves, 0, sizeof(shelves));
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_Init(115200);
	Arm_Init(7199, 199);
	CAN_Mode_Init(); //��ʼ��CAN����
	Ledbeep_init();  //��ʼ��LED�ơ�������
	//RC_Init();
	OLED_Init();			//��ʼ��OLED
	las_Init();				//��ʼ�����ģ��
	PID_init();				//��ʼ��PID����
	huiductrlinit();		//��ʼ��ģ��Ҷ�
	infrared_Init();		//��ʼ���ײ���⴫����
	KEY_Init();				//��ʼ������
	OLED_Clear();			//���OLED��
	path_Init();			//��ʼ��·���滮����
	TIM5_Int_Init(35, 999); //1000HZ		PID����
	TIM7_Int_Init(35, 999); //1000HZ,    ȷ���ٶ�
	M8266HostIf_Init();
	success = M8266WIFI_Module_Init_Via_SPI();
	LED1 = 0;
	delay(500);
	LED1 = 1;
	delay(500);
	LED1 = 0;

	//����ָ��
	wifi_wait_begin();
	begin1(); //�����Ӻ�ɫ��������
	position_x = 1;
	position_y = 2;
	target_position_x = 1;
	target_position_y = 2;
	nextx = 1;
	nexty = 2;
	TIM6_Int_Init(71, 99); //1000HZ		·���滮��ȷ��nextx,nexty 72m
	sifi_send();
	delay(10);
	success = wifi_finish();
	LED1 = 1;
	mode = 1;
	IsHD = 1;

	while (1) //����
	{
		wifi_connect();
		waitingStop(); //OLED�˵���ʾ���ȴ��Ϸ�����ָֹͣ��
		if (!IsFetch)
		{
			MOVE(nextx, nexty);
			sifi_send();
		}
//		else if (IsFetch && !stopping)
//		{
//			toFetch(Goods_num, 1); //ץȡ
//			wifi_finish();
//		}
		if (IsMoveFinsh)
		{
			if (target_orientation != orientation)
			{
				switch (target_orientation)
				{
				case positive_x:
					while (orientation != positive_x)
					{
						if (orientation == negative_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case positive_y:
					while (orientation != positive_y)
					{
						if (orientation == positive_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_x:
					while (orientation != negative_x)
					{
						if (orientation == positive_y)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				case negative_y:
					while (orientation != negative_y)
					{
						if (orientation == negative_x)
							ROTATE(0);
						else
							ROTATE(1);
					}
					break;
				}
			}
		}
	}
}
