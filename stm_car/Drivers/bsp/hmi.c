#include "hmi.h"

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

extern EventGroupHandle_t myEventGroupHandle_check;//�¼�����
extern osThreadId Task_checkHandle, Task_MotorHandle;
Check_obj_ check_obj ;
HMI_Control hmi;

HMI_Command hmi_command_ = 
{
	.start = HMI_Command_start,
	.stop = HMI_Command_stop,
	.end = HMI_Command_end,
	.top = HMI_Command_top,
	.pid_angle = HMI_Command_pid_angle,
	.pid_position = HMI_Command_pid_position,
	.pid_speed = HMI_Command_pid_speed,
	.pid_P = HMI_Command_pid_P,
	.pid_I = HMI_Command_pid_I,
	.pid_D = HMI_Command_pid_D,
	.check_motor = HMI_Command_check_motor,
	.check_imu = HMI_Command_check_imu,
	.check_enc = HMI_Command_check_enc,
	.check_xbox = HMI_Command_check_xbox,
	.check_top = HMI_Command_check,
	.check_quit = HMI_Command_check_quit,
	.check_quit_2 = HMI_Command_check_quit2,
	
	.inertial_inertial = HMI_Command_inertial,
	.inertial_save_start = HMI_Command_save_start,
	.inertial_save_stop = HMI_Command_save_stop,
	.inertial_run = HMI_Command_run,

	
};

////����main��
////void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
////{
////  if (huart->Instance == hmi.USART_BASE)
////  {
////		hmi.hmi_data_analysis(&hmi, &hmi.res);

////		HAL_UART_Transmit(&huart1, (uint8_t *)&hmi.res, 1, 0xffff);			

////		HAL_UART_Receive_IT(hmi.huart, &hmi.res, 1);
////  }
////	
////	if (huart->Instance == XBOX.USART_BASE)
////  {
////		XBOX.XBOX_data_analysis(&XBOX, &XBOX.res);

//////		HAL_UART_Transmit(&huart1, (uint8_t *)&XBOX.res, 1, 0xffff);		

////		HAL_UART_Receive_IT(XBOX.huart, &XBOX.res, 1);
////  }

////}

void hmi_param_init(HMI_Control* hmi, UART_HandleTypeDef* huart, USART_TypeDef* USART_BASE)
{

	hmi->huart = huart;

	hmi->USART_BASE = USART_BASE;
}

char hmi_wait_command(HMI_Control* hmi, char* command)
{
		if(!memcmp((const void*)hmi->buff_rx,(const void*)command, sizeof(command)))
		{
			
			return 1;
			
		}
		else
		{
			return 0;
		}
}

uint8_t hmi_get_p(HMI_Control* hmi, uint8_t pack_len,uint8_t p)
{
	return hmi->arr_rx[(hmi->arr_p + buff_rx_len - pack_len + p) % buff_rx_len] ;
}
extern int save_run,encoder_all,in_index,in_index_all;

void hmi_data_analysis(HMI_Control* hmi, uint8_t *data)
{

    if (hmi->arr_p >= buff_rx_len)          /* ���������������飩��󳤶� */
    {
        hmi->arr_p = 0;                           /* ��ַƫ�������� */
    }
		hmi->arr_rx[hmi->arr_p] = *(data);         /* ȡ�����ݣ�������� */

		
    if (*data == hmi->hmi_command->end[1])                   /* �ж��Ƿ��յ�֡β */
    {
//			printf("%d",hmi->arr_p);
//			printf("%d",hmi->arr_rx[(hmi->arr_p + buff_rx_len + 1) % buff_rx_len]);
			uint8_t pack_len = start_end_len;			//��Ҫ�ı�
			
			if (hmi->arr_rx[(hmi->arr_p + buff_rx_len - 1) % buff_rx_len] ==  hmi->hmi_command->end[0])                // +1��ʾ֡β��һ�� ���ǵڶ���֡β
      {

				//---------------��ʼ����------------------------û���õ�
				pack_len = start_end_len;			//��Ҫ�ı�
        if (hmi->hmi_get_p(hmi,pack_len,1) == hmi->hmi_command->top)                // +1��ʾ��һ������ Ҳ����֡ͷ 
        {
					
						if (hmi->hmi_get_p(hmi,pack_len,2) == 0xFF)
						{
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->start[1]))
							{

								hmi->start_menu = 1;
								printf("start");
	
							}
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->stop[1]))
							{

								hmi->start_menu = 0;
								printf("stop");


							}
							
		
						}
            
        }
				//---------------��ʼ�����ߵ�------------------------
				pack_len = inertial_len;			//��Ҫ�ı�
        if (hmi->hmi_get_p(hmi,pack_len,1) == hmi->hmi_command->top)                // +1��ʾ��һ������ Ҳ����֡ͷ 
        {
					
						if (hmi->hmi_get_p(hmi,pack_len,2) == hmi->hmi_command->inertial_inertial)
						{
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->inertial_save_start))
							{

								inertial_car.in_index = 0;
								inertial_car.in_index_all = 0;
								inertial_car.encoder_all = 0;
								encoder_1.g_encoder_date_all_IN = encoder_2.g_encoder_date_all_IN = encoder_3.g_encoder_date_all_IN = encoder_4.g_encoder_date_all_IN = 0;
								inertial_car.save_run = Inertial_Save_start;

	
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->inertial_save_stop))
							{
								
								inertial_car.save_run = Inertial_Save_stop;

							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->inertial_run))
							{
	
								inertial_car.save_run = Inertial_Run_ready;


							}
							
		
						}
            
        }
				
				//---------------pid����------------------------
				pack_len = pid_len;			//��Ҫ�ı�
				uint16_t temp;
				if (hmi->hmi_get_p(hmi,pack_len,1) == hmi->hmi_command->top)                // +1��ʾ��һ������ Ҳ����֡ͷ 
        {
						float fbl = 0.001;
						if (hmi->hmi_get_p(hmi,pack_len,2) == hmi->hmi_command->pid_speed)			//�ٶȻ�
						{
							pid__t *pid = &pid_all.pid_speed[1];
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_P))
							{
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->p = (float)temp * fbl;
								(pid+1)->p = (float)temp * fbl;
								(pid+2)->p = (float)temp * fbl;
								(pid+3)->p = (float)temp * fbl;
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_I))
							{
								
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->i = (float)temp * fbl;
								(pid+1)->i = (float)temp * fbl;
								(pid+2)->i = (float)temp * fbl;
								(pid+3)->i = (float)temp * fbl;
								pid->delta_u = 0;
								pid->delta_out = 0;
								pid->last_delta_out = 0;
								
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_D))
							{
								
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->d = (float)temp * fbl;
								(pid+1)->d = (float)temp * fbl;
								(pid+2)->d = (float)temp * fbl;
								(pid+3)->d = (float)temp * fbl;
								
							}		
								      
						}
						
						else if (hmi->hmi_get_p(hmi,pack_len,2) == hmi->hmi_command->pid_angle)			//�ǶȻ�
						{
							pid__t *pid = &pid_all.pid_angle;
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_P))
							{
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->p = (float)temp * fbl;
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_I))
							{
								
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->i = (float)temp * fbl;
								
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_D))
							{
								
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->d = (float)temp * fbl;
								
							}			
							
								      
						}
						
						else if (hmi->hmi_get_p(hmi,pack_len,2) == hmi->hmi_command->pid_position)			//λ�û�
						{
							pid__t *pid = &pid_all.pid_position;
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_P))
							{
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->p = (float)temp * fbl;
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_I))
							{
								
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->i = (float)temp * fbl;
								
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->pid_D))
							{
								
								temp = ((int16_t)(hmi->hmi_get_p(hmi,pack_len,5)))<<8 | hmi->hmi_get_p(hmi,pack_len,4);
								pid->d = (float)temp * fbl;
								
							}		
							
								      
						}
            
        }

				//---------------�Լ�------------------------
				pack_len = check_len;			//��Ҫ�ı�
        if (hmi->hmi_get_p(hmi,pack_len,1) == hmi->hmi_command->top)                // +1��ʾ��һ������ Ҳ����֡ͷ 
        {
						if (hmi->hmi_get_p(hmi,pack_len,2) == hmi->hmi_command->check_top)
						{
							if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->check_motor))
							{
								xTaskResumeFromISR(Task_checkHandle);
								
								check_obj = check_motor;
	
							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->check_imu))
							{
								xTaskResumeFromISR(Task_checkHandle);
								check_obj = check_imu;

							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->check_enc))
							{
								xTaskResumeFromISR(Task_checkHandle);
								check_obj = check_enc;

							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->check_xbox))
							{
								xTaskResumeFromISR(Task_checkHandle);
								check_obj = check_xbox;

							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->check_quit))
							{
								xTaskResumeFromISR(Task_MotorHandle);
								check_obj = check_quit;

							}
							else if(hmi->hmi_get_p(hmi,pack_len,3) == (hmi->hmi_command->check_quit_2))
							{
								xTaskResumeFromISR(Task_MotorHandle);
								check_obj = check_quit;

							}
							

							
		
						}
            
        }
			}
			

       
    }

    hmi->arr_p ++;
}

void HMI_struct_init(
    HMI_Control* hmi,

		UART_HandleTypeDef* huart,
		USART_TypeDef* USART_BASE
    )
{
		
		hmi->f_param_init = hmi_param_init;
	
		hmi->f_param_init(hmi, huart, USART_BASE);
	
		HAL_UART_Receive_IT(hmi->huart, &hmi->res, 1);
	
	
		memset((void*)hmi->buff_rx,0,sizeof(hmi->buff_rx));
	
		hmi->hmi_command = &hmi_command_;
	
		hmi->hmi_wait_command = hmi_wait_command; 
	
		hmi->hmi_get_p = hmi_get_p;
	
		hmi->hmi_data_analysis = hmi_data_analysis;
	
		
		
}
 


 
/* USER CODE END 0 */