#ifndef __FRAME_H
#define __FRAME_H

#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"

//������������
#include "can.h"
#include "dbus.h"
#include "usart.h"
#include "led.h"
#include "pid.h"
#include "pwm.h"
#include "mecanum.h"
#include "gimbal.h"
#include "gimbal_task.h"

//����������
#include "task_manager.h"
#include "bmi_task.h"


#define MaxNumOf_DataSourceCount 20//��Ҫ��ӵ����ݸ��º����б�����������

//mecanum�궨��
#define UsingMpu 0       //�Ƿ�ʹ��MPUģʽ
#define MAX_SPEED 2000	 //���������ٶ�


//���ܺ���������亯���ṹ��
typedef struct{
	void (*DataSetupPointer) (void);	//���ݳ�ʼ��
	void (*DataFillPointer ) (void);	//�������
}DataFilltor;


//���ݻ���
typedef struct{
    //���
	moto_info Data_m3508[4];				//���̵�� 						from: can.c
    moto_info Data_m6020[2];				//��̨��� 					 	from: can.c
    moto_info Data_m2006;					//���̵��	   				 	from: can.c

    float Data_ChassisAimSpeed[4];			//���̼���õ��ĵ���趨�ٶ� 	from: mecanum.c
 
    RC_Ctl_t Data_RC;						//ң�������� 					from: dbus.c
	dbus_ControlData Data_dbusControl;      //ң���������Ŀ�������        from: dbus.c

	bmi_data Data_bmi;						//����������					from: bmi_task.c
} dataCollection;

//����������ܿ���
typedef enum
{
	UsingMecanum = 1,
	UsingGimbal  = 1,
	UsingLED     = 1,
	UsingVOFA    = 1,
	
	UsingPID_Debug = 0
}IndividualSwitches;

extern dataCollection DataCollection;						//���ݻ���
extern dataCollection DataCollection_lastFrame; 			//��һ֡(frametask֡)�����ݣ����ڱȽ��жϡ�

extern DataFilltor Filltors[MaxNumOf_DataSourceCount];

void frame_task_init(void);
void frame_task	(void *pvParameters);							//���������
void frame_task_PidDebug(void);

void InitAll	(void);											//��ʼ��
void AddFilltor	(DataFilltor filltor);		
					
void debug(char * input,int length);

#endif
