#include "kinematics.h"
//float speed[4];
double get_RPM(double liner_vel_in)
{
		float circumference_=PI*WHEEL_DIAMETER;
		float liner_vel = liner_vel_in * 60;		//���ٶ�תΪm/min
		double retrun_speed=liner_vel*COUNTS_PER_REV/circumference_;//���ٶ�ת��Ϊ����ת��
		return retrun_speed;
}

void stop_base()
{
	required_vel=0;
	
}
