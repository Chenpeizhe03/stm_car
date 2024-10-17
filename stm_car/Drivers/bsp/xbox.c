#include "XBOX.h"



XBOX_Control XBOX;

XBOX_Command XBOX_command_ = 
{

	.end = XBOX_Command_end,
	.top = XBOX_Command_top

};

void XBOX_param_init(XBOX_Control* XBOX, UART_HandleTypeDef* huart, USART_TypeDef* USART_BASE)
{

	XBOX->huart = huart;

	XBOX->USART_BASE = USART_BASE;
}

int8_t abs_8(int8_t data)
{
	return data>0?data:-data;
}

void xbox_todata(int16_t* data, XBOX_DATA* XBOX_data, float p1, float p2)
{
		int8_t temp = 0;
		
		temp = XBOX_data->L_UP_DOWN	- 100; 

	
		if(abs_8(temp) < 50)
			p1 = p1 * 0.6;
			
		*data = p1 * (int)temp;
		
		//-------------------------------------
		
		temp = XBOX_data->L_LEFT_RIGHT	- 100; 
		
		if(abs_8(temp) < 50)
			p2 = p2 * 0.6;
			
		*data += p2 * (int)temp;
}

uint8_t XBOX_get_p(XBOX_Control* XBOX, uint8_t pack_len,uint8_t p)
{
	return XBOX->arr_rx[(XBOX->arr_p + xbox_rx_len - pack_len + p) % xbox_rx_len] ;
}


void XBOX_data_analysis(XBOX_Control* XBOX, uint8_t *data)
{

    if (XBOX->arr_p >= xbox_rx_len)          /* 超过缓冲区（数组）最大长度 */
    {
        XBOX->arr_p = 0;                           /* 地址偏移量清零 */
    }
		XBOX->arr_rx[XBOX->arr_p] = *(data);         /* 取出数据，存进数组 */


    if (*data == XBOX->XBOX_command->end[1])                   /* 判断是否收到帧尾 */
    {

			uint8_t pack_len = xbox_len;			//需要改变
			
			if (XBOX->arr_rx[(XBOX->arr_p + xbox_rx_len - 1) % xbox_rx_len] ==  XBOX->XBOX_command->end[0])                // -1表示帧尾前一个 就是第一个帧尾
      {
				
				//---------------开始结束------------------------
				if (XBOX->XBOX_get_p(XBOX,pack_len,1) == XBOX->XBOX_command->top)                // +1表示第一个数据 也就是帧头 
        {
					
					uint8_t* data_p = &XBOX->XBOX_data.L_UP_DOWN;
					int i = 0;

					for(i = 0;i< xbox_obj_len;i++)
					{

						
							*(data_p+i) = XBOX->XBOX_get_p(XBOX,pack_len,i+2);
						
					}
					
						
						
					}
					if(XBOX->XBOX_data.START_BUTTON == 1)
						XBOX->get_data = 1;	
					else if(XBOX->XBOX_data.BACK_BUTTON == 1)
						XBOX->get_data = 0;	
				}
			}
			

       
    

    XBOX->arr_p ++;
}

void check_buttom(XBOX_Control* XBOX)
{
		uint8_t* data_p = &XBOX->XBOX_data.A_BUTTON;
		int i = 0;

		for(i = 0;i < xbox_buttom_len ;i++)
		{

			*(data_p+i)?printf("%s : %d\r\n",*(*XBOX->XBOX_data.buttom_str + i),*(data_p+i) ):1;	
			//二维数组指针 指向首地址 一重解引用得到第 i 行地址 指向第一列地址 二重解引用得到第 i 行第一列地址 
			
		}
}


void check_telecontrol(XBOX_Control* XBOX)
{
		uint8_t* data_p = &XBOX->XBOX_data.L_UP_DOWN;
		int i = 0;

		for(i = 0;i < telecontrol_len ;i++)
		{
			if(*(data_p+i) != 100 && i < 4)
			{
				printf("%s : %d\r\n",*(*XBOX->XBOX_data.telecontrol_str + i),*(data_p+i));
			}
			else if(*(data_p+i) != 0 && i >= 4)
			{
				printf("%s : %d\r\n",*(*XBOX->XBOX_data.telecontrol_str + i),*(data_p+i));
			}
			
			//二维数组指针 指向首地址 一重解引用得到第 i 行地址 指向第一列地址 二重解引用得到第 i 行第一列地址 
			
		}
}

void printf_xbox(XBOX_Control* XBOX)
{
	printf("-----------xbox-----------------\r\n");
	
	XBOX->check_telecontrol(XBOX);
	XBOX->check_buttom(XBOX);
	
}

char buttom_str[xbox_buttom_len][20] =
{
	{" A_BUTTON "},
	{" B_BUTTON "},
	{" Y_BUTTON "},
	{" X_BUTTON "},
	{" START_BUTTON "},
	{" BACK_BUTTON "},
	{" LOGITECH_BUTTON "},
	{" LEFT_GA_BUTTON "},
	{" RIGHT_GA_BUTTON "},
	{" LB_BUTTON "},
	{" RB_BUTTON "},
	{" FX_LEFT "},
	{" FX_RIGHT "},
	{" FX_UP "},
	{" FX_DOWN "}
};

char telecontrol_str[telecontrol_len][20] =
{
	{" L_UP_DOWN "},
	{" L_LEFT_RIGHT "},
	{" R_UP_DOWN "},
	{" R_LEFT_RIGHT "},
	{" L_UP "},
	{" R_UP "}
};


		
void XBOX_struct_init(
    XBOX_Control* XBOX,

		UART_HandleTypeDef* huart,
		
		USART_TypeDef* USART_BASE


    )
{
		
		XBOX->f_param_init = XBOX_param_init;
	
		XBOX->f_param_init(XBOX, huart, USART_BASE);
	
		HAL_UART_Receive_IT(XBOX->huart, &XBOX->res, 1);
	
	
		XBOX->XBOX_command = &XBOX_command_;
	
	
		XBOX->XBOX_get_p = XBOX_get_p;
	
		XBOX->XBOX_data_analysis = XBOX_data_analysis;
	
		XBOX->printf_xbox = printf_xbox;
	
		XBOX->check_buttom = check_buttom;
	
		XBOX->check_telecontrol = check_telecontrol;
		
		XBOX->XBOX_data.buttom_str = &buttom_str;
		
		XBOX->XBOX_data.telecontrol_str = &telecontrol_str;
		
		XBOX->xbox_todata = xbox_todata;
		
		
}
 


 
/* USER CODE END 0 */