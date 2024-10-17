#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "main.h"




//-----------------LCD端口定义---------------- 

#define LCD_RES_Clr()  HAL_GPIO_WritePin(IPS_RES_GPIO_Port,IPS_RES_Pin, GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(IPS_RES_GPIO_Port,IPS_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(IPS_DC_GPIO_Port,IPS_DC_Pin, GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(IPS_DC_GPIO_Port,IPS_DC_Pin, GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(IPS_CS_GPIO_Port,IPS_CS_Pin, GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(IPS_CS_GPIO_Port,IPS_CS_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(IPS_BLK_GPIO_Port,IPS_BLK_Pin, GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(IPS_BLK_GPIO_Port,IPS_BLK_Pin, GPIO_PIN_SET)


void LCD_Writ_Bus(uint8_t dat);//模拟SPI时序
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




