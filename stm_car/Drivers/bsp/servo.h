
#ifndef __SERVO_H__
#define __SERVO_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define SERVO1_Pin GPIO_PIN_12
#define SERVO1_GPIO_Port GPIOD

float Litim(float litim,float min,float max);
	
typedef struct SERVO_Control_
{
		GPIO_TypeDef *GPIOx;
		uint16_t Pin;
		
		TIM_HandleTypeDef* htim;
	
		uint16_t TIM_CHANNEL;
		int pwm;
		void (*f_param_init)(struct SERVO_Control_* servo, GPIO_TypeDef * GPIOx, uint16_t Pin, TIM_HandleTypeDef* htim, uint32_t TIM_CHANNEL);
		void (*servo_set_pwm)(struct SERVO_Control_* servo, int pwm);

} SERVO_Control;
 

extern SERVO_Control servo1;

void SERVO_struct_init(
    SERVO_Control* servo,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin,
		TIM_HandleTypeDef* htim,
		uint16_t TIM_CHANNEL
    );
/* USER CODE END PTD */

#endif 

