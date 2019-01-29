#include "remote.h"
uint8_t sbus_rx_buffer[RC_FRAME_LENGTH]; //double sbus rx buffer to save data
REMOTE RC_CtrlData;
DMA_InitTypeDef DMA_InitStructure;
extern double required_vel;
void RC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
 	USART_DeInit(USART2);  //��λ����1

    //USART1_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 100000;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_Even;//żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    //l USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	//USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
		
		
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
		USART_DMACmd(USART2,USART_DMAReq_Rx,DISABLE);
		DMA_DeInit(DMA1_Channel6);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
		DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;  //DMA����ADC����ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sbus_rx_buffer;  //DMA�ڴ����ַ
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽��
		DMA_InitStructure.DMA_BufferSize = 18;  //DMAͨ����DMA����Ĵ�С
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ��Ϊ8λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ��Ϊ8λ
		
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//������ѭ��ģʽ��
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; //DMAͨ�� xӵ�������ȼ� 
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
		DMA_Init(DMA1_Channel6, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
		DMA_ClearFlag(DMA1_FLAG_TC6); //���DMA������ɱ�־
		DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);//DMA5��������ж�
		USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);//ʹ��USART2�Ľ���DMA����
		

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	DMA_Cmd(DMA1_Channel6, ENABLE);         	
		
		
		
		
		
		
		
		
		
		
}

/******************************************************************************
* @fn RemoteDataProcess
** @brief resolution rc protocol data.
* @pData a point to rc receive buffer.
* @return None.
* @note RC_CtrlData is a global variable.you can deal with it in other place.
*/
void RemoteDataProcess(uint8_t *pData)
{
	if(pData == NULL)
	{
		return;
	}
	RC_CtrlData.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
	RC_CtrlData.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5))& 0x07FF;
	RC_CtrlData.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF;
	RC_CtrlData.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) &0x07FF;
	RC_CtrlData.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	RC_CtrlData.s2 = ((pData[5] >> 4) & 0x0003);
//	if(RC_CtrlData.ch0<1400&&RC_CtrlData.ch0>600)
//		required_vel=(double)(RC_CtrlData.ch0 -1024)*0.0025;	

}


void DMA1_Channel6_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC6)) //ͨ��5��������ж�TC ���д��� �����ж�HT �����ж�TE ȫ���ж�GL
     {
        DMA_ClearITPendingBit(DMA1_IT_GL6);    //���ȫ���жϱ�־
				RemoteDataProcess(sbus_rx_buffer);
     }
}
