#ifndef __MECANUM_H
#define __MECANUM_H

#include "stm32f4xx_conf.h"


#include "math.h"
#include "frame.h"

void get_aimSpeed(void);

typedef struct{
	float xVelocity_set;			//x设定速度 : m/s
	float yVelocity_set;			//y设定速度 : m/s
	float aVelocity_set;			//角设定速度: rad/s

	float angle_GimbalRelative_set; //相对于云台的设定角度
	
	int wheel_speed[4];
}chassis_info;

#endif
