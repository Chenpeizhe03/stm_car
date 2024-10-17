
#ifndef __HMI_H__
#define __HMI_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define HMI1_Pin GPIO_PIN_12
#define HMI1_GPIO_Port GPIOD

#define HMI1_USART &huart2
#define HMI1_USART_BASE USART2


#define buff_rx_len 20

#define start_end_len 5
#define pid_len 7
#define check_len 5
#define inertial_len 5

#define HMI_Command_start 	{0xFF,0XFD}
#define HMI_Command_stop 	{0xFF,0XFC}

#define HMI_Command_end 		{0x0D,0X0A}
#define HMI_Command_top  	0X55

#define HMI_Command_pid_speed 			0X01
#define HMI_Command_pid_angle 			0X02
#define HMI_Command_pid_position 		0X03

#define HMI_Command_pid_P  0x01
#define HMI_Command_pid_I  0x02
#define HMI_Command_pid_D  0x03

#define HMI_Command_check   			0X04
#define HMI_Command_check_motor   0X01
#define HMI_Command_check_imu   	0X02
#define HMI_Command_check_enc   	0X03
#define HMI_Command_check_xbox   	0X04
#define HMI_Command_check_quit   	0X05
#define HMI_Command_check_quit2   0X06

#define HMI_Command_inertial			0X05
#define HMI_Command_save_start 		0X01
#define HMI_Command_save_stop			0X02
#define HMI_Command_run						0X03
typedef enum
{
	check_quit = 0,
  check_motor = 1,
  check_imu = 2,
	check_enc = 3,
	check_xbox = 4,
	
} Check_obj_;

extern Check_obj_ check_obj ;
typedef struct HMI_Command_
{
			char start[3];
			char stop[3];
			char end[3];
			char pid_speed;
			char pid_angle;
			char pid_position;

			char check_top;
			char check_motor;
			char check_imu;
			char check_enc;
			char check_xbox;
			char check_quit;
			char check_quit_2;
	
			char top;
			char pid_P;
			char pid_I;
			char pid_D;
	
			char inertial_inertial;
			char inertial_save_start;
			char inertial_save_stop;
			char inertial_run;


} HMI_Command;
 


float Litim(float litim,float min,float max);
	
typedef struct HMI_Control_
{
		
		UART_HandleTypeDef* huart;
	
		USART_TypeDef* USART_BASE;
	
		char buff_rx[buff_rx_len];
	
		char arr_rx[buff_rx_len];
	
		char arr_p;
	
		void (*f_param_init)(struct HMI_Control_* hmi, UART_HandleTypeDef* htim, USART_TypeDef* USART_BASE);
		
		HMI_Command* hmi_command;
	
		char start_menu;
	
		uint8_t res;
	
		char (*hmi_wait_command)(struct HMI_Control_* hmi, char* command);
		
		uint8_t (*hmi_get_p)(struct HMI_Control_* hmi, uint8_t pack_len,uint8_t p);
		
		void (*hmi_data_analysis)(struct HMI_Control_* hmi, uint8_t *data);

} HMI_Control;
 
extern HMI_Command hmi_command_;
extern HMI_Control hmi;

void HMI_struct_init(
    HMI_Control* hmi,

		UART_HandleTypeDef* huart,
		
		USART_TypeDef* USART_BASE

    );
/* USER CODE END PTD */

#endif 

