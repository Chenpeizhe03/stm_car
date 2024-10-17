
#ifndef __USBCDC_H__
#define __USBCDC_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define USB_rx_len 24

#define USB_Command_end {0x0D,0X0A}

#define USB_Command_top 0X55
#include "usbd_cdc_if.h"

void USB_analysis(void);


typedef struct usb_cdc_
{
		XBOX_DATA XBOX_data;
	
		uint8_t rxflag;

		uint8_t arr[30];
	
		uint32_t data_nums;
	
		uint8_t end;
	
	
		uint8_t top[2];
		
		uint8_t get_data;
	
}usb_cdc;



void usb_xbox_todata(float* data_enc,float* data_imu,float* data_imu_tag, XBOX_DATA* XBOX_data, float p1, float p2, float p3);
void usb_xbox_todata_angle(float* data, XBOX_DATA* XBOX_data, float p1);
extern usb_cdc usb;
void usb_xbox_todata_run( XBOX_DATA* XBOX_data, float p1);
void xbox_to_hmi(void);
#endif 

