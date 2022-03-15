#ifndef __FRAME_H
#define __FRAME_H

#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"

//基础函数引用
#include "can.h"
#include "dbus.h"
#include "usart.h"
#include "led.h"
#include "pid.h"
#include "pwm.h"
#include "mecanum.h"
#include "gimbal.h"
#include "gimbal_task.h"

//任务函数引用
#include "task_manager.h"
#include "bmi_task.h"


#define MaxNumOf_DataSourceCount 20//需要添加到数据更新函数列表的最大函数个数

//mecanum宏定义
#define UsingMpu 0       //是否使用MPU模式
#define MAX_SPEED 2000	 //电机的最大速度


//功能函数数据填充函数结构体
typedef struct{
	void (*DataSetupPointer) (void);	//数据初始化
	void (*DataFillPointer ) (void);	//数据填充
}DataFilltor;


//数据汇总
typedef struct{
    //电机
	moto_info Data_m3508[4];				//底盘电机 						from: can.c
    moto_info Data_m6020[2];				//云台电机 					 	from: can.c
    moto_info Data_m2006;					//拨盘电机	   				 	from: can.c

    float Data_ChassisAimSpeed[4];			//底盘计算得到的电机设定速度 	from: mecanum.c
 
    RC_Ctl_t Data_RC;						//遥控器数据 					from: dbus.c
	dbus_ControlData Data_dbusControl;      //遥控器处理后的控制数据        from: dbus.c

	bmi_data Data_bmi;						//陀螺仪数据					from: bmi_task.c
} dataCollection;

//各个组件的总开关
typedef enum
{
	UsingMecanum = 1,
	UsingGimbal  = 1,
	UsingLED     = 1,
	UsingVOFA    = 1,
	
	UsingPID_Debug = 0
}IndividualSwitches;

extern dataCollection DataCollection;						//数据汇总
extern dataCollection DataCollection_lastFrame; 			//上一帧(frametask帧)的数据，用于比较判断。

extern DataFilltor Filltors[MaxNumOf_DataSourceCount];

void frame_task_init(void);
void frame_task	(void *pvParameters);							//框架任务函数
void frame_task_PidDebug(void);

void InitAll	(void);											//初始化
void AddFilltor	(DataFilltor filltor);		
					
void debug(char * input,int length);

#endif
