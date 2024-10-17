#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "main.h"




//-----------------LCD�˿ڶ���---------------- 

#define LCD_RES_Clr()  HAL_GPIO_WritePin(IPS_RES_GPIO_Port,IPS_RES_Pin, GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(IPS_RES_GPIO_Port,IPS_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(IPS_DC_GPIO_Port,IPS_DC_Pin, GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(IPS_DC_GPIO_Port,IPS_DC_Pin, GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(IPS_CS_GPIO_Port,IPS_CS_Pin, GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(IPS_CS_GPIO_Port,IPS_CS_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(IPS_BLK_GPIO_Port,IPS_BLK_Pin, GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(IPS_BLK_GPIO_Port,IPS_BLK_Pin, GPIO_PIN_SET)


void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




