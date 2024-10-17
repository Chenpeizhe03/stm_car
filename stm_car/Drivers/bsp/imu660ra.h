/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		imu20602
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看common.h内VERSION宏定义
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					接线定义：
					------------------------------------ 

					------------------------------------ 
 ********************************************************************************************************************/
#ifndef _SEEKFREE_imu20602_h
#define _SEEKFREE_imu20602_h


#include "main.h"
#include "kalman_filter.h"
//----------------------可修改-----------------------------

#define IMU_SPI &hspi1

#define OFFSET_COUNT 300
#define IMU_TIME 0.001f

#define CAR_YAW  				imu660ra.eulerAngle.yaw
#define CAR_YAW_TARGET  imu660ra.eulerAngle.yaw_target

//---------------------------------------------------------
#define IMU660RA_ACC_SAMPLE_DEFAULT     ( IMU660RA_ACC_SAMPLE_SGN_8G )          // 在这设置默认的 加速度计 初始化量程
#define IMU660RA_GYRO_SAMPLE_DEFAULT    ( IMU660RA_GYRO_SAMPLE_SGN_2000DPS )    // 在这设置默认的 陀螺仪   初始化量程


#define IMU660RA_TIMEOUT_COUNT      ( 0x00FF )                                  // IMU660RA 超时计数

//================================================定义 IMU660RA 内部地址================================================
#define IMU660RA_DEV_ADDR           ( 0x69 )                                    // SA0接地：0x68 SA0上拉：0x69 模块默认上拉
#define IMU660RA_SPI_W              ( 0x00 )
#define IMU660RA_SPI_R              ( 0x80 )

#define IMU660RA_CHIP_ID            ( 0x00 )
#define IMU660RA_PWR_CONF           ( 0x7C )
#define IMU660RA_PWR_CTRL           ( 0x7D )
#define IMU660RA_INIT_CTRL          ( 0x59 )
#define IMU660RA_INIT_DATA          ( 0x5E )
#define IMU660RA_INT_STA            ( 0x21 )
#define IMU660RA_ACC_ADDRESS        ( 0x0C )
#define IMU660RA_GYRO_ADDRESS       ( 0x12 )
#define IMU660RA_ACC_CONF           ( 0x40 )
#define IMU660RA_ACC_RANGE          ( 0x41 )
#define IMU660RA_GYR_CONF           ( 0x42 )
#define IMU660RA_GYR_RANGE          ( 0x43 )

typedef enum
{
    IMU660RA_ACC_SAMPLE_SGN_2G ,                                                // 加速度计量程 ±2G  (ACC = Accelerometer 加速度计) (SGN = signum 带符号数 表示正负范围) (G = g 重力加速度 g≈9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_4G ,                                                // 加速度计量程 ±4G  (ACC = Accelerometer 加速度计) (SGN = signum 带符号数 表示正负范围) (G = g 重力加速度 g≈9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_8G ,                                                // 加速度计量程 ±8G  (ACC = Accelerometer 加速度计) (SGN = signum 带符号数 表示正负范围) (G = g 重力加速度 g≈9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_16G,                                                // 加速度计量程 ±16G (ACC = Accelerometer 加速度计) (SGN = signum 带符号数 表示正负范围) (G = g 重力加速度 g≈9.80 m/s^2)
}imu660ra_acc_sample_config;

typedef enum
{
    IMU660RA_GYRO_SAMPLE_SGN_125DPS ,                                           // 陀螺仪量程 ±125DPS  (GYRO = Gyroscope 陀螺仪) (SGN = signum 带符号数 表示正负范围) (DPS = Degree Per Second 角速度单位 °/S)
    IMU660RA_GYRO_SAMPLE_SGN_250DPS ,                                           // 陀螺仪量程 ±250DPS  (GYRO = Gyroscope 陀螺仪) (SGN = signum 带符号数 表示正负范围) (DPS = Degree Per Second 角速度单位 °/S)
    IMU660RA_GYRO_SAMPLE_SGN_500DPS ,                                           // 陀螺仪量程 ±500DPS  (GYRO = Gyroscope 陀螺仪) (SGN = signum 带符号数 表示正负范围) (DPS = Degree Per Second 角速度单位 °/S)
    IMU660RA_GYRO_SAMPLE_SGN_1000DPS,                                           // 陀螺仪量程 ±1000DPS (GYRO = Gyroscope 陀螺仪) (SGN = signum 带符号数 表示正负范围) (DPS = Degree Per Second 角速度单位 °/S)
    IMU660RA_GYRO_SAMPLE_SGN_2000DPS,                                           // 陀螺仪量程 ±2000DPS (GYRO = Gyroscope 陀螺仪) (SGN = signum 带符号数 表示正负范围) (DPS = Degree Per Second 角速度单位 °/S)
}imu660ra_gyro_sample_config;


