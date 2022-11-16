//
// Created by tw on 2022/11/15.
//
#include "N20Motor.h"
#include "tim.h"
uint16_t pwm=500;
uint8_t dir=0;
uint8_t motor_enable=0;
void N20Motor_Ctrl(void)
{
    if (HAL_GPIO_ReadPin(GPIOB,K3_Pin)==GPIO_PIN_RESET)
    {
        dir=!dir;
    }
    if (HAL_GPIO_ReadPin(GPIOB,K2_Pin)==GPIO_PIN_RESET)
    {
        motor_enable=!motor_enable;
    }
    if (motor_enable)
    {
        HAL_GPIO_WritePin(GPIOB, STBY_Pin|Blue_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, STBY_Pin|Blue_Pin, GPIO_PIN_RESET);
    }
}