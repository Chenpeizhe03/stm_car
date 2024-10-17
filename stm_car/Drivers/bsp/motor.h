
#ifndef __MOTOR_H__
#define __MOTOR_H__

/* Includes ------------------------------------------------------------------*/

#include "main.h"

#define M1_TIM &htim1
#define M1_CHANNEL TIM_CHANNEL_1
#define M2_TIM &htim1
#define M2_CHANNEL TIM_CHANNEL_2
#define M3_TIM &htim1
#define M3_CHANNEL TIM_CHANNEL_3
#define M4_TIM &htim1
#define M4_CHANNEL TIM_CHANNEL_4
#define PWM_LITIM 400

typedef struct MOTOR_Control_
{
		GPIO_TypeDef *GPIOx;
		uint16_t Pin;
		
		TIM_HandleTypeDef* htim;
	
		uint16_t TIM_CHANNEL;
	
		int pwm;
	
		int pwm_L;
	
		int pwm_litim;
	
		void (*f_param_init)(struct MOTOR_Control_* motor, GPIO_TypeDef * GPIOx, uint16_t Pin, TIM_HandleTypeDef* htim, uint32_t TIM_CHANNEL);
		void (*motor_set_pwm)(struct MOTOR_Control_* motor, int pwm);
		void (*motor_update_pwm)(struct MOTOR_Control_* motor, int flag);
		void (*motor_check)(struct MOTOR_Control_* motor, uint8_t motor_i);
		
		
	
} MOTOR_Control;
 

void clear_pwm(void);
extern MOTOR_Control motor1;
extern MOTOR_Control motor2;
extern MOTOR_Control motor3;
extern MOTOR_Control motor4;

void MOTOR_struct_init(
    MOTOR_Control* motor,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin,
		TIM_HandleTypeDef* htim,
		uint16_t TIM_CHANNEL
    );

void all_motor_check(void);
/* USER CODE END PTD */

#endif 

