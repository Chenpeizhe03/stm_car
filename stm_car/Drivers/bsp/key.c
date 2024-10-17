#include "key.h"

KEY_Control key;


KEY_STATE KEY_Read(KEY_Control* key)
{
	return (KEY_STATE)HAL_GPIO_ReadPin(key->GPIOx, key->Pin);
}


READ_STATE KEY_STATE_Read(KEY_Control* key)
{
	key->state = NO_KEY;
	key->time = 0;
	if(KEY_DOWM)
	{
		while(1)
		{
			if(KEY_DOWM)
			{

				key->time++;
				osDelay(10);

			}		
		
			if(KEY_UP)
			{
				if(key->time > 8)
				{
					key->state = ONE_SHORT;
				}
				
				break;
			}
		}
		if(key->time > 40)
		{
			key->state = ONE_LONG;
		}
		
		//Ë«»÷ ²»ºÃÓÃ
//		if(key->state != NO_KEY)
//		{
//			key->time = 0;
//			while(1)
//			{
//				printf("key->time = %d\r\n",key->time);
//				key->time++;
//				osDelay(10);
//				if(key->time > 40)
//				{
//					break;
//				}
//				if(KEY_DOWM)
//				{
//					while(1)
//					{
//						if(KEY_UP)
//						{
//							key->state = TWO;
//							return key->state;
//						}
//					}
//				}
//			}
//			
//		}
		
	}
	
	
	return key->state;
}

void key_param_init(KEY_Control* key, GPIO_TypeDef * GPIOx, uint16_t x_Pin)
{
	key->GPIOx = GPIOx;
	key->Pin = x_Pin;
}

void KEY_struct_init(
    KEY_Control* key,
    GPIO_TypeDef *GPIOx,
    uint16_t Pin
    )
{
		
		key->f_param_init = key_param_init;
    key->read_key = KEY_Read;
		key->read_state = KEY_STATE_Read;
		key->f_param_init(key, GPIOx, Pin);
}
 
 
/* USER CODE END 0 */