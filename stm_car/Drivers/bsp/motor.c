#include "motor.h"



MOTOR_Control motor1;
MOTOR_Control motor2;
MOTOR_Control motor3;
MOTOR_Control motor4;


void motor_param_init(MOTOR_Control* motor, GPIO_TypeDef * GPIOx, uint16_t Pin, TIM_HandleTypeDef* htim, uint32_t TIM_CHANNEL)
{
	motor->GPIOx = GPIOx;
	motor->Pin = Pin;
	motor->htim = htim;
	motor->TIM_CHANNEL = TIM_CHANNEL;
}

void motor_set_pwm(MOTOR_Control* motor, int pwm)
{
	
		motor->pwm = pwm;
	

}


void motor_update_pwm(MOTOR_Control* motor, int flag)
{
		int pwm;
	
		if(flag == 1 || flag == 2)
		{
			motor->pwm>0?HAL_GPIO_WritePin(motor->GPIOx, motor->Pin, 1):HAL_GPIO_WritePin(motor->GPIOx, motor->Pin, 0);
			
		}
		
		else
			motor->pwm>0?HAL_GPIO_WritePin(motor->GPIOx, motor->Pin, 0):HAL_GPIO_WritePin(motor->GPIOx, motor->Pin, 1);
	
		if( motor->pwm < 0 )
		{			
				pwm =  -motor->pwm;		
				
		}
		else
		{
			pwm =  motor->pwm;

		}
		
		if(pwm > motor->pwm_litim)
			pwm = motor->pwm_litim;
		
		__HAL_TIM_SetCompare(motor->htim, motor->TIM_CHANNEL, pwm); 
		
}

void clear_pwm(void)
{
		motor1.pwm = 0;
		motor2.pwm = 0;
		motor3.pwm = 0;
		motor4.pwm = 0;

		motor1.motor_update_pwm(&motor1,1);
		motor2.motor_update_pwm(&motor2,2);
		motor3.motor_update_pwm(&motor3,3);
		motor4.motor_update_pwm(&motor4,4);
}
void all_motor_check(void)
{
		int check_pwm = 150;
		motor1.motor_set_pwm(&motor1, check_pwm);
		motor1.motor_update_pwm(&motor1, 1);
		motor2.motor_set_pwm(&motor2, -check_pwm);
		motor2.motor_update_pwm(&motor2, 1);
		
		motor3.motor_set_pwm(&motor3, -check_pwm);
		motor3.motor_update_pwm(&motor3, 0);
		
		motor4.motor_set_pwm(&motor4, check_pwm);
		motor4.motor_update_pwm(&motor4, 0);
	
		HAL_Delay(500);
		motor1.motor_set_pwm(&motor1, 0);
		motor1.motor_update_pwm(&motor1, 1);
		
		motor2.motor_set_pwm(&motor2, 0);
		motor2.motor_update_pwm(&motor2, 1);
		
		motor3.motor_set_pwm(&motor3, 0);
		motor3.motor_update_pwm(&motor3, 0);
		
		motor4.motor_set_pwm(&motor4, 0);
		motor4.motor_update_pwm(&motor4, 0);
	
		HAL_Delay(500);
	
		motor1.motor_set_pwm(&motor1, -check_pwm);
		motor1.motor_update_pwm(&motor1, 1);
		
		motor2.motor_set_pwm(&motor2, check_pwm);
		motor2.motor_update_pwm(&motor2, 1);
		
		motor3.motor_set_pwm(&motor3, check_pwm);
		motor3.motor_update_pwm(&motor3, 0);
		
		motor4.motor_set_pwm(&motor4, -check_pwm);
		motor4.motor_update_pwm(&motor4, 0);
		HAL_Delay(500);
		motor1.motor_set_pwm(&motor1, 0);
		motor1.motor_update_pwm(&motor1, 1);
		
		motor2.motor_set_pwm(&motor2, 0);
		motor2.motor_update_pwm(&motor2, 1);
		
		motor3.motor_set_pwm(&motor3, 0);
		motor3.motor_update_pwm(&motor3, 0);
		
		motor4.motor_set_pwm(&motor4, 0);
		motor4.motor_update_pwm(&motor4, 0);
}

void motor_check(MOTOR_Control* motor, uint8_t motor_i)
{
		motor->motor_set_pwm(motor, 200);
		motor->motor_update_pwm(motor, motor_i);		
	
		osDelay(1000);
	
		motor->motor_set_pwm(motor, -200);
		motor->motor_update_pwm(motor, motor_i);	

}

void MOTOR_struct_init(
    MOTOR_Control* motor,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin,
		TIM_HandleTypeDef* htim,
		uint16_t TIM_CHANNEL
    )
{
		
		motor->motor_set_pwm = motor_set_pwm;
		motor->f_param_init = motor_param_init;
		motor->pwm_litim = PWM_LITIM;
		motor->motor_update_pwm = motor_update_pwm;
	
		motor->motor_check = motor_check;
	
		motor->f_param_init(motor, GPIOx, Pin, htim, TIM_CHANNEL);
	
		HAL_TIM_PWM_Start(motor->htim,motor->TIM_CHANNEL);
		
}
 
 
/* USER CODE END 0 */