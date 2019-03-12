#ifndef motor_h
#define motor_h
#include "include.h"
#include "pid.h"
void CAN_Mode_Init(void);

void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq);


typedef struct
{
	int16_t now_speed;			//��ǰת��
	int16_t target_speed;		//Ŀ��ת��
}Motor;//speed��λRPM

extern Motor* motor1;
extern Motor* motor2;
extern Motor motor3;
extern Motor motor4;
extern Motor yt_motor1;
extern Motor yt_motor2;
#endif
