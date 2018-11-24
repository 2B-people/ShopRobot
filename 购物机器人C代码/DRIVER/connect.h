#ifndef _connect_h
#define _connect_h
#include "include.h"
typedef struct
{
	uint8_t Type_L;
	uint8_t Type_H;
	uint8_t Date_1;
	uint8_t Date_2;
	uint8_t Date_3;
	uint8_t Date_4;
}Connect_Typedef;
extern Connect_Typedef connectMicorw2PC;
void Set_Type(Connect_Typedef co,uint16_t type);
void Set_Data(Connect_Typedef co,uint32_t data);
void Send_Message(Connect_Typedef co);
void publish_vel(void);
void publish_remote(void);
void publish_las(void);
#define MSG_vel_x         0X0001
#define MSG_vel_y         0X0002
#define MSG_vel_z         0X0003
#define MSG_distance_f    0X0004		//ǰ����
#define MSG_distance_b    0X0005		//�����
#define MSG_distance_l    0X0006		//�����
#define MSG_distance_r    0X0007		//�Ҿ���
#define MSG_remote_ch0    0x0008   //ң����ch0
#define MSG_remote_ch1    0x0008   //ң����ch1
#define MSG_remote_ch2    0x0009   //ң����ch2
#define MSG_remote_ch3    0x000A   //ң����ch3
#define MSG_remote_s1     0x000B   //ң����s1
#define MSG_remote_s2     0x000C   //ң����s2
#endif
