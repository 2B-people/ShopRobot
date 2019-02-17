#include "bottom_sensor.h"
void infrared_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(infrared_CLK1,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(infrared_PORT1, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(infrared_CLK2,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(infrared_PORT2, &GPIO_InitStructure);

	 	RCC_APB2PeriphClockCmd(infrared_CLK3,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(infrared_PORT3, &GPIO_InitStructure);

	 RCC_APB2PeriphClockCmd(infrared_CLK4,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(infrared_PORT4, &GPIO_InitStructure);
	
		 RCC_APB2PeriphClockCmd(infrared_CLK5,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_InitStructure.GPIO_Pin  = infrared_PIN5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(infrared_PORT5, &GPIO_InitStructure);
}
void ChangeCoordinate()
{
	static uint8_t flag=0;
	if(flag==0&&infrared1==BLACK&&infrared2==BLACK&&infrared3==BLACK&&infrared4==BLACK)
	{
		Beep_On_Off(False);
		flag=1;
	}
	if(flag==1&&((infrared1==WHITE&&infrared2==WHITE)||(infrared3==WHITE&&infrared4==WHITE)))
	{
		Beep_On_Off(True);
		switch(orientation)
		{
			case positive_x:if(required_vel>0) position_x+=1;else if(required_vel<0)position_x-=1;break;
			case positive_y:if(required_vel>0) position_y+=1;else if(required_vel<0)position_y-=1;break;
			case negative_x:if(required_vel>0) position_x-=1;else if(required_vel<0)position_x+=1;break;
			case negative_y:if(required_vel>0) position_y-=1;else if(required_vel<0)position_y+=1;break;
		}
		flag=0;
	}
}

void ROTATE(uint8_t Clockwise)//��ת��  ,1 ��˳ʱ��
{
	required_vel=0;
	
	IsRotate=1;	
	switch(Clockwise)
	{
		case 0:
			motor1.target_speed=-get_RPM(0.2);
			motor2.target_speed=get_RPM(0.2);
		break;
		case 1:
			motor1.target_speed=get_RPM(0.2);
			motor2.target_speed=-get_RPM(0.2);
		break;
	}
	delay(720);
	switch(Clockwise)
	{
		case 0:
		if(orientation!=0)
			orientation--;
		else
			orientation=3;
		break;
		case 1:
		if(orientation!=3)
			orientation++;
		else
			orientation=0;	
		break;
	}
	motor1.target_speed=get_RPM(required_vel);
	motor2.target_speed=get_RPM(required_vel);
	IsRotate=0;
	
}
void toFetch(void)
{
	if(position_x==0)
	{
		while(orientation!=negative_x)
		{
			ROTATE(1);
			delay(10);
		}
	}
	else if(position_x==9)
	{
		while(orientation!=positive_x)
		{
			ROTATE(1);
			delay(10);
		}
	}	
	else if(position_y==9)
	{
		while(orientation!=positive_y)
		{
			ROTATE(1);
			delay(10);
		}
	}	
	else if(position_y==0)
	{
		while(orientation!=negative_y)
		{
			ROTATE(1);
			delay(10);
		}
	}
	
	required_vel=slow_vel;
	while(infrared5==1);
	required_vel=0;
	IsFetch=0;
}

