

#include "encoder.h"

encoder encoder_1;
encoder encoder_2;
encoder encoder_3;
encoder encoder_4;

char encoder_str[4][20] =
{
	{" encoder_1 "},
	{" encoder_2 "},
	{" encoder_3 "},
	{" encoder_4 "}
};
	

void encoder_check( encoder* encoder_x, uint8_t encoder_i)
{
	encoder_x->encoder_get(encoder_x, encoder_i, 1);
	printf("g_encoder_date = %d\r\n",encoder_x->g_encoder_date);
}

void encoder_param_init(encoder* encoder_x, TIM_HandleTypeDef* htim, TIM_TypeDef* TIME_BASE)
{
	encoder_x->htim = htim;
	encoder_x->TIME_BASE = TIME_BASE;

	HAL_TIM_Encoder_Start(encoder_x->htim,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(encoder_x->htim,TIM_CHANNEL_2);  

	encoder_x->encoder_str = &encoder_str;
	
}


void encoder_to_hmi(void)
{
	char tx_buff[30] = "";
	sprintf(tx_buff, "n1.val=%d\xff\xff\xff",encoder_1.g_encoder_date_all);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n2.val=%d\xff\xff\xff",encoder_2.g_encoder_date_all);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n3.val=%d\xff\xff\xff",encoder_3.g_encoder_date_all);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n4.val=%d\xff\xff\xff",encoder_4.g_encoder_date_all);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
   
}



void encoder_get( encoder* encoder_x, uint8_t x, int8_t time)
{
	
		encoder_x->g_encoder_date = time * encoder_x->TIME_BASE->CNT;      //获取编码器值
	
		if(x == 1 || x == 4)
		{
			encoder_x->g_encoder_date = -encoder_x->g_encoder_date;
		}
		
		encoder_x->g_encoder_date_all += encoder_x->g_encoder_date;
		encoder_x->g_encoder_date_all_IN += encoder_x->g_encoder_date;
		
		
//		printf("%s = %d\r\n",*(*encoder_x->encoder_str + x - 1),encoder_x->g_encoder_date);
	
		encoder_x->TIME_BASE->CNT = 0;     
	
}

void set_speed(float speed)
{
		encoder_1.g_encoder_target = speed;
		encoder_2.g_encoder_target = speed;
		encoder_3.g_encoder_target = speed;
		encoder_4.g_encoder_target = speed;
}



void encoder_struct_init(
    encoder* encoder_x,
		TIM_HandleTypeDef* htim,
		TIM_TypeDef* TIME_BASE
    )
{
	
		encoder_x->encoder_param_init = encoder_param_init;
		encoder_x->encoder_check = encoder_check;
		encoder_x->encoder_get = encoder_get;
	
		encoder_x->encoder_param_init(encoder_x, htim, TIME_BASE);
	
		
}






