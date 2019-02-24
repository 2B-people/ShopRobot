#include "kinematics.h"
double get_RPM(double liner_vel_in)
{
		float circumference_=PI*WHEEL_DIAMETER;
		float liner_vel = liner_vel_in * 60;		//���ٶ�תΪm/min
		double retrun_speed=liner_vel*COUNTS_PER_REV/circumference_;//���ٶ�ת��Ϊ����ת��
		return retrun_speed;
}

void waitingStop()
{

	if((!stopping)||required_vel==0)
			{
				OLED_SHOW_MANU();
			}		 		
			if (IsStop)											//���յ�ֹͣ�ź�
			{
				switch(orientation)						//�ı䳵����
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
				stopping = 1;
			}
			else if(stopping)								//���յ���ʼ�ź�
			{
					stopping = 0;									
			}						
}
void decideSpeed(void)
{
	static uint8_t lsx;							
	static uint8_t lsy;
	

	
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
	if(required_vel>=fast_vel)					//�ٶȿ�ʱ������һ��PID
	{
		huidu_PID.Kp=hK_P;
		huidu_PID.Ki=hK_I;
		huidu_PID.Kd=hK_D;
		s_PIDcm1.error_sum=0;							//����������
		s_PIDcm2.error_sum=0;			
	}
	else
	{
		huidu_PID.Kp=0.55;
		huidu_PID.Ki=0;
		huidu_PID.Kd=0.02;
		s_PIDcm1.error_sum=0;							//��������
		s_PIDcm2.error_sum=0;			
	}
	if(IsRotate==0)
	{
		
		if(LsRotate&&position_x==lsx&&position_y==lsy)			//���ת���ߵĵ�һ������н�
		{
			required_vel=slow_vel;	
		}
		else if(LsRotate)																		
			LsRotate=0;
		lsx=position_x;																			
		lsy=position_y;																			//������һ������λ��
		
		motor1.target_speed = get_RPM(required_vel);
		motor2.target_speed = get_RPM(required_vel);
	}
	if(IsHD&&IsRotate==0)																	
	{
			adcjihe();											//adc��������
			HuiduPidCalcuation();						//����adc��ֵ
			if(required_vel>0)
			{
				motor1.target_speed += huidu_PID.pid_out;
				motor2.target_speed -= huidu_PID.pid_out;				
			}
	}
	
	
}
