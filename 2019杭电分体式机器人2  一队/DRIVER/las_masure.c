#include "las_masure.h"
uint16_t USART_RX_STA=0;
uint16_t USART_RX_NUM=0;
uint8_t MEASURE_BUF[5];
uint8_t Distance_data[5];
uint8_t USART3_BUFF[8];
uint8_t las_mode;

void las_Init()
{
		USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;   
    GPIO_InitTypeDef GPIO_InitStructure;    //����һ���ṹ�������������ʼ��GPIO  
		DMA_InitTypeDef DMA_InitStructure;	
		
    //ʹ�ܴ��ڵ�RCCʱ��  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE); //ʹ��UART3����GPIOB��ʱ��  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  
		USART_DeInit(USART3);
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
	
		    //���ô���  
    USART_InitStructure.USART_BaudRate = 115200;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx ;//ֻ��Ҫ���ܣ�����Ҫ����  
		
		

    USART_Init(USART3, &USART_InitStructure);//���ô���3 
   
    USART_Cmd(USART3, ENABLE);//ʹ�ܴ���3  
		
		
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                      //ʹ��DMA1ʱ��  
		USART_DMACmd(USART3, USART_DMAReq_Rx, DISABLE);  //ʹ�ܴ���3 DMA����

		DMA_DeInit(DMA1_Channel3);                                              //��ʼ��DMA1ͨ��3  ����3����ͨ��
		DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART3->DR;                  //����3�������ݵĵ�ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART3_BUFF;      //���ݴ�ŵĸ���
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //���ݴ��ͷ���  ����3��Ϊ����Դ
		DMA_InitStructure.DMA_BufferSize = 8;                    //�������ݸ���       
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //��Χ�豸 ����3 ��ַ������
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // DMA�洢��ַ����
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //��Χ�豸 ����3 ���ݿ�� 8bits
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //DMA�洢 ���ݿ�� 8bits
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //ѭ����ȡ����
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   //����3ͨ������Ϊ�е�
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //�ر��ڴ浽�ڴ�
		DMA_Init(DMA1_Channel3, &DMA_InitStructure);
		DMA_ClearFlag(DMA1_FLAG_TC3); //���DMA������ɱ�־
		DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);//DMA5��������ж�
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);//ʹ��USART2�Ľ���DMA����
		 		
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		DMA_Cmd(DMA1_Channel3, ENABLE);         	
}


void las_measure(uint8_t *Distance_data)
{
	static uint16_t distance;
	static uint16_t strength;
	distance&=0X0000;
	distance|=(((int16_t)Distance_data[2])&0x00FF);
	distance|=((((int16_t)Distance_data[3])<<8)&0xFF00);
	strength&=0X0000;
	strength|=(((int16_t)Distance_data[4])&0x00FF);
	strength|=((((int16_t)Distance_data[5])<<8)&0xFF00);
	
	
	if(strength>20&&strength<2000&&distance>=30&&distance<=1200)		//ֻ�е��ź���һ��ǿ���ڣ����ݲ��ǿ��ŵ�
	{
		Distance=distance;
	}
}
	

//void USART3_IRQHandler(void)                    //����3�жϷ������
//{
//    static uint8_t Res;
//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
//		{
//			
//			Res=USART_ReceiveData(USART3);
//			if((USART_RX_STA&0x2000)!=0)		//���ܾ�������
//			{
//				MEASURE_BUF[USART_RX_NUM++]=Res;
//				if(USART_RX_NUM==5)
//				{
//					Distance_data[0]=MEASURE_BUF[0];
//					Distance_data[1]=MEASURE_BUF[1];
//					Distance_data[2]=MEASURE_BUF[2];
//					Distance_data[3]=MEASURE_BUF[3];
//					Distance_data[4]=MEASURE_BUF[4];
//					USART_RX_NUM=0;
//					USART_RX_STA=0;
//				}
//			}
//			else if((USART_RX_STA&0x1000)!=0)//�ڶ�����ʼλ
//			{
//				if(Res==0x59)USART_RX_STA|=0x2000;
//				else USART_RX_STA=0;
//			}
//			else if(Res==0x59)USART_RX_STA|=0x1000;//��һ����ʼλ
//		}
//		USART_ClearITPendingBit(USART3, USART_IT_RXNE);

//}
void DMA1_Channel3_IRQHandler(void)
{
		  if(DMA_GetITStatus(DMA1_IT_TC3)) //ͨ��5��������ж�TC ���д��� �����ж�HT �����ж�TE ȫ���ж�GL
     {
        DMA_ClearITPendingBit(DMA1_IT_GL3);    //���ȫ���жϱ�־
				las_measure(USART3_BUFF);
     }
}

