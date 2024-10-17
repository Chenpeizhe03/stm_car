#include "led.h"




LED_Control led_g;

void LED_On(LED_Control* led) 
{
    HAL_GPIO_WritePin(led->GPIOx, led->Pin, GPIO_PIN_SET);
}
 

void LED_Off(LED_Control* led) 
{
    HAL_GPIO_WritePin(led->GPIOx, led->Pin, GPIO_PIN_RESET);
}
 

void LED_Toggle(LED_Control* led)
{
  HAL_GPIO_TogglePin(led->GPIOx, led->Pin);
}

void led_param_init(LED_Control* led, GPIO_TypeDef * GPIOx, uint16_t Pin)
{
	led->GPIOx = GPIOx;
	led->Pin = Pin;
}

void LED_struct_init(
    LED_Control* led,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin
    )
{
		
		led->f_param_init = led_param_init;
    led->On = LED_On;
		led->Off = LED_Off;
		led->Toggle = LED_Toggle;
	
		led->f_param_init(led, GPIOx, Pin);
}
 
 
/* USER CODE END 0 */