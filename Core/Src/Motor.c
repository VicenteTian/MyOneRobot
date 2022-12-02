//
// Created by tw on 2022/11/15.
//
//本项目中所使用了两个电机，其中控制动量轮保持左右平衡的电机命名为Motor_Roll,控制俯仰平衡的电机命名为Motor_Pitch
#include "Motor.h"
#include "oled.h"

Motor_TypeDef Motor_Pitch = {.PID_Enable=1};
Motor_TypeDef Motor_Roll = {.Motor_ID=1,
        .PID_Enable=1};
__IO uint16_t Motor_Pitch_Encoder_CNT = 0;

void Motor_Init(void) {
    Motor_Pitch.PWM = 0;
    Motor_Roll.PWM = 0;
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//PWM
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//PWM2
    Motor_Ctrl(&Motor_Pitch);
    Motor_Ctrl(&Motor_Roll);
    HAL_GPIO_WritePin(GPIOB, EN2_Pin | EN_Pin, GPIO_PIN_SET);//两个电机使能
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);//开启Motor_Pitch的编码器
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);//开启Motor_Roll的编码器
}

void Motor_Ctrl(Motor_TypeDef *motor) {
    if (motor->PWM > MAX_PWM_Duty) {
        motor->PWM = MAX_PWM_Duty;
    }//检查电机设定的PWM占空比是否过大
    if (motor->Motor_ID == MOTOR_ID_PITCH) {
        if (motor->Dir) {
            HAL_GPIO_WritePin(GPIOB, DIR2_Pin, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOB, DIR2_Pin, GPIO_PIN_SET);//左转
        }//电机转向控制
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, motor->PWM);//电机转速控制
    }
    if (motor->Motor_ID == MOTOR_ID_ROLL) {
        if (motor->Dir) {
            HAL_GPIO_WritePin(GPIOB, DIR_Pin, GPIO_PIN_RESET);
        } else {
            HAL_GPIO_WritePin(GPIOB, DIR_Pin, GPIO_PIN_SET);//左转
        }//电机转向控制
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motor->PWM);//电机转速控制
    }
}

void get_Encoder(void) {
    static uint8_t PitchOverSpeedCNT = 0;
    static uint8_t RollOverSpeedCNT = 0;
    //从相应变量中取出编码器的计数值
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4))//采用定时器的正交解码会获得转向，获取电机转向
    {
        Motor_Roll.Encoder = 32768 - htim4.Instance->CNT;
    } else {
        Motor_Roll.Encoder = htim4.Instance->CNT - 32768;
    }
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3))//采用定时器的正交解码会获得转向，获取电机转向
    {
        Motor_Pitch.Encoder = 32768 - htim3.Instance->CNT;
    } else {
        Motor_Pitch.Encoder = htim3.Instance->CNT - 32768;
    }
    OLED_ShowNumber(48, 4, Motor_Pitch.Encoder, 4, 12);
    OLED_ShowNumber(48, 5, Motor_Roll.Encoder, 4, 12);
    //编码器相关定时器计数值复位
    htim3.Instance->CNT = 32768;
    htim4.Instance->CNT = 32768;
    //超速保护
//    if (Motor_Pitch.Encoder > M_PITCH_MAX_Speed) {
//        ++PitchOverSpeedCNT;
//    } else {
//        PitchOverSpeedCNT = 0;
//    }
//    if (Motor_Roll.Encoder > M_ROLL_MAX_Speed) {
//        ++RollOverSpeedCNT;
//    } else {
//        RollOverSpeedCNT = 0;
//    }
//    if (PitchOverSpeedCNT > 10) {
//        Motor_Pitch.PWM = 0;
//    }
//    if (RollOverSpeedCNT > 10) {
//        Motor_Roll.PWM = 0;
//        Motor_Roll.PID_Enable = 0;
//        HAL_GPIO_TogglePin(GPIOA, Red_Pin);
//    }
}

uint16_t  myabs(int16_t x)
{
    if (x>=0)
        return x;
    else
        return -x;
}
void Roll_balance_ctrl(int16_t balanceAngle,int16_t angle, int16_t gyro) {
    float Bias = 0;
    int balance = 0;
    Bias = balanceAngle - angle;                                 //===求出平衡的角度中值和机械相关
    if (Motor_Roll.PID_Enable&(myabs(angle)<50)) { balance = 200 * Bias - 0.8* gyro; }  //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数
    if (balance >= 0) {
        Motor_Roll.Dir = 1;
        Motor_Roll.PWM = balance;
    } else {
        Motor_Roll.Dir = 0;
        Motor_Roll.PWM = -balance;
    }
    Motor_Ctrl(&Motor_Roll);
}

void Pitch_balance_ctrl(int16_t balanceAngle,int16_t angle, int16_t gyro) {
    float Bias = 0;
    int balance = 0;
    Bias = balanceAngle - angle;                                 //===求出平衡的角度中值和机械相关
    if (Motor_Roll.PID_Enable&(myabs(angle)<10)) { balance = 500 * Bias - 0.2 * gyro; }  //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数
    else if (Motor_Roll.PID_Enable&(myabs(angle)<50)) { balance = 110 * Bias - 0.2 * gyro; }
    if (balance >= 0) {
        Motor_Pitch.Dir = 1;
        Motor_Pitch.PWM = balance;
    } else {
        Motor_Pitch.Dir = 0;
        Motor_Pitch.PWM = -balance;
    }
    Motor_Ctrl(&Motor_Pitch);
}