extern unsigned char imu660ra_config_file[8192];

typedef struct {
    float pitch;    //俯仰角

    float yaw;      //偏航角
		float roll;     //滚转角
	
	
		float pitch_target;    //俯仰角

    float yaw_target;      //偏航角
		float roll_target;     //滚转角
	
		float pitch_L;    //俯仰角

    float yaw_L;      //偏航角
		float roll_L;     //滚转角

	
}corner_param_t;				//陀螺仪角度

typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
}imu_param_t;      //陀螺仪参数

typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
}gyro_param_t;     //陀螺仪零偏

typedef struct {
    int16_t imu_gyro_x,imu_gyro_y,imu_gyro_z;
		int16_t imu_acc_x,imu_acc_y,imu_acc_z;
}read_imu_;     //陀螺仪零偏

typedef enum
{
	IMU_ERR_OK,
	IMU_ERR_INIT,
	IMU_ERR_CONFIG,
	IMU_ERR_SAMPLE,

	
}IMU_ERR_;

typedef struct imu_
{
	corner_param_t eulerAngle;
	imu_param_t imu_data;
	gyro_param_t GyroOffset;
	read_imu_ read_imu;
	
	kalman2_state state;
	
	SPI_HandleTypeDef* hspi;
	
	GPIO_TypeDef *GPIOx_CS;
  uint16_t Pin_CS;
	
	float imu660ra_transition_factor[2];
//	float imu660ra_transition_factor[2] = {4096, 16.4};
	
	IMU_ERR_ imu_err;
	
	uint16_t count;
	
	float time;
	
	uint8_t gyroOffset_ok;;
	
	
	void (*IMU660RA_CS)(struct imu_* imu660ra,uint8_t x);
	void (*imu660ra_write_register)(struct imu_* imu660ra,uint8_t cmd, uint8_t val);
	void (*imu660ra_write_registers)(struct imu_* imu660ra,uint8_t cmd, uint8_t* data, uint32_t length);
	uint8_t (*imu660ra_read_register)(struct imu_* imu660ra,uint8_t cmd);
	void (*imu660ra_read_registers)(struct imu_* imu660ra, uint8_t * val, uint8_t len);
	uint8_t (*imu660ra_self_check)(struct imu_* imu660ra);
	void (*imu660_gyroOffset)(struct imu_* imu660ra);
	uint8_t (*imu660ra_init)(struct imu_* imu660ra);
	void (*imu660ra_get_gyro)(struct imu_ *imu660ra);
	void (*imu660ra_get_acc)(struct imu_ *imu660ra);
	void (*imu_param_init)(struct imu_ *imu660ra, SPI_HandleTypeDef* hspi, GPIO_TypeDef * GPIOx_CS, uint16_t Pin_CS );
	void (*imu660ra_transition)(struct imu_* imu660ra);
	void (*imu660ra_print)(struct imu_* imu660ra);
	void (*imu660ra_get)(struct imu_* imu660ra);
	void (*imu660ra_check)(struct imu_* imu660ra);
	void (*imu660ra_to_hmi)(struct imu_* imu660ra);
	
}imu;    


extern imu imu660ra;

void imu_struct_init(
    imu* imu660ra,
		SPI_HandleTypeDef* hspi,
    GPIO_TypeDef *GPIOx_CS,
    uint16_t Pin_CS
    );
#endif
