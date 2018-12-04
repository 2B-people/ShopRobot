#include "las_measure.h"
#include "config.h"
#include "HardwareSerial.h"
uint16_t USART_RX_STA=0;
uint16_t USART_RX_NUM=0;
uint16_t Distance;
uint8_t MEASURE_BUF[5];
extern HardwareSerial usart1;

void las_Init()
{
		USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;    //����һ���ṹ�������������ʼ��GPIO  
    //ʹ�ܴ��ڵ�RCCʱ��  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //ʹ��UART3����GPIOB��ʱ��  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  

    //����ʹ�õ�GPIO������  
    // Configure USART3 Rx (PB.11) as input floating    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

    // Configure USART3 Tx (PB.10) as alternate function push-pull  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
		// ����ѡ��1
		RCC_APB2PeriphClockCmd(CHOSE_LAS_CLK1,ENABLE);
    GPIO_InitStructure.GPIO_Pin = CHOSE_LAS_PIN1;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(CHOSE_LAS_PORT1, &GPIO_InitStructure); 
		
			// ����ѡ��2
		RCC_APB2PeriphClockCmd(CHOSE_LAS_CLK2,ENABLE);
    GPIO_InitStructure.GPIO_Pin = CHOSE_LAS_PIN2;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(CHOSE_LAS_PORT2, &GPIO_InitStructure); 
		
    //���ô���  
    USART_InitStructure.USART_BaudRate = 115200;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx ;//ֻ��Ҫ���ܣ�����Ҫ����  


    // Configure USART3   
    USART_Init(USART3, &USART_InitStructure);//���ô���3 
    // Enable USART3 Receive interrupts ʹ�ܴ��ڽ����ж�  
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  
    // Enable the USART3   
    USART_Cmd(USART3, ENABLE);//ʹ�ܴ���3  

    //�����ж�����  
    //Configure the NVIC Preemption Priority Bits     
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  

    // Enable the USART3 Interrupt   
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);       
}
void changeDirection(direction dir)//������ѡ����ѡ�񴮿ڵĽӿ���ѡ�񼤹���
{
	switch(dir)
	{
		case FORWARD:
			GPIO_ResetBits(CHOSE_LAS_PORT1,CHOSE_LAS_PIN1);
			GPIO_ResetBits(CHOSE_LAS_PORT2,CHOSE_LAS_PIN2);		//00
			break;
		case BACK:
			GPIO_ResetBits(CHOSE_LAS_PORT1,CHOSE_LAS_PIN1);
			GPIO_SetBits(CHOSE_LAS_PORT2,CHOSE_LAS_PIN2);			//01
			break;
		case LEFT:
			GPIO_SetBits(CHOSE_LAS_PORT1,CHOSE_LAS_PIN1);
			GPIO_ResetBits(CHOSE_LAS_PORT2,CHOSE_LAS_PIN2);			//10
			break;
		case RIGHT:
			GPIO_SetBits(CHOSE_LAS_PORT1,CHOSE_LAS_PIN1);
			GPIO_SetBits(CHOSE_LAS_PORT2,CHOSE_LAS_PIN2);			//11
			break;
	}
	//USART_RX_STA=0;
}

void las_measure()
{
	uint16_t distance;
	uint16_t strength;
	uint8_t mode;
	while(USART_RX_STA!=0);
	while(USART_RX_STA==0x2000);//�ȴ��������ݽ���
	distance&=0X0000;
	distance|=((uint16_t(MEASURE_BUF[0]))&0x00FF);
	distance|=(((uint16_t(MEASURE_BUF[1]))<<8)&0xFF00);
	strength&=0X0000;
	strength|=((uint16_t(MEASURE_BUF[2]))&0x00FF);
	strength|=(((uint16_t(MEASURE_BUF[3]))<<8)&0xFF00);
	
	mode&=0x00;
	mode|=MEASURE_BUF[4];		//0x02������ 0x07Զ����
	
	if(strength>20&&strength<2000)		//ֻ�е��ź���һ��ǿ���ڣ����ݲ��ǿ��ŵ�
		Distance=distance;
	
}



uint16_t las_data(direction dir)
{
	changeDirection(dir);
	las_measure();

	return Distance;
}





extern "C" void USART3_IRQHandler(void)                    //����3�жϷ������
{
    uint8_t Res;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
		{
			Res=USART_ReceiveData(USART3);
			if((USART_RX_STA&0x2000)!=0)		//���ܾ�������
			{
				MEASURE_BUF[USART_RX_NUM++]=Res;
				if(USART_RX_NUM==5)
				{
					USART_RX_NUM=0;
					USART_RX_STA=0;
				}
			}
			else if((USART_RX_STA&0x1000)!=0)//�ڶ�����ʼλ
			{
				if(Res==0x59)USART_RX_STA|=0x2000;
				else USART_RX_STA=0;
			}
			else if(Res==0x59)USART_RX_STA|=0x1000;//��һ����ʼλ
		}
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);

}