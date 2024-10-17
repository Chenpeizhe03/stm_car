

#ifndef _ENCODER_H
#define _ENCODER_H


#include "main.h"
#include "stdio.h"


#define ENCODER_HTIM_1 &htim3
#define ENCODER_HTIM_2 &htim4
#define ENCODER_HTIM_3 &htim5
#define ENCODER_HTIM_4 &htim8

#define ENCODER_BASE_1 TIM3
#define ENCODER_BASE_2 TIM4
#define ENCODER_BASE_3 TIM5
#define ENCODER_BASE_4 TIM8

typedef struct encoder_
{
	TIM_HandleTypeDef* htim;
	
	TIM_TypeDef* TIME_BASE;
	
	int16_t g_encoder_date;
	int16_t g_encoder_date_L;
	int32_t g_encoder_date_all;
	int32_t g_encoder_date_all_IN;
	
	float g_encoder_target;
	
	void (*encoder_param_init)(struct encoder_* encoder_x, TIM_HandleTypeDef* htim , TIM_TypeDef* TIME_BASE);
	void (*encoder_init)( struct encoder_* encoder_x);
	void (*encoder_get)(  struct encoder_* encoder_x, uint8_t x, int8_t time);
	void (*encoder_check)( struct encoder_* encoder_x, uint8_t encoder_i);
		
	char (*encoder_str)[][20];		//Êý×éÖ¸Õë
	
}encoder;    

void encoder_struct_init(
    encoder* encoder_x,
		TIM_HandleTypeDef* htim,
		TIM_TypeDef* TIME_BASE
    );
void set_speed(float speed);
extern encoder encoder_1;
extern encoder encoder_2;
extern encoder encoder_3;
extern encoder encoder_4;
void encoder_to_hmi(void);
#endif

