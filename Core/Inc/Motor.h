//
// Created by tw on 2022/11/15.
//

#ifndef CODE_MOTOR_H
#define CODE_MOTOR_H
#include "tim.h"

#define MAX_PWM_Duty 1000//控制电机的最大占空比

#define MOTOR_ID_PITCH 0//俯仰轮电机ID号
#define MOTOR_ID_ROLL 1//动量轮电机ID号

//电机结构体
typedef struct
{
    uint8_t Motor_ID;//电机的ID号
    uint8_t Dir;//电机转向
    uint8_t Enable;//电机使能
    uint16_t PWM;//电机转速，占空比，0~999
    uint16_t Encoder;//电机编码器的
}Motor_TypeDef;
void Motor_Init(void);
void Motor_Ctrl(Motor_TypeDef *motor) ;
#endif //CODE_MOTOR_H
