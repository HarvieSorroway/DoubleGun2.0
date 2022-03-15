#include "task_manager.h"

TaskHandle_t Start_Task_Handler;
TaskHandle_t test_Task_Handler;
InitParams pidInitParams;

//任务初始化列表,成员由各个任务自行定义
taskCreateStruct taskInitArray[MaxNumOfTask];

//记录共有多少个任务需要创建
int MaxNum = 0;
	
void TaskInit(void)
{		
	test_task_Init();
	frame_task_init();
	
	xTaskCreate((TaskFunction_t)start_task,
                (char*         )"start_task",
                (uint16_t      )Large_STK_Size,
                (void *        )NULL,
                (UBaseType_t   )StartTask_PRIO,
                (TaskHandle_t*)&Start_Task_Handler);
}

void AddInitFunction(taskCreateStruct aim)
{	
	if(MaxNum >= 20)
	{
		return;
	}
	taskInitArray[MaxNum] = aim;
	MaxNum++;
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//进入临界区
	
//	xTaskCreate((TaskFunction_t)test_task,
//					(char*         )"test_task",
//					(uint16_t      )Regular_STK_Size,
//					(void*         )NULL,
//					(UBaseType_t   )2,
//					(TaskHandle_t* )&test_Task_Handler);
					
//	xTaskCreate((TaskFunction_t)taskInitArray[1].functionPointer,
//					(char*         )taskInitArray[1].taskName,
//					(uint16_t      )taskInitArray[1].task_STK_Size,
//					(void*         )NULL,
//					(UBaseType_t   )3,
//					(TaskHandle_t* )&(taskInitArray[1].handle));				
	
	for(int i = 0; i < MaxNum; i++)
	{
		TaskHandle_t tempHandle;
		
		xTaskCreate((TaskFunction_t)taskInitArray[i].functionPointer,
					(char*         )taskInitArray[i].taskName,
					(uint16_t      )taskInitArray[i].task_STK_Size,
					(void*         )NULL,
					(UBaseType_t   )StartTask_PRIO + i + 1,
					(TaskHandle_t* )&tempHandle);
					
		//debug(taskInitArray[i].taskName,(sizeof(&taskInitArray[i].taskName) / sizeof(char)));
	}
	vTaskDelete(Start_Task_Handler);//删除开始任务
	taskEXIT_CRITICAL();//退出临界区
}

void manager_task(void *pvParameters)
{
	for(;;)
	{
		//利用debug模式重设pid参数
		if(UsingPID_Debug)
		{
			for(int i = 0; i < MaxNum + 1; i++)
			{
				taskInitArray[i].pidDebugPointer();
			}
			vTaskDelay(pdMS_TO_TICKS(10));
		}
	}
}
