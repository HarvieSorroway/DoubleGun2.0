#include "test_task.h"

taskCreateStruct testTaskInit;

void test_task(void *pvParameters)
{
	for(;;)
	{
		ledX_On(7);
		vTaskDelay(1000);
		ledX_Off(7);
		vTaskDelay(500);
	}
	
}

void test_task_Init(void)
{
	testTaskInit.functionPointer = test_task;
	testTaskInit.taskName = "test_task";
	testTaskInit.task_STK_Size = Min_STK_Size;
	testTaskInit.pidDebugPointer = test_task_PidDebug;

	AddInitFunction(testTaskInit);
}

void test_task_PidDebug(void)
{
	
}
