
#ifndef __XBOX_H__
#define __XBOX_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define XBOX1_Pin GPIO_PIN_12
#define XBOX1_GPIO_Port GPIOD

#define xbox_rx_len 30


#define xbox_len 24

#define xbox_buttom_len 15

#define telecontrol_len 6

#define xbox_obj_len 21

#define XBOX_Command_end {0x0D,0X0A}
#define XBOX_Command_top 0X55

#define XBOX_USART &huart3
#define XBOX_USART_BASE USART3



//////						85,				0X55
//////            uint8_t L_UP_DOWN ,

//////            self.L_LEFT_RIGHT ,
//////            self.R_UP_DOWN ,
//////            self.R_LEFT_RIGHT ,
//////            self.L_UP ,
//////            self.R_UP ,
//////            self.A_BUTTON ,
//////            self.B_BUTTON ,
//////            self.Y_BUTTON ,
//////            self.X_BUTTON ,
//////            self.START_BUTTON ,
//////            self.BACK_BUTTON ,
//////            self.LOGITECH_BUTTON ,
//////            self.LEFT_GA_BUTTON ,
//////            self.RIGHT_GA_BUTTON ,
//////            self.LB_BUTTON ,
//////            self.RB_BUTTON ,
//////            self.FX_LEFT ,
//////            self.FX_RIGHT ,
//////            self.FX_UP ,
//////            self.FX_DOWN ,
//////            10,				0X0A
//////            13				0x0D
						
typedef struct XBOX_DATA_
{
	//下和右是199 中间是100 左边是 0
		uint8_t L_UP_DOWN ;

		uint8_t L_LEFT_RIGHT ;
	
		uint8_t R_LEFT_RIGHT ;
		uint8_t L_UP ;
		uint8_t R_UP_DOWN ;
		uint8_t R_UP ;
	
		uint8_t A_BUTTON ;
		uint8_t B_BUTTON ;
		uint8_t Y_BUTTON ;
		uint8_t X_BUTTON ;
		uint8_t START_BUTTON ;
		uint8_t BACK_BUTTON ;
		uint8_t LOGITECH_BUTTON ;
		uint8_t LEFT_GA_BUTTON ;
		uint8_t RIGHT_GA_BUTTON ;
		uint8_t LB_BUTTON ;
		uint8_t RB_BUTTON ;
		uint8_t FX_LEFT ;
		uint8_t FX_RIGHT ;
		uint8_t FX_UP ;
		uint8_t FX_DOWN ;
		
		char (*buttom_str)[][20];		//数组指针
		char (*telecontrol_str)[][20];		//数组指针
		
		
} XBOX_DATA;
 

typedef struct XBOX_Command_
{
	
		uint8_t top;
		char end[10];

		
} XBOX_Command;

	
typedef struct XBOX_Control_
{
		
		UART_HandleTypeDef* huart;
	
		USART_TypeDef* USART_BASE;
	
	
		char arr_rx[xbox_rx_len];
	
		char arr_p;
	
		void (*f_param_init)(struct XBOX_Control_* XBOX, UART_HandleTypeDef* htim, USART_TypeDef* USART_BASE);
		
		XBOX_Command* XBOX_command;
	
		
		uint8_t get_data;
	
		uint8_t res;
	
		XBOX_DATA XBOX_data;
		
		uint8_t (*XBOX_get_p)(struct XBOX_Control_* XBOX, uint8_t pack_len,uint8_t p);
		
		void (*XBOX_data_analysis)(struct XBOX_Control_* XBOX, uint8_t *data);
		
		void (*printf_xbox)(struct XBOX_Control_* XBOX);
		
		void (*check_buttom)(struct XBOX_Control_* XBOX);
		
		void (*check_telecontrol)(struct XBOX_Control_* XBOX);
		
		void (*xbox_todata)( int16_t* pwm, XBOX_DATA* XBOX_data, float p, float p2);

} XBOX_Control;
 
extern XBOX_Command XBOX_command_;
extern XBOX_Control XBOX;

void XBOX_struct_init(
    XBOX_Control* XBOX,

		UART_HandleTypeDef* huart,
		
		USART_TypeDef* USART_BASE


    );
/* USER CODE END PTD */

#endif 

