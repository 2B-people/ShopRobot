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
				required_vel=0;
				stopping = 1;
			}
			else if(stopping)								//���յ���ʼ�ź�
			{
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
	if(IsRotate==0)
	{
		motor1.target_speed = get_RPM(required_vel);
		motor2.target_speed = get_RPM(required_vel);
	}
	if(IsHD&&IsRotate==0)
	{
			adcjihe();											//adc��������
			HuiduPidCalcuation();						//����adc��ֵ
			if(required_vel!=0)
			{
				motor1.target_speed += huidu_PID.pid_out;
				motor2.target_speed -= huidu_PID.pid_out;				
			}
	}
	
	
}
