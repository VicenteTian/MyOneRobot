/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define pwr_check_Pin GPIO_PIN_4
#define pwr_check_GPIO_Port GPIOA
#define Green_Pin GPIO_PIN_5
#define Green_GPIO_Port GPIOA
#define MotorB_A_Pin GPIO_PIN_6
#define MotorB_A_GPIO_Port GPIOA
#define MotorB_B_Pin GPIO_PIN_7
#define MotorB_B_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_0
#define BIN2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_1
#define BIN1_GPIO_Port GPIOB
#define K3_Pin GPIO_PIN_2
#define K3_GPIO_Port GPIOB
#define K2_Pin GPIO_PIN_12
#define K2_GPIO_Port GPIOB
#define EN_Pin GPIO_PIN_13
#define EN_GPIO_Port GPIOB
#define DIR_Pin GPIO_PIN_14
#define DIR_GPIO_Port GPIOB
#define STBY_Pin GPIO_PIN_15
#define STBY_GPIO_Port GPIOB
#define PWM_Pin GPIO_PIN_8
#define PWM_GPIO_Port GPIOA
#define Red_Pin GPIO_PIN_15
#define Red_GPIO_Port GPIOA
#define MPU6050_SDA_Pin GPIO_PIN_3
#define MPU6050_SDA_GPIO_Port GPIOB
#define MPU6050_SCL_Pin GPIO_PIN_4
#define MPU6050_SCL_GPIO_Port GPIOB
#define Blue_Pin GPIO_PIN_5
#define Blue_GPIO_Port GPIOB
#define Motor_A_Pin GPIO_PIN_6
#define Motor_A_GPIO_Port GPIOB
#define Motor_B_Pin GPIO_PIN_7
#define Motor_B_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
