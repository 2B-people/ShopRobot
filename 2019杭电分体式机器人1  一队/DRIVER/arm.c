#include "arm.h"

int16_t up_dowm=0;												//�ǶȼӼ���־					

int16_t now_angle_[3]={7030,6646,6280};			//�Ƕȳ�ʼ�������1~3

int16_t init=6316;															//now_angle_[1]-330

int16_t taitou=6660;														//floor_[0]+240

int16_t floor_[2]={6420,6900};							//����1��2�����

int16_t rid_speed=3;												//����ٶ�

int16_t goods[12]={6320,6320,6320,6310,6290,6298,6325,6320,6320,6315,6340,6325}; 		 				//ץ����
								// ���� ���� ���� ˬ�� ���� AD�� ѩ�� ��ţ �ֻ� ���� ħ�� ������

int16_t give_goods=6650;										//�Ż���



					//      7199    199    50hz
void Arm_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); 
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
 

	TIM_CtrlPWMOutputs(TIM2,ENABLE);	
	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);  
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable); 


	TIM_ARRPreloadConfig(TIM2,ENABLE); 
	
	TIM_Cmd(TIM2,ENABLE);  
	
	TIM_SetCompare1(TIM2,now_angle_[0]);
	TIM_SetCompare2(TIM2,now_angle_[1]);
	TIM_SetCompare3(TIM2,now_angle_[2]);
}



void Arm_run()
{
	if((give_goods-now_angle_[2])>0)
		up_dowm=1;
	else
		up_dowm=-1;
	
	for(;now_angle_[2]!=give_goods;now_angle_[2]+=up_dowm)		
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);																			//�򿪻�е��
	}	
	
	for(;now_angle_[1]!=init;now_angle_[1]-=1)
	{
		delay(rid_speed);
		TIM_SetCompare2(TIM2,now_angle_[1]);															
	}	
	
	if((floor_[0]-now_angle_[0])>0)
		up_dowm=1;

	else
		up_dowm=-1;

	for(;now_angle_[0]!=floor_[0];now_angle_[0]+=up_dowm,now_angle_[1]-=up_dowm)
	{
		delay(rid_speed);
		TIM_SetCompare1(TIM2,now_angle_[0]);
		TIM_SetCompare2(TIM2,now_angle_[1]);																			//����һ��
	}	
}


void Com_run()
{
	if((give_goods-now_angle_[2])>0)
		up_dowm=1;
	else
		up_dowm=-1;
	
	for(;now_angle_[2]!=give_goods;now_angle_[2]+=up_dowm)		
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);																			//�򿪻�е��
	}	
	
	if((floor_[0]-now_angle_[0])>0)
		up_dowm=1;

	else
		up_dowm=-1;

	for(;now_angle_[0]!=floor_[0];now_angle_[0]+=up_dowm,now_angle_[1]-=up_dowm)
	{
		delay(rid_speed);
		TIM_SetCompare1(TIM2,now_angle_[0]);
		TIM_SetCompare2(TIM2,now_angle_[1]);																			//����һ��
	}	
}


void Get_goods(int16_t goods_num)
{
											
	if((goods[goods_num]-now_angle_[2])>0)
		up_dowm=1;
	else
		up_dowm=-1;
	
	for(;now_angle_[2]!=goods[goods_num];now_angle_[2]+=up_dowm)
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);
	}																																						//ץȡָ������0~11
																
}



void Goods_floor(int16_t floor_num)
{
	int16_t i=0;
	if(floor_num==0)
	{
		for(;now_angle_[0]!=floor_[0]+10;now_angle_[0]+=1,now_angle_[1]-=1)
		{
			delay(rid_speed);
			TIM_SetCompare1(TIM2,now_angle_[0]);
			TIM_SetCompare2(TIM2,now_angle_[1]);
		}
	}
	else
	{
		if(floor_num ==1)
		{
			if((floor_[1]-now_angle_[0])>0)
				up_dowm=1;

			else
				up_dowm=-1;

			for(;now_angle_[0]!=(floor_[1]+floor_[0])/2;now_angle_[0]+=up_dowm)
			{
				delay(rid_speed);
				TIM_SetCompare1(TIM2,now_angle_[0]);
			}											
																													//����ָ������
			for(;now_angle_[0]!=floor_[1];now_angle_[0]+=up_dowm,now_angle_[1]-=up_dowm)
			{
				delay(rid_speed);
				TIM_SetCompare1(TIM2,now_angle_[0]);
				TIM_SetCompare2(TIM2,now_angle_[1]);
			}																											//�������Ĳ�0~1
			for(i=0;i!=(floor_[1]-floor_[0])/2;i++,now_angle_[1]-=up_dowm)
			{
				delay(rid_speed);
				TIM_SetCompare2(TIM2,now_angle_[1]);
			}
		}
		else
		{
			if((floor_[0]-now_angle_[0])>0)
				up_dowm=1;

			else
				up_dowm=-1;

			for(;now_angle_[0]!=floor_[0];now_angle_[0]+=up_dowm,now_angle_[1]-=up_dowm)
			{
				delay(rid_speed);
				TIM_SetCompare1(TIM2,now_angle_[0]);
				TIM_SetCompare2(TIM2,now_angle_[1]);																			//����һ��
			}	
		}
	}
}




void Give_goods()
{
	if((give_goods-now_angle_[2])>0)
		up_dowm=1;
	else
		up_dowm=-1;
	
	for(;now_angle_[2]!=give_goods;now_angle_[2]+=up_dowm)		
	{
		delay(rid_speed);
		TIM_SetCompare3(TIM2,now_angle_[2]);
	}																																						//�ſ�����
}






