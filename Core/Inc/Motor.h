//
// Created by tw on 2022/11/15.
//

#ifndef CODE_MOTOR_H
#define CODE_MOTOR_H
#include "tim.h"
//电机结构体
typedef struct
{
    uint8_t Dir;//电机转向
    uint8_t Enable;//电机使能
    uint16_t PWM;//电机转速，占空比，0~999
    uint16_t Encoder;//电机编码器的
}Motor_TypeDef;

void Motor_Ctrl(void);
#endif //CODE_MOTOR_H
