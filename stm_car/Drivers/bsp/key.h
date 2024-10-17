
#ifndef __KEY_H__
#define __KEY_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define KEY_Pin GPIO_PIN_0
#define KEY_GPIO_Port GPIOA

#define KEY_DOWM (KEY_STATE)HAL_GPIO_ReadPin(key->GPIOx, key->Pin) == DOWM
#define KEY_UP (KEY_STATE)HAL_GPIO_ReadPin(key->GPIOx, key->Pin) == UP
typedef enum
{
	UP,
	DOWM,
}KEY_STATE;

typedef enum
{
	NO_KEY,
	ONE_SHORT,
	ONE_LONG,
	TWO,
}READ_STATE;

typedef struct KEY_Control_
{
		GPIO_TypeDef *GPIOx;
		uint16_t Pin;
		void (*f_param_init)(struct KEY_Control_* key, GPIO_TypeDef * GPIOx, uint16_t Pin);  
    KEY_STATE (*read_key)(struct KEY_Control_* key);  
		READ_STATE (*read_state)(struct KEY_Control_* key);
		int16_t time;
		READ_STATE state;
} KEY_Control;
 

extern KEY_Control key;

void KEY_struct_init(
    KEY_Control* key,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin
    );
/* USER CODE END PTD */

#endif 

