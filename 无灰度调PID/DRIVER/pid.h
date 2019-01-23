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

struct PID_member
{
	double Kp;
	double Ki;
	double Kd;
	int16_t error_now;
	int16_t error_last;
	int16_t error_inter;
	int16_t error_sum;
	int16_t pid_out;
	int16_t pid_out_last;
	int16_t pid_out_inter;
};

extern struct PID_member s_PIDcm1, s_PIDcm2, huidu_PID;

void PID_init(void);

void HuiduPidCalcuation(void);
void CM2speedPID_Calculation(void);
void CM1speedPID_Calculation(void);
void CMControl(void);
#endif
