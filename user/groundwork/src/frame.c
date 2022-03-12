#include "frame.h"

//task includes
#include "FreeRTOS.h"
#include "task.h"

//初始化
#include "init.h"


dataCollection DataCollection;
dataCollection DataCollection_lastFrame;

DataFilltor Filltors[MaxNumOf_DataSourceCount];
int maxNum = 0;

void InitAll(void)
{
	//基础函数初始化
	delay_init(180);
	ledX_init();
	RC_Init();
	can1_init();
	power_init();
	PWM4_init();
	UART8_init();
	USART6_init();

	//进行数据初始化
	for(int i = 0;i < maxNum;i++)
	{
		Filltors[i].DataSetupPointer();
	}
	
	TaskInit();
}

void FrameTask(void *pvParameters)
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
		
        vTaskDelayUntil(&xLastWakeTime_Frame,pdMS_TO_TICKS(5));//5ms周期
    }
}

void AddFilltor(DataFilltor filltor)
{
	if(maxNum < 20)
	{
		Filltors[maxNum] = filltor;
		maxNum++;
	}
}
