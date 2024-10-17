
#ifndef __LED_H__
#define __LED_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB

typedef struct LED_Control_
{
		GPIO_TypeDef *GPIOx;
		uint16_t Pin;
		void (*f_param_init)(struct LED_Control_* led, GPIO_TypeDef * GPIOx, uint16_t Pin);  
    void (*On)(struct LED_Control_* led);  
    void (*Off)(struct LED_Control_* led); 
    void (*Toggle)(struct LED_Control_* led); 

} LED_Control;
 

extern LED_Control led_g;

void LED_struct_init(
    LED_Control* led,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin
    );
/* USER CODE END PTD */

#endif 

