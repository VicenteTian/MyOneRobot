//
// Created by tw on 2022/11/16.
//
//用于调试机器人的相关功能，包括按键、OLED、蓝牙串口
#include "debug.h"
#include "Motor.h"

extern Motor_TypeDef Motor_Pitch;
extern Motor_TypeDef Motor_Roll;
extern __IO uint16_t time_count; // 时间计数，每1ms增加一(与滴答定时器频率有关)
extern ADC_HandleTypeDef hadc1;
uint8_t Receive_COM = 0;
uint8_t is_message = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    is_message = 1;
    HAL_GPIO_TogglePin(GPIOB,Blue_Pin);
    HAL_UART_Receive_IT(&huart3, &Receive_COM, 1);
}

void UART_ctrl(void) {
    if (is_message) {
        is_message = 0;
        switch (Receive_COM) {
            case 's':
                HAL_GPIO_WritePin(GPIOB, EN2_Pin | EN_Pin, GPIO_PIN_RESET);//两个电机失能
                break;
            case 'e':
                Motor_Pitch.PWM = 0;
                Motor_Roll.PWM = 0;
                HAL_GPIO_WritePin(GPIOB, EN2_Pin | EN_Pin, GPIO_PIN_SET);//两个电机使能
                break;
            case 'a':
                Motor_Pitch.PWM += 100;//电机加速
                OLED_ShowNumber(48, 6, Motor_Pitch.PWM, 4, 12);
                break;
            case '1':
                Motor_Roll.PWM += 100;
                break;
            case 'd':
                if(Motor_Pitch.PWM<100)
                    Motor_Pitch.PWM=100;
                Motor_Pitch.PWM -= 100;//电机减速
                break;
            case '2':
                if(Motor_Roll.PWM<100)
                    Motor_Roll.PWM=100;
                Motor_Roll.PWM -= 100;
                break;
            case 'c':
                Motor_Pitch.Dir = !Motor_Pitch.Dir;
                Motor_Roll.Dir = !Motor_Roll.Dir;
                break;
        }
    }

}

void get_key(void) {
    if (HAL_GPIO_ReadPin(GPIOB, K3_Pin) == GPIO_PIN_RESET) {
        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(GPIOB, K3_Pin) == GPIO_PIN_RESET) {
            Motor_Pitch.Dir = !Motor_Pitch.Dir;
            Motor_Roll.Dir = !Motor_Roll.Dir;
        }
    }
    if (HAL_GPIO_ReadPin(GPIOB, K2_Pin) == GPIO_PIN_RESET) {
        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(GPIOB, K2_Pin) == GPIO_PIN_RESET) {
            Motor_Pitch.PID_Enable = !Motor_Pitch.PID_Enable;
            Motor_Roll.PID_Enable = !Motor_Roll.PID_Enable;
        }
    }
}

void OLED_show(void) {
    OLED_ShowString(0, 0, (uint8_t *) "Pitch:", 12);
    OLED_ShowString(0, 1, (uint8_t *) "Roll :", 12);
    OLED_ShowString(0, 2, (uint8_t *) "Yaw  :", 12);
    OLED_ShowString(0, 3, (uint8_t *) "Temp :", 12);
    OLED_ShowString(0, 4, (uint8_t *) "MP   :", 12);
    OLED_ShowString(0, 5, (uint8_t *) "MR   :", 12);
    OLED_ShowString(0, 6, (uint8_t *) "Bat V:", 12);
    HAL_UART_Receive_IT(&huart3, &Receive_COM, 1);//开启串口的接收中断功能
}

void MPU_data_show(float *var_MPU6050) {
    //vcan_sendware((uint8_t *)var_MPU6050, sizeof(var_MPU6050));
    if (var_MPU6050[0] < 0) {
        OLED_ShowString(48, 0, (uint8_t *) "-", 12);
        OLED_Float(0, 56, -var_MPU6050[0], 3);
    } else {
        OLED_ShowString(48, 0, (uint8_t *) "+", 12);
        OLED_Float(0, 56, var_MPU6050[0], 3);
    }
    if (var_MPU6050[1] < 0) {
        OLED_ShowString(48, 1, (uint8_t *) "-", 12);
        OLED_Float(1, 56, -var_MPU6050[1], 3);
    } else {
        OLED_ShowString(48, 1, (uint8_t *) "+", 12);
        OLED_Float(1, 56, var_MPU6050[1], 3);
    }
    if (var_MPU6050[2] < 0) {
        OLED_ShowString(48, 2, (uint8_t *) "-", 12);
        OLED_Float(2, 56, -var_MPU6050[2], 3);
    } else {
        OLED_ShowString(48, 2, (uint8_t *) "+", 12);
        OLED_Float(2, 56, var_MPU6050[2], 3);
    }
    OLED_Float(3, 48, MPU_Get_Temperature(), 2);
}
void Motor_test(void) {
    //get_key();
    Motor_Ctrl(&Motor_Pitch);
    Motor_Ctrl(&Motor_Roll);
}
void get_bat_vol(void)
{
    static uint32_t temp_val=0;
    static uint8_t i=0;
    if (i<10)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 100);
        temp_val += HAL_ADC_GetValue(&hadc1);
    }
    else
    {
        OLED_Float(6, 48,temp_val/10*0.0035671 , 2);
        i=0;
        temp_val=0;
    }
    ++i;
}