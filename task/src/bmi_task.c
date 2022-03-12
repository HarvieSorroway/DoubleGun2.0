#include "bmi_task.h"
#include "pid_caculate_task.h"

#include "bsp_protocol.h"
#include "gimbal_task.h"
#include "gimbal.h"

#include "pid.h"
#include "filters.h"

#include "frame.h"

volatile uint8_t Res;
uint16_t usart6_rx_pos = 0;	//usart6_rx_pos移位指针
const uint16_t usart6_rx_len = 100;
uint8_t usart6_rx_buf[usart6_rx_len] = {0};

uint16_t rx_it_3;
float imu_rx_data[20];

uint16_t flag_imu=0x0201;

float coefficients[3] = {2,0.1,0};
float s[10] = {0,};

pid_typedef pid;


bmi_data dataThisFrame;

void bmi_task(void *pvParameters)
{
	static portTickType xLastWakeTime_bmiTask;
	xLastWakeTime_bmiTask = xTaskGetTickCount();
	
	get_protocol_info(usart6_rx_buf,&usart6_rx_pos,&rx_it_3,imu_rx_data);
	
	for(;;)
	{
		get_protocol_info(usart6_rx_buf,&usart6_rx_pos,&rx_it_3,imu_rx_data);
		
		//数据填充
		dataThisFrame.zVelocity    = 15 * imu_rx_data[5];
		dataThisFrame.zAngle_raw   = 	  imu_rx_data[6];
		dataThisFrame.zAngle_total =      imu_rx_data[7];
		
		vTaskDelayUntil(&xLastWakeTime_bmiTask,pdMS_TO_TICKS(5));
	}
}


void protocol_rx_irq_usart6(uint8_t res)
{
    PROTOCOL_RX_IRQ(res,usart6_rx_buf,&usart6_rx_pos);
    if(usart6_rx_pos>=usart6_rx_len)usart6_rx_pos=0;
}

void USART6_IRQHandler()
{
	
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)//接收中断
    {
		//ledX_cmd(8);
        Res = USART_ReceiveData(USART6);//(USART6->DR);//读取接收到的数据
        protocol_rx_irq_usart6(Res);
		//ledX_cmd(4);
    }
	
	USART_ClearITPendingBit(USART6, USART_IT_RXNE);
    USART_ClearFlag(USART6, USART_IT_RXNE);
}

void CollectData_BMI(void)
{       
}
