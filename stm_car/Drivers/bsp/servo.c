#include "servo.h"



SERVO_Control servo1;


float Litim(float litim,float min,float max)
{
	if(litim > max)
		return max;
	if(litim < min)
		return min;
	
	return litim;
}

void servo_param_init(SERVO_Control* servo, GPIO_TypeDef * GPIOx, uint16_t Pin, TIM_HandleTypeDef* htim, uint32_t TIM_CHANNEL)
{
	servo->GPIOx = GPIOx;
	servo->Pin = Pin;
	servo->htim = htim;
	servo->TIM_CHANNEL = TIM_CHANNEL;
}

void servo_set_pwm(SERVO_Control* servo, int pwm)
{
	
		servo->pwm = pwm;
	
		pwm>0?HAL_GPIO_WritePin(servo->GPIOx, servo->Pin, 1):HAL_GPIO_WritePin(servo->GPIOx, servo->Pin, 0);
	
		if(pwm < 0 )
		{
			pwm = -pwm;
		}

		__HAL_TIM_SetCompare(servo->htim, servo->TIM_CHANNEL, pwm); 
}

void SERVO_struct_init(
    SERVO_Control* servo,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin,
		TIM_HandleTypeDef* htim,
		uint16_t TIM_CHANNEL
    )
{
		
		servo->servo_set_pwm = servo_set_pwm;
		servo->f_param_init = servo_param_init;
	
		servo->f_param_init(servo, GPIOx, Pin, htim, TIM_CHANNEL);
	
		HAL_TIM_PWM_Start(servo->htim,servo->TIM_CHANNEL);
}
 
 
/* USER CODE END 0 */