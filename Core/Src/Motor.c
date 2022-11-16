//
// Created by tw on 2022/11/15.
//
//本项目中所使用了两个电机，其中控制动量轮保持左右平衡的电机命名为Motor_Roll,控制俯仰平衡的电机命名为Motor_Pitch
#include "Motor.h"
Motor_TypeDef Motor_Pitch={.Dir=0,
                           .Enable=0,
                           .Encoder=0,
                           .PWM=500};
void Motor_Ctrl(void)
{
    if (HAL_GPIO_ReadPin(GPIOB,K3_Pin)==GPIO_PIN_RESET)
    {
        Motor_Pitch.Dir=!Motor_Pitch.Dir;
    }
    if (HAL_GPIO_ReadPin(GPIOB,K2_Pin)==GPIO_PIN_RESET)
    {
        Motor_Pitch.Enable=!Motor_Pitch.Enable;
    }
    if (Motor_Pitch.Enable)
    {
        HAL_GPIO_WritePin(GPIOB, STBY_Pin|Blue_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, STBY_Pin|Blue_Pin, GPIO_PIN_RESET);
    }
    if (Motor_Pitch.Dir)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, Motor_Pitch.PWM);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
    } else
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Motor_Pitch.PWM);
    }
}