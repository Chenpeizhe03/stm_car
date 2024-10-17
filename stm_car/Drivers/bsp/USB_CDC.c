#include "USB_CDC.h"


usb_cdc usb;


void xbox_to_hmi(void)
{
	char tx_buff[50] = "";
	sprintf(tx_buff, "n0.val=%d\xff\xff\xff",usb.XBOX_data.L_LEFT_RIGHT);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n1.val=%d\xff\xff\xff",usb.XBOX_data.L_UP_DOWN);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n2.val=%d\xff\xff\xff",usb.XBOX_data.R_UP_DOWN);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n3.val=%d\xff\xff\xff",usb.XBOX_data.R_LEFT_RIGHT);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n4.val=%d\xff\xff\xff",usb.XBOX_data.L_UP);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
	
	sprintf(tx_buff, "n5.val=%d\xff\xff\xff",usb.XBOX_data.R_UP);
	HAL_UART_Transmit(hmi.huart, (uint8_t *)tx_buff, strlen(tx_buff), 0xffff);			//放在这里会拖到串口读取
   
}


void USB_analysis(void)
{
	if(usb.rxflag)
	{
		
		if(usb.arr[22] == 0x0d && usb.arr[23] == 0x0a && usb.arr[0] == 0x55)
		{
				uint8_t* data_p = &usb.XBOX_data.L_UP_DOWN;
				int i = 0;

				for(i = 1;i< 22;i++)
				{
						* (data_p+ i -1) = usb.arr[i];
//							printf("*(data_p+i) = %d\r\n",*(data_p+i - 1));
				}
//				printf("-----------------\r\n");
				if(usb.XBOX_data.START_BUTTON == 1)
					usb.get_data = 1;	
				else if(usb.XBOX_data.BACK_BUTTON == 1)
					usb.get_data = 0;	
			
		}
		
		usb.rxflag = 0;
	}
}

static int8_t usb_abs_8(int8_t data)
{
	return data>0?data:-data;
}

void usb_xbox_todata(float* data_enc,float* data_imu,float* data_imu_tag, XBOX_DATA* XBOX_data, float p_run, float p_turn, float p3)
{
		int8_t temp = 0;
		static float temp_imu = 0, temp_imu_L = 0;;
		
		//-------------------------------------
	
		temp = XBOX_data->L_UP_DOWN	- 100; 
			
		*data_enc = p_run * (int)temp;
		
		//-------------------------------------
		
		temp = XBOX_data->L_UP; 
			
		*data_enc += p_turn * (int)temp;
		
		//-------------------------------------
		
		temp = XBOX_data->R_UP; 
			
		*data_enc -= p_turn * (int)temp;

		//-------------------------------------
		
		temp = XBOX_data->L_LEFT_RIGHT	- 100; 
			
		*data_enc += p_turn * (int)temp;
		
		//---------------角度环----------------------
		
		if(usb_abs_8(XBOX_data->L_UP) < 5 && usb_abs_8(XBOX_data->R_UP) < 5 && usb_abs_8(XBOX_data->L_LEFT_RIGHT	- 100) < 5)
		{
			temp_imu = pid_all.pid_angle.f_cal_pid(&pid_all.pid_angle, *data_imu, *data_imu_tag);
			temp_imu = RCFilter(temp_imu, temp_imu_L, 0.4);
			temp_imu_L = temp_imu;
			*data_enc += p3 * temp_imu;
		}
		else
		{
			*data_imu_tag = *data_imu;
		}

}

void usb_xbox_todata_angle(float* data, XBOX_DATA* XBOX_data, float p1)
{
		int8_t temp = 0;
		
		temp = XBOX_data->L_UP; 

	
		if(usb_abs_8(temp) < 50)
			p1 = p1 * 0.6;
			
		*data += p1 * (int)temp;
		
		//-------------------------------------
		
		temp = XBOX_data->R_UP; 

	
		if(usb_abs_8(temp) < 50)
			p1 = p1 * 0.6;
			
		*data -= p1 * (int)temp;
		
		//-------------------------------------
		
		temp = XBOX_data->L_LEFT_RIGHT	- 100; 

		if(usb_abs_8(temp) < 50)
			p1 = p1 * 0.6;
			
		*data += p1 * (int)temp;
		
	

}

void usb_xbox_todata_run( XBOX_DATA* XBOX_data, float p1)
{
		int8_t temp = 0;
		int vx = 0, vy = 0;
		
		temp = XBOX_data->R_LEFT_RIGHT	- 100; 

			
		vx = p1 * (int)temp;
		
		//---------------
		
		temp = XBOX_data->R_UP_DOWN	- 100; 

			
		vy = -p1 * (int)temp;
		
		
		encoder_1.g_encoder_target += -vx + vy;
		encoder_2.g_encoder_target += vx + vy;
		encoder_3.g_encoder_target += -vx + vy;
		encoder_4.g_encoder_target += vx + vy;
		
	

}




