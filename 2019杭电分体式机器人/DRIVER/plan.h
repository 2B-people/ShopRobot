#ifndef _plan_h
#define _plan_h
#include "include.h"
void MOVE(uint8_t _target_position_x,uint8_t _target_position_y);
void ROTATE(uint8_t Clockwise);//ClockwiseΪ1˳ʱ��
void move_control(void);
extern uint8_t IsMoveFinsh;
extern uint8_t IsRotate;

#define fast_vel 0.5		//һ������³���
#define slow_vel 0.1		//���ӻ�������״̬����ͳ���
#define down_vel 0.0005	//�ﵽ���һ��ʱ��ÿ�����ڼ��µ��ٶ�

#endif

