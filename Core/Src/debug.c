//
// Created by tw on 2022/11/16.
//
//用于调试机器人的相关功能，包括按键、OLED、蓝牙串口
#include "debug.h"
#include "Motor.h"

extern Motor_TypeDef Motor_Pitch;
extern Motor_TypeDef Motor_Roll;

void get_key(void) {
    if (HAL_GPIO_ReadPin(GPIOB, K3_Pin) == GPIO_PIN_RESET) {
        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(GPIOB, K3_Pin) == GPIO_PIN_RESET) {
            Motor_Pitch.Dir = !Motor_Pitch.Dir;
        }
    }
    if (HAL_GPIO_ReadPin(GPIOB, K2_Pin) == GPIO_PIN_RESET) {
        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(GPIOB, K2_Pin) == GPIO_PIN_RESET) {
            Motor_Pitch.Enable = !Motor_Pitch.Enable;
        }
    }
}

void OLED_show(void) {
    OLED_ShowString(0, 0, (uint8_t *) "Pitch:", 12);
    OLED_ShowString(0, 2, (uint8_t *) "Roll :", 12);
    OLED_ShowString(0, 4, (uint8_t *) "Yaw  :", 12);
    OLED_ShowString(0, 6, (uint8_t *) "Temp :", 12);
}

void MPU_test(void) {
    float var_MPU6050[4] = {0};
    var_MPU6050[3] = mpu_dmp_get_data(&var_MPU6050[0], &var_MPU6050[1], &var_MPU6050[2]);
    //vcan_sendware((uint8_t *)var_MPU6050, sizeof(var_MPU6050));
    if (var_MPU6050[0] < 0) {
        OLED_ShowString(48, 0, (uint8_t *) "-", 12);
        OLED_Float(0, 56, -var_MPU6050[0], 3);
    } else {
        OLED_ShowString(48, 0, (uint8_t *) "+", 12);
        OLED_Float(0, 56, var_MPU6050[0], 3);
    }
    if (var_MPU6050[1] < 0) {
        OLED_ShowString(48, 2, (uint8_t *) "-", 12);
        OLED_Float(2, 56, -var_MPU6050[1], 3);
    } else {
        OLED_ShowString(48, 2, (uint8_t *) "+", 12);
        OLED_Float(2, 56, var_MPU6050[1], 3);
    }
    if (var_MPU6050[2] < 0) {
        OLED_ShowString(48, 4, (uint8_t *) "-", 12);
        OLED_Float(4, 56, -var_MPU6050[2], 3);
    } else {
        OLED_ShowString(48, 4, (uint8_t *) "+", 12);
        OLED_Float(4, 56, var_MPU6050[2], 3);
    }

    OLED_Float(6, 48, MPU_Get_Temperature(), 2);
}
void Motor_test(void)
{
    Motor_Pitch.PWM=350;
    Motor_Roll.PWM=500;
    get_key();
    Motor_Ctrl(&Motor_Pitch);
    Motor_Ctrl(&Motor_Roll);
}