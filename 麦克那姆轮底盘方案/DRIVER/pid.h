#ifndef _pid_h
#define _pid_h
#include "include.h"

typedef struct
{
	float SetSpeed; //�����趨ֵ
	float ActualSpeed;//����ʵ��ֵ
	float err; //����ƫ��ֵ
	float err_last; //������һ��ƫ��ֵ
	float Kp,Ki,Kd; //������������֡�΢��ϵ��
	float voltage; //�����ѹֵ������ִ�����ı�����
	float integral; //�������ֵ
}pid;
void PID_init(void);


void CM2speedPID_Calculation(void);
void CM4speedPID_Calculation(void);
void CM1speedPID_Calculation(void);
void CM3speedPID_Calculation(void);
void CMControl(void);
#endif
