#include "queue.h"

void initQueue(queue *pque)
{
	pque->front = pque->endline = 0;//��ն���
}
//���
void enQueue(queue *pque, datatype data) 
{
	//�ж϶����Ƿ����
	if (pque->endline < EN)
	{
		//�ж϶����Ƿ�Ϊ��
		if (pque->front == pque->endline)//��ͷ�Ͷ�β�غϱ���û��Ԫ��
		{
			//��ʼ������
			initQueue(pque);
		}
		pque->data[pque->endline] = data;
		pque->endline += 1;
	}
	else		
	{
		return;
	}

}
//����
void deQueue(queue *pque)
{
	//�ж϶����Ƿ�Ϊ��
	if (pque->front == pque->endline)
	{
		//����Ϊ��
		return;
	}
	else {
		//ֱ�ӵ������һ��
		pque->front += 1;
	}
}
