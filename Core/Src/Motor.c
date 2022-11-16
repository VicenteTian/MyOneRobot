//
// Created by tw on 2022/11/15.
//
//本项目中所使用了两个电机，其中控制动量轮保持左右平衡的电机命名为Motor_Roll,控制俯仰平衡的电机命名为Motor_Pitch
#include "Motor.h"

Motor_TypeDef Motor_Pitch = {0};
Motor_TypeDef Motor_Roll = {.Motor_ID=1};
void Motor_Init(void)
{
    Motor_Pitch.PWM=0;
    Motor_Roll.PWM=0;
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    Motor_Ctrl(&Motor_Pitch);
    Motor_Ctrl(&Motor_Roll);
    HAL_GPIO_WritePin(GPIOB, STBY_Pin | EN_Pin, GPIO_PIN_SET);//两个电机使能
}
void Motor_Ctrl(Motor_TypeDef *motor) {
    if (motor->PWM > MAX_PWM_Duty) {
        motor->PWM = MAX_PWM_Duty;
    }//检查电机设定的PWM占空比是否过大
    if (motor->Motor_ID == MOTOR_ID_PITCH) {
        if (motor->Dir) {
            HAL_GPIO_WritePin(GPIOA, Green_Pin, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, Motor_Pitch.PWM);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
        } else {
            HAL_GPIO_WritePin(GPIOA, Green_Pin, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Motor_Pitch.PWM);
        }//电机转向和转速控制
    }

    if (motor->Motor_ID == MOTOR_ID_ROLL) {
        if (motor->Dir) {
            HAL_GPIO_WritePin(GPIOB, DIR_Pin, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOB, DIR_Pin, GPIO_PIN_SET);
        }//电机转向控制
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motor->PWM);//电机转速控制
    }
}