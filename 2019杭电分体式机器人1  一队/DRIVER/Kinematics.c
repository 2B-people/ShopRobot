#include "kinematics.h"
uint8_t lsx;
uint8_t lsy;
float get_RPM(float liner_vel_in)
{
		float circumference_=PI*WHEEL_DIAMETER;
		float liner_vel = liner_vel_in * 60;		//���ٶ�תΪm/min
		double retrun_speed=liner_vel*COUNTS_PER_REV/circumference_;//���ٶ�ת��Ϊ����ת��
		return retrun_speed;
}

void waitingStop()
{

			OLED_SHOW_MANU();	 		
			if (IsStop&&!stopping)											//���յ�ֹͣ�ź�
			{
				switch(orientation)
				{
					case positive_x:
						target_position_x=position_x+1;
						target_position_y=position_y;
						path_cal();
						break;
					case negative_x:
						target_position_x=position_x-1;
						target_position_y=position_y;
						path_cal();
						break;
					case negative_y:
						target_position_x=position_x;
						target_position_y=position_y-1;
						path_cal();
						break;
					case positive_y:
						target_position_x=position_x;
						target_position_y=position_y+1;
						path_cal();
						break;
				}
				LED3=0;
				stopping = 1;
			}
			else if(!IsStop&&stopping)								//���յ���ʼ�ź�
			{
				LED3=0;
				dis=0;
				stopping = 0;									
			}						
}
void decideSpeed(void)
{	
	if(required_vel==0)
	{
		s_PIDcm1.error_sum=0;							//�ٶ�Ϊ0ʱ����������
		s_PIDcm2.error_sum=0;							
	}
	if(required_vel>=MaxVel)
	{
		required_vel=MaxVel;							
	}
	else if(required_vel<=-MaxVel)
	{
		required_vel=-MaxVel;
	}	
	if(required_vel>=fast_vel)
	{
		huidu_PID.Kd=hK_P;
		huidu_PID.Ki=hK_I;
		huidu_PID.Kd=hK_D;
	}
	else
	{
		huidu_PID.Kp=0.65;
		huidu_PID.Ki=0;
		huidu_PID.Kd=0.02;
	}
	if(IsRotate==0)		//��ת����
	{
		
		if(LsRotate&&position_x==lsx&&position_y==lsy&&!IsFetch&&(position_x!=target_position_x||position_y!=target_position_y))//�������ת�������ߵĵ�һ��
		{
			required_vel=slow_vel;	
		}
		else if(LsRotate)//��ת�����������һ��					
			LsRotate=0;
		
		

		
		motor1.target_speed = get_RPM(required_vel);	
		motor2.target_speed = get_RPM(required_vel);
	}
	
	
}
