#ifndef _plan_h
#define _plan_h
#include "include.h"
void MOVE(uint8_t _target_position_x,uint8_t _target_position_y);
void ROTATE(uint8_t Clockwise);//ClockwiseΪ1˳ʱ��
void move_control(void);
extern uint8_t IsMoveFinsh;
extern uint8_t IsRotate;



#endif

