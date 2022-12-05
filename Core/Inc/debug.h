//
// Created by tw on 2022/11/16.
//

#ifndef CODE_DEBUG_H
#define CODE_DEBUG_H
#include "oled.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "UART.h"
void get_key(void);
void OLED_show(void );

void UART_ctrl(void);
void MPU_data_show(float *var_MPU6050);
void Motor_test(void);
void get_bat_vol(void);
#endif //CODE_DEBUG_H
