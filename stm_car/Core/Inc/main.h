/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "led.h"
#include "key.h"
#include "XBOX.h"
#include "motor.h"
#include "tim.h"
#include "servo.h"
#include "string.h"
#include "encoder.h"
#include <motor_pid.h>
#include "hmi.h"
#include "imu660ra.h"
#include "lcd_init.h"
#include "lcd.h"

#include "pic.h"
#include "spi.h"
#include "string.h"
#include "filter.h"
#include "config.h"
#include "inertial.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define Event_check_motor (1<<1)
#define Event_check_imu (1<<2)
#define Event_check_enc (1<<3)
#define Event_check_xbox (1<<4)
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
#define SERVO_1_Pin GPIO_PIN_5
#define SERVO_1_GPIO_Port GPIOE
#define SERVO_2_Pin GPIO_PIN_6
#define SERVO_2_GPIO_Port GPIOE
#define ENCODER_3_1_Pin GPIO_PIN_0
#define ENCODER_3_1_GPIO_Port GPIOA
#define ENCODER_3_2_Pin GPIO_PIN_1
#define ENCODER_3_2_GPIO_Port GPIOA
#define RGB_Pin GPIO_PIN_3
#define RGB_GPIO_Port GPIOA
#define IMU_SCLK_Pin GPIO_PIN_5
#define IMU_SCLK_GPIO_Port GPIOA
#define ENCODER_1_1_Pin GPIO_PIN_6
#define ENCODER_1_1_GPIO_Port GPIOA
#define ENCODER_1_2_Pin GPIO_PIN_7
#define ENCODER_1_2_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define KEY_1_Pin GPIO_PIN_7
#define KEY_1_GPIO_Port GPIOE
#define MOTOR_1_DIR_Pin GPIO_PIN_8
#define MOTOR_1_DIR_GPIO_Port GPIOE
#define MOTOR_1_Pin GPIO_PIN_9
#define MOTOR_1_GPIO_Port GPIOE
#define MOTOR_2_DIR_Pin GPIO_PIN_10
#define MOTOR_2_DIR_GPIO_Port GPIOE
#define MOTOR_2_Pin GPIO_PIN_11
#define MOTOR_2_GPIO_Port GPIOE
#define MOTOR_3_DIR_Pin GPIO_PIN_12
#define MOTOR_3_DIR_GPIO_Port GPIOE
#define MOTOR_3_Pin GPIO_PIN_13
#define MOTOR_3_GPIO_Port GPIOE
#define MOTOR_4_Pin GPIO_PIN_14
#define MOTOR_4_GPIO_Port GPIOE
#define MOTOR_4_DIR_Pin GPIO_PIN_15
#define MOTOR_4_DIR_GPIO_Port GPIOE
#define PI_T_Pin GPIO_PIN_10
#define PI_T_GPIO_Port GPIOB
#define PI_R_Pin GPIO_PIN_11
#define PI_R_GPIO_Port GPIOB
#define IPS_SCK_Pin GPIO_PIN_13
#define IPS_SCK_GPIO_Port GPIOB
#define IPS_MISO_Pin GPIO_PIN_14
#define IPS_MISO_GPIO_Port GPIOB
#define IPS_MOSI_Pin GPIO_PIN_15
#define IPS_MOSI_GPIO_Port GPIOB
#define IPS_RES_Pin GPIO_PIN_8
#define IPS_RES_GPIO_Port GPIOD
#define IPS_DC_Pin GPIO_PIN_9
#define IPS_DC_GPIO_Port GPIOD
#define IPS_CS_Pin GPIO_PIN_10
#define IPS_CS_GPIO_Port GPIOD
#define IPS_BLK_Pin GPIO_PIN_11
#define IPS_BLK_GPIO_Port GPIOD
#define ENCODER_2_1_Pin GPIO_PIN_12
#define ENCODER_2_1_GPIO_Port GPIOD
#define ENCODER_2_2_Pin GPIO_PIN_13
#define ENCODER_2_2_GPIO_Port GPIOD
#define ESP_RST_Pin GPIO_PIN_14
#define ESP_RST_GPIO_Port GPIOD
#define ENCODER_4_1_Pin GPIO_PIN_6
#define ENCODER_4_1_GPIO_Port GPIOC
#define ENCODER_4_2_Pin GPIO_PIN_7
#define ENCODER_4_2_GPIO_Port GPIOC
#define HMI_T_Pin GPIO_PIN_5
#define HMI_T_GPIO_Port GPIOD
#define HMI_R_Pin GPIO_PIN_6
#define HMI_R_GPIO_Port GPIOD
#define IMU_MISO_Pin GPIO_PIN_4
#define IMU_MISO_GPIO_Port GPIOB
#define IMU_MOSI_Pin GPIO_PIN_5
#define IMU_MOSI_GPIO_Port GPIOB
#define IMU_CS_Pin GPIO_PIN_6
#define IMU_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define   u32 uint32_t;
#define  u16 uint16_t;
#define   u8 uint8_t;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
