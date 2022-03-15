#include "test_task.h"

taskCreateStruct testTaskInit;
TaskHandle_t test_task_handle;

void test_task(void *pvParameters)
{
	for(;;)
	{
		debug("a",1);
		ledX_On(7);
		debug("b",1);
		vTaskDelay(500);
		ledX_Off(7);
		debug("d",1);
		vTaskDelay(500);
	}
	
}

void test_task_Init(void)
{
	testTaskInit.functionPointer = test_task;
	testTaskInit.taskName = "test_task";
	testTaskInit.task_STK_Size = Min_STK_Size;
	testTaskInit.pidDebugPointer = test_task_PidDebug;
	testTaskInit.handle = test_task_handle;

	AddInitFunction(testTaskInit);
}

void test_task_PidDebug(void)
{
	
}
