#ifndef KEY_H
#define KEY_H

#include "include.h"

#define KEY1_PRES 	1	//KEY1����
#define KEY2_PRES  	2	//KEY2����
#define KEY3_PRES 	3	//KEY3����
#define KEY4_PRES   4	//KEY4����
#define KEY5_PRES   5	//KEY5����
#define KEY6_PRES	  6	//KEY6����

#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)//��ȡ����2
#define KEY3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)//��ȡ����3 
#define KEY4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//��ȡ����4
#define KEY5  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)//��ȡ����5
#define KEY6  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)//��ȡ����6 

u8 KEY_Scan(u8 mode);
void KEY_Init(void); //IO��ʼ��
	
#endif
