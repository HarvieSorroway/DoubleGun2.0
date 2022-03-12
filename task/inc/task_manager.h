#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H

#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"

#include "frame.h"

#include "test_task.h"

#define MaxNumOfTask     20

//�������ȼ�����
#define StartTask_PRIO   1
#define PIDCaculate_PRIO 2

//���������С����
#define	Min_STK_Size     32
#define	Regular_STK_Size 128
#define	Big_STK_Size     256
#define	Max_STK_Size     512


//�����ʼ���ṹ��
typedef struct initLink{
	TaskFunction_t  functionPointer;	//������
	char*           taskName;			//��������
	uint16_t        task_STK_Size;		//�����ڴ��С
	void (*pidDebugPointer)(void);	//pid����ģʽ����ָ��
} taskCreateStruct;	


//pid��ʼ��������
typedef struct initParams{
	float* Chassis_Speed_Position;//�����ٶȻ�-λ����
	float* Chassis_Current_Position;//���̵�����-λ����
}InitParams;


//�����ʼ���б�,��Ա�ɸ����������ж���
extern taskCreateStruct taskInitArray[MaxNumOfTask];
extern InitParams pidInitParams;


void TaskInit(void);
void start_task(void *pvParameters);
void AddInitFunction(taskCreateStruct aim);

#endif
