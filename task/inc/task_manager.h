#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H

#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"

#include "frame.h"

#include "test_task.h"

#define MaxNumOfTask     20

//任务优先级定义
#define StartTask_PRIO   1
#define PIDCaculate_PRIO 2

//任务区块大小设置
#define	Min_STK_Size     32
#define	Regular_STK_Size 128
#define	Big_STK_Size     256
#define	Max_STK_Size     512


//任务初始化结构体
typedef struct initLink{
	TaskFunction_t  functionPointer;	//任务函数
	char*           taskName;			//函数名称
	uint16_t        task_STK_Size;		//任务内存大小
	void (*pidDebugPointer)(void);	//pid调试模式函数指针
} taskCreateStruct;	


//pid初始化参数表
typedef struct initParams{
	float* Chassis_Speed_Position;//底盘速度环-位置形
	float* Chassis_Current_Position;//底盘电流环-位置形
}InitParams;


//任务初始化列表,成员由各个任务自行定义
extern taskCreateStruct taskInitArray[MaxNumOfTask];
extern InitParams pidInitParams;


void TaskInit(void);
void start_task(void *pvParameters);
void AddInitFunction(taskCreateStruct aim);

#endif
