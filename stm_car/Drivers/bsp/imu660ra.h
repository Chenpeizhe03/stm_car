/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		imu20602
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴common.h��VERSION�궨��
 * @Software 		IAR 7.8 or MDK 5.24a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					���߶��壺
					------------------------------------ 

					------------------------------------ 
 ********************************************************************************************************************/
#ifndef _SEEKFREE_imu20602_h
#define _SEEKFREE_imu20602_h


#include "main.h"
#include "kalman_filter.h"
//----------------------���޸�-----------------------------

#define IMU_SPI &hspi1

#define OFFSET_COUNT 300
#define IMU_TIME 0.001f

#define CAR_YAW  				imu660ra.eulerAngle.yaw
#define CAR_YAW_TARGET  imu660ra.eulerAngle.yaw_target

//---------------------------------------------------------
#define IMU660RA_ACC_SAMPLE_DEFAULT     ( IMU660RA_ACC_SAMPLE_SGN_8G )          // ��������Ĭ�ϵ� ���ٶȼ� ��ʼ������
#define IMU660RA_GYRO_SAMPLE_DEFAULT    ( IMU660RA_GYRO_SAMPLE_SGN_2000DPS )    // ��������Ĭ�ϵ� ������   ��ʼ������


#define IMU660RA_TIMEOUT_COUNT      ( 0x00FF )                                  // IMU660RA ��ʱ����

//================================================���� IMU660RA �ڲ���ַ================================================
#define IMU660RA_DEV_ADDR           ( 0x69 )                                    // SA0�ӵأ�0x68 SA0������0x69 ģ��Ĭ������
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
    IMU660RA_ACC_SAMPLE_SGN_2G ,                                                // ���ٶȼ����� ��2G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_4G ,                                                // ���ٶȼ����� ��4G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_8G ,                                                // ���ٶȼ����� ��8G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_16G,                                                // ���ٶȼ����� ��16G (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
}imu660ra_acc_sample_config;

typedef enum
{
    IMU660RA_GYRO_SAMPLE_SGN_125DPS ,                                           // ���������� ��125DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_250DPS ,                                           // ���������� ��250DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_500DPS ,                                           // ���������� ��500DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_1000DPS,                                           // ���������� ��1000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_2000DPS,                                           // ���������� ��2000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
}imu660ra_gyro_sample_config;


extern unsigned char imu660ra_config_file[8192];

typedef struct {
    float pitch;    //������

    float yaw;      //ƫ����
		float roll;     //��ת��
	
	
		float pitch_target;    //������

    float yaw_target;      //ƫ����
		float roll_target;     //��ת��
	
		float pitch_L;    //������

    float yaw_L;      //ƫ����
		float roll_L;     //��ת��

	
}corner_param_t;				//�����ǽǶ�

typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
}imu_param_t;      //�����ǲ���

typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
}gyro_param_t;     //��������ƫ

typedef struct {
    int16_t imu_gyro_x,imu_gyro_y,imu_gyro_z;
		int16_t imu_acc_x,imu_acc_y,imu_acc_z;
}read_imu_;     //��������ƫ

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
