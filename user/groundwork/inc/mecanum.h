#ifndef __MECANUM_H
#define __MECANUM_H

#include "stm32f4xx_conf.h"


#include "math.h"
#include "frame.h"

void get_aimSpeed(void);

typedef struct{
	float xVelocity_set;			//x�趨�ٶ� : m/s
	float yVelocity_set;			//y�趨�ٶ� : m/s
	float aVelocity_set;			//���趨�ٶ�: rad/s

	float angle_GimbalRelative_set; //�������̨���趨�Ƕ�
	
	int wheel_speed[4];
}chassis_info;

#endif
