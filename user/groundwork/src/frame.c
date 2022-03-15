#include "frame.h"

//task includes
#include "FreeRTOS.h"
#include "task.h"

dataCollection DataCollection;
dataCollection DataCollection_lastFrame;

DataFilltor Filltors[MaxNumOf_DataSourceCount];

taskCreateStruct frameTaskInit;
TaskHandle_t frame_task_handle;

char logs[50];
int maxNum = 0;
int debugIndex = 0;

void InitAll(void)
{
	//基础函数初始化
	delay_init(180);
	ledX_init();
//	RC_Init();
//	can1_init();
//	power_init();
//	PWM4_init();
//	UART8_init();
//	USART6_init();
	
	//进行数据初始化
//	for(int i = 0;i < maxNum;i++)
//	{
//		Filltors[i].DataSetupPointer();
//	}
	
	TaskInit();
	vTaskStartScheduler(); 
}

void frame_task_init(void)
{
	frameTaskInit.functionPointer = frame_task;
	frameTaskInit.taskName = "frame_task";
	frameTaskInit.task_STK_Size = Regular_STK_Size;
	frameTaskInit.handle = frame_task_handle;
	frameTaskInit.pidDebugPointer = frame_task_PidDebug;

	AddInitFunction(frameTaskInit);
}

void frame_task(void *pvParameters)
{
    static portTickType xLastWakeTime_Frame;
    xLastWakeTime_Frame = xTaskGetTickCount();

    //功能函数初始化
    
    for(;;)//框架任务
    {
		//进行数据填充
		for(int i = 0;i < maxNum;i++)
		{
			Filltors[i].DataFillPointer();
		}
		//delay_ms(50);
        //vTaskDelayUntil(&xLastWakeTime_Frame,pdMS_TO_TICKS(5));//5ms周期
		vTaskDelay(50);
    }
}

void frame_task_PidDebug(void)
{
	
}

void AddFilltor(DataFilltor filltor)
{
	if(maxNum < 20)
	{
		Filltors[maxNum] = filltor;
		maxNum++;
	}
}

void debug(char * input,int length)
{
	for(int i = 0;i < length;i++)
	{
		if(debugIndex + i > 50)
		{
			debugIndex = 0;
		}
		logs[debugIndex + i] = input[i];
	}
	debugIndex += length;
}
