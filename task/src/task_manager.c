#include "task_manager.h"

TaskHandle_t Start_Task_Handler;
InitParams pidInitParams;

//�����ʼ���б�,��Ա�ɸ����������ж���
taskCreateStruct taskInitArray[MaxNumOfTask];

//��¼���ж��ٸ�������Ҫ����
int MaxNum = 0;
	
void TaskInit(void)
{		
	test_task_Init();
	
	xTaskCreate((TaskFunction_t)start_task,
                (char*         )"start_task",
                (uint16_t      )Min_STK_Size,
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
	taskENTER_CRITICAL();//�����ٽ���
	
	for(int i = 0; i < MaxNum + 1; i++)
	{
		TaskHandle_t tempHandle;
		
		xTaskCreate((TaskFunction_t)taskInitArray[i].functionPointer,
					(char*         )taskInitArray[i].taskName,
					(uint16_t      )taskInitArray[i].task_STK_Size,
					(void*         )NULL,
					(UBaseType_t   )StartTask_PRIO + i + 1,
					(TaskHandle_t* )&tempHandle);

	}
	vTaskDelete(Start_Task_Handler);//ɾ����ʼ����
	taskEXIT_CRITICAL();//�˳��ٽ���
}

void manager_task(void *pvParameters)
{
	for(;;)
	{
		//����debugģʽ����pid����
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
