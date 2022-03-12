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
		friction_stop_sign ,		//Ħ���ֹر�
		friction_start_sign,		//Ħ���ֿ���
	}friction_state;//<---------------Ħ����״̬

	enum{
		revolver_stop_sign ,		//���̹ر�
		revolver_start_sign,		//���̿���
	}revolver_state;//<---------------����״̬
	
	enum{
		cover_close_sign,		    //���ָǹر�
		cover_open_sign,		    //���ָǿ���
	}cover_state;//<------------------���ָ�״̬
	
	enum 
	{
		Gimbal_gyro,				//��̨-С����ģʽ
		Gimbal_free,				//��̨-����ģʽ
		Gimbal_visual				//��̨-�Ӿ�����
	} gimbal_mode;//<-----------------��̨ģʽ

	enum
	{
		Chassic_rotate,				//����-����ģʽ
		Chassic_free,					//����-����ģʽ
		Chassic_return					//����-����ģʽ
	} chassic_mode;//<----------------����ģʽ
	
	float leftRocker_xAxis;			//��ҡ��x���һ����
	float leftRocker_yAxis;			//��ҡ��y���һ����
	float rightRocker_xAxis;		//��ң��x���һ����
	float rightRocker_yAxis;		//��ң��y���һ����
}dbus_ControlData;

extern RC_Ctl_t RC_CtrlData;
extern dbus_ControlData Dbus_ControlData;

void RC_Init(void);
void RemoteDataProcess(uint8_t *pData);

void DBUS_DataFilltor(void);
void DBUS_DataSetup(void);
#endif
