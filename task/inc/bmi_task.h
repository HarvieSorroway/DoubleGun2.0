#ifndef __BMI_TASK_H
#define __BMI_TASK_H

#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"

typedef struct
{
	float zAngle_raw;
	float zAngle_total;
	float zVelocity;
}bmi_data;

extern float delta;

void protocol_rx_irq_usart6(uint8_t res);
void bmi_task(void *pvParameters);

#endif
