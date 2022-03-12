#ifndef __DBUS_H
#define __DBUS_H

#include "stm32f4xx_conf.h"

typedef __packed struct  
{
	__packed struct 
	{
		uint16_t ch0;
		uint16_t ch1;
		uint16_t ch2;
		uint16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;
	__packed struct 
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t press_l;
		uint8_t press_r;
	}mouse;
	
	__packed struct 
	{
		uint16_t v;
	}key;
	
}RC_Ctl_t;

typedef struct
{
	enum{
		friction_stop_sign ,		//摩擦轮关闭
		friction_start_sign,		//摩擦轮开启
	}friction_state;//<---------------摩擦轮状态

	enum{
		revolver_stop_sign ,		//拨盘关闭
		revolver_start_sign,		//拨盘开启
	}revolver_state;//<---------------拨盘状态
	
	enum{
		cover_close_sign,		    //弹仓盖关闭
		cover_open_sign,		    //弹仓盖开启
	}cover_state;//<------------------弹仓盖状态
	
	enum 
	{
		Gimbal_gyro,				//云台-小陀螺模式
		Gimbal_free,				//云台-自由模式
		Gimbal_visual				//云台-视觉跟随
	} gimbal_mode;//<-----------------云台模式

	enum
	{
		Chassic_rotate,				//底盘-自旋模式
		Chassic_free,					//底盘-自由模式
		Chassic_return					//底盘-回中模式
	} chassic_mode;//<----------------底盘模式
	
	float leftRocker_xAxis;			//左摇杆x轴归一数据
	float leftRocker_yAxis;			//左摇杆y轴归一数据
	float rightRocker_xAxis;		//右遥感x轴归一数据
	float rightRocker_yAxis;		//右遥感y轴归一数据
}dbus_ControlData;

extern RC_Ctl_t RC_CtrlData;
extern dbus_ControlData Dbus_ControlData;

void RC_Init(void);
void RemoteDataProcess(uint8_t *pData);

void DBUS_DataFilltor(void);
void DBUS_DataSetup(void);
#endif
