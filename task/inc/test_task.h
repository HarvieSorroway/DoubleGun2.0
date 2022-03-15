#ifndef __TEST_TASK_H
#define __TEST_TASK_H

#include "stm32f4xx_conf.h"

#include "task_manager.h"

#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

void test_task(void *pvParameters);
void test_task_Init(void);
void test_task_PidDebug(void);

#endif
