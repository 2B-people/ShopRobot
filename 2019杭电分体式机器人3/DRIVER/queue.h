#ifndef queue_h
#define queue_h
#include "include.h"
#define datatype int8_t
#define EN 1000
typedef struct Queue {
	int front;//��ͷ
	int endline;//��β
	datatype data[EN];//����
}queue;
void initQueue(queue *pque);
void enQueue(queue *pque, datatype data) ;
void deQueue(queue *pque);

#endif
