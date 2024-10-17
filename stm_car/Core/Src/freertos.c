/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "USB_CDC.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

EventGroupHandle_t myEventGroupHandle_check;//事件组句柄

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId Task_MotorHandle;
osThreadId Task_checkHandle;
osThreadId Task_InertialNaHandle;
osTimerId myTimer01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Motor_Entry(void const * argument);
void Check_Entry(void const * argument);
void InertialNavigation_Entry(void const * argument);
void Callback01(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of myTimer01 */
  osTimerDef(myTimer01, Callback01);
  myTimer01Handle = osTimerCreate(osTimer(myTimer01), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Task_Motor */
  osThreadDef(Task_Motor, Motor_Entry, osPriorityIdle, 0, 128);
  Task_MotorHandle = osThreadCreate(osThread(Task_Motor), NULL);

  /* definition and creation of Task_check */
  osThreadDef(Task_check, Check_Entry, osPriorityIdle, 0, 128);
  Task_checkHandle = osThreadCreate(osThread(Task_check), NULL);

  /* definition and creation of Task_InertialNa */
  osThreadDef(Task_InertialNa, InertialNavigation_Entry, osPriorityIdle, 0, 128);
  Task_InertialNaHandle = osThreadCreate(osThread(Task_InertialNa), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	osTimerStart(myTimer01Handle,1);
	myEventGroupHandle_check=xEventGroupCreate();//创建事件组
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
	
		LED_struct_init(&led_g,LED_GPIO_Port,LED_Pin);
	
		encoder_struct_init(&encoder_1,ENCODER_HTIM_1,ENCODER_BASE_1);
	
		encoder_struct_init(&encoder_2,ENCODER_HTIM_2,ENCODER_BASE_2);
		
		encoder_struct_init(&encoder_3,ENCODER_HTIM_3,ENCODER_BASE_3);
		
		encoder_struct_init(&encoder_4,ENCODER_HTIM_4,ENCODER_BASE_4);
		
		XBOX_struct_init(&XBOX,XBOX_USART,XBOX_USART_BASE);
		
		HMI_struct_init(&hmi, HMI1_USART, HMI1_USART_BASE);
	
		MOTOR_struct_init(&motor1,MOTOR_1_DIR_GPIO_Port,MOTOR_1_DIR_Pin,M1_TIM,M1_CHANNEL);
	//右上
	
		MOTOR_struct_init(&motor2,MOTOR_2_DIR_GPIO_Port,MOTOR_2_DIR_Pin,M2_TIM,M2_CHANNEL);
	//左上
	
		MOTOR_struct_init(&motor3,MOTOR_3_DIR_GPIO_Port,MOTOR_3_DIR_Pin,M3_TIM,M3_CHANNEL);
		//左下
		
		MOTOR_struct_init(&motor4,MOTOR_4_DIR_GPIO_Port,MOTOR_4_DIR_Pin,M4_TIM,M4_CHANNEL);
		//右下
		
		PID_struct_init(&pid_all.pid_speed[1],DELTA_PID,500,100,1,0,0,1500,0);
	
		PID_struct_init(&pid_all.pid_speed[2],DELTA_PID,500,100,1,0,0,1500,0);
		
		PID_struct_init(&pid_all.pid_speed[3],DELTA_PID,500,100,1,0,0,1500,0);
		
		PID_struct_init(&pid_all.pid_speed[4],DELTA_PID,500,100,1,0,0,1500,0);
		
		PID_struct_init(&pid_all.pid_angle,POSITION_PID,100,50,1,0,0,1500,2);
		

		pid_all.pid_angle.f_pid_reset(&pid_all.pid_angle, 0.388f, 0.000f, 1.888f);
//		pid_all.pid_angle.f_pid_reset(&pid_all.pid_angle, 0.888f, 0.000f, 0.888f);
		
		if(IMU660RA_SWITCH)
		{
			printf("init_imu\r\n");
		
			imu_struct_init(&imu660ra,IMU_SPI,IMU_CS_GPIO_Port,IMU_CS_Pin);
	
			imu660ra.imu660ra_init(&imu660ra);
		}

  /* Infinite loop */
  for(;;)
  {

    osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Motor_Entry */
void usb_xbox_todata(float* data_enc,float* data_imu,float* data_imu_tag, XBOX_DATA* XBOX_data, float p1, float p2, float p3);
/**
* @brief Function implementing the Task_Motor thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motor_Entry */
void Motor_Entry(void const * argument)
{
  /* USER CODE BEGIN Motor_Entry */

	static float times = 0;
	
	if(!MOTOR_SWITCH)
	{
		vTaskSuspend(NULL);
	}
		printf("motor_init_ok\r\n");
  /* Infinite loop */
  for(;;)
  {

		times ++;
		if(times > 1000)
		{
		}
		if(times < 1000)
		{
		}  
		if(times > 2000)
		{
			times = 0;
		}

		
		USB_analysis();


		if(usb.get_data == 1)
		{
	
			usb_xbox_todata(&encoder_1.g_encoder_target, &CAR_YAW, &CAR_YAW_TARGET, &usb.XBOX_data,  -0.4f, -0.11f, 1);
			
			usb_xbox_todata(&encoder_2.g_encoder_target, &CAR_YAW, &CAR_YAW_TARGET, &usb.XBOX_data,  -0.4f, 0.11f, -1);
			
			usb_xbox_todata(&encoder_3.g_encoder_target, &CAR_YAW, &CAR_YAW_TARGET, &usb.XBOX_data,  -0.4f, 0.11f, -1);
			
			usb_xbox_todata(&encoder_4.g_encoder_target, &CAR_YAW, &CAR_YAW_TARGET, &usb.XBOX_data,  -0.4f, -0.11f, 1);
						
			usb_xbox_todata_run( &usb.XBOX_data, 0.88f);
			
		
		}
		else if(0)			//测试角度环
		{
				encoder_1.g_encoder_target = 0;
				encoder_2.g_encoder_target = 0;
				encoder_3.g_encoder_target = 0;
				encoder_4.g_encoder_target = 0;

			
				static float temp = 0, temp_L = 0;
				temp = pid_all.pid_angle.f_cal_pid(&pid_all.pid_angle, CAR_YAW, CAR_YAW_TARGET);
				temp = RCFilter(temp, temp_L, 0.4);
				temp_L = temp;
				encoder_1.g_encoder_target += temp;
				encoder_2.g_encoder_target -= temp;
				encoder_3.g_encoder_target -= temp;
				encoder_4.g_encoder_target += temp;
			

		}
		else
		{
				encoder_1.g_encoder_target = 0;
				encoder_2.g_encoder_target = 0;
				encoder_3.g_encoder_target = 0;
				encoder_4.g_encoder_target = 0;
			
				CAR_YAW_TARGET = CAR_YAW;		

		}
				
    osDelay(1);
  }
  /* USER CODE END Motor_Entry */
}

/* USER CODE BEGIN Header_Check_Entry */
/**
* @brief Function implementing the Task_check thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Check_Entry */
void Check_Entry(void const * argument)
{
  /* USER CODE BEGIN Check_Entry */
	if(!CHECK_SWITCH)
	{
		vTaskSuspend(NULL);
	}
	osDelay(2000);
	
  /* Infinite loop */
  for(;;)
  {
		osThreadSuspend(NULL);
		
		if(check_obj == check_motor)
		{
				osThreadSuspendAll();
				all_motor_check();
				osThreadResumeAll();
		}
		else if(check_obj == check_imu)
		{
			imu660ra.imu660ra_to_hmi(&imu660ra);
		}
		else if(check_obj == check_enc)
		{
				osThreadSuspend(Task_MotorHandle);
				encoder_to_hmi();
		}
		else if(check_obj == check_xbox)
		{
			osThreadSuspend(Task_MotorHandle);
			USB_analysis();
			xbox_to_hmi();
		}


		
    osDelay(2);
  }
  /* USER CODE END Check_Entry */
}

/* USER CODE BEGIN Header_InertialNavigation_Entry */


/**
* @brief Function implementing the Task_InertialNa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_InertialNavigation_Entry */
void InertialNavigation_Entry(void const * argument)
{
  /* USER CODE BEGIN InertialNavigation_Entry */
	

	float temp_imu = 0, temp_imu_L = 0;
  /* Infinite loop */
  for(;;)
  {
		if(Inertial_SWITCH)
		{
			inertial_car.encoder_all = encoder_1.g_encoder_date_all_IN + encoder_2.g_encoder_date_all_IN + encoder_3.g_encoder_date_all_IN + encoder_4.g_encoder_date_all_IN ;

			if(inertial_car.save_run == Inertial_Save_start)
			{
				clear_pwm();
				if(abs(inertial_car.encoder_all) > inertial_car.save_time)
				{
					if(inertial_car.encoder_all > 0 && inertial_car.return_go == 1)
						inertial_car.negitive[inertial_car.in_index] = 0;
					else
						inertial_car.negitive[inertial_car.in_index] = 1;
					
					
					inertial_car.encoder_all = 0;
					encoder_1.g_encoder_date_all_IN = encoder_2.g_encoder_date_all_IN = encoder_3.g_encoder_date_all_IN = encoder_4.g_encoder_date_all_IN = 0;
					
					inertial_car.save_in[inertial_car.in_index] = CAR_YAW;
					if(inertial_car.in_index < Save_Num - 10)
					{
						inertial_car.in_index++;
						
					}
					
				}

			}
			if(inertial_car.save_run == Inertial_Run_ready)
			{
				inertial_car.in_index_all = inertial_car.in_index;
				inertial_car.in_index = 0;
				inertial_car.save_run = Inertial_Run;
				inertial_car.encoder_all = 0;
				encoder_1.g_encoder_date_all_IN = encoder_2.g_encoder_date_all_IN = encoder_3.g_encoder_date_all_IN = encoder_4.g_encoder_date_all_IN = 0;
				
			}
		
			if(inertial_car.save_run == Inertial_Run && inertial_car.in_index_all > 1)
			{
				if(inertial_car.negitive[inertial_car.in_index] == 1 && inertial_car.return_go == 1)
				{
					set_speed(-7);
				}
				else
				{
					set_speed(7);
				}
				if(abs(inertial_car.encoder_all) > inertial_car.save_time)
				{
					
					if(inertial_car.in_index_all > inertial_car.in_index)
					{
						
							//-----------------速度环-----------------------
						
					
							//---------------角度环----------------------
						CAR_YAW_TARGET = inertial_car.save_in[inertial_car.in_index];

											
						if(inertial_car.in_index < Save_Num - 10)
							inertial_car.in_index++;
						
					}
					else
					{
						inertial_car.save_run = Inertial_Run_Stop;
						set_speed(0);
						CAR_YAW_TARGET = inertial_car.save_in[inertial_car.in_index-1];
					}					
					inertial_car.encoder_all = 0;
					encoder_1.g_encoder_date_all_IN = encoder_2.g_encoder_date_all_IN = encoder_3.g_encoder_date_all_IN = encoder_4.g_encoder_date_all_IN = 0;
				}
				
					temp_imu = pid_all.pid_angle.f_cal_pid(&pid_all.pid_angle, CAR_YAW, CAR_YAW_TARGET);
					if(temp_imu != 0)
					{
						temp_imu = RCFilter(temp_imu, temp_imu_L, 0.4);
						
					}
					temp_imu_L = temp_imu;
					
					encoder_1.g_encoder_target +=  1 * temp_imu;
					encoder_2.g_encoder_target += -1 * temp_imu;
					encoder_3.g_encoder_target += -1 * temp_imu;
					encoder_4.g_encoder_target +=  1 * temp_imu;

			}
			else if(inertial_car.save_run == Inertial_Run_Stop)
			{
						set_speed(0);
												//---------------角度环----------------------
			
						temp_imu = pid_all.pid_angle.f_cal_pid(&pid_all.pid_angle, CAR_YAW, CAR_YAW_TARGET);
						temp_imu = RCFilter(temp_imu, temp_imu_L, 0.4);
						temp_imu_L = temp_imu;
						encoder_1.g_encoder_target +=  1 * temp_imu;
						encoder_2.g_encoder_target += -1 * temp_imu;
						encoder_3.g_encoder_target += -1 * temp_imu;
						encoder_4.g_encoder_target +=  1 * temp_imu;				
						
			}
	
		}
		
		
    osDelay(1);
  }
  /* USER CODE END InertialNavigation_Entry */
}

/* Callback01 function */
void Callback01(void const * argument)
{
  /* USER CODE BEGIN Callback01 */
	
	static int times = 0;
	times++;
	if(times >= 1000)
	{
		led_g.Toggle(&led_g);
		times = 0;
	}

	encoder_1.encoder_get(&encoder_1, 1, 1);
	encoder_2.encoder_get(&encoder_2, 2, 1);
	encoder_3.encoder_get(&encoder_3, 3, 1);
	encoder_4.encoder_get(&encoder_4, 4, 1);
	
	encoder_1.g_encoder_date_L = encoder_1.g_encoder_date;
	encoder_1.g_encoder_date = RCFilter(encoder_1.g_encoder_date,encoder_1.g_encoder_date_L , 0.1f);
	
	encoder_2.g_encoder_date_L = encoder_2.g_encoder_date;
	encoder_2.g_encoder_date = RCFilter(encoder_2.g_encoder_date,encoder_2.g_encoder_date_L , 0.1f);
	
	encoder_3.g_encoder_date_L = encoder_3.g_encoder_date;
	encoder_3.g_encoder_date = RCFilter(encoder_3.g_encoder_date,encoder_3.g_encoder_date_L , 0.1f);
	
	encoder_4.g_encoder_date_L = encoder_4.g_encoder_date;
	encoder_4.g_encoder_date = RCFilter(encoder_4.g_encoder_date,encoder_4.g_encoder_date_L , 0.1f);
	
	if(imu660ra.gyroOffset_ok)
	{
		imu660ra.imu660ra_get(&imu660ra);
	
	}

		//-----------------速度环-----------------------
		
	if(inertial_car.save_run >= Inertial_Run || usb.get_data == 1)
	{
		fabs(encoder_1.g_encoder_target) < 5?pid_all.pid_speed[1].f_pid_reset(&pid_all.pid_speed[1], 38.088f, 0.28f, -3.0f):pid_all.pid_speed[1].f_pid_reset(&pid_all.pid_speed[1], 4.088f, 0.188f, 7.888f);
		fabs(encoder_2.g_encoder_target) < 5?pid_all.pid_speed[2].f_pid_reset(&pid_all.pid_speed[2], 38.088f, 0.28f, -3.0f):pid_all.pid_speed[2].f_pid_reset(&pid_all.pid_speed[2], 4.088f, 0.188f, 7.888f);
		fabs(encoder_3.g_encoder_target) < 5?pid_all.pid_speed[3].f_pid_reset(&pid_all.pid_speed[3], 38.088f, 0.28f, -3.0f):pid_all.pid_speed[3].f_pid_reset(&pid_all.pid_speed[3], 4.088f, 0.188f, 7.888f);
		fabs(encoder_4.g_encoder_target) < 5?pid_all.pid_speed[4].f_pid_reset(&pid_all.pid_speed[4], 38.088f, 0.28f, -3.0f):pid_all.pid_speed[4].f_pid_reset(&pid_all.pid_speed[4], 4.088f, 0.188f, 7.888f);
		
		
		motor1.pwm = (int)pid_all.pid_speed[1].f_cal_pid(&pid_all.pid_speed[1], encoder_1.g_encoder_date, encoder_1.g_encoder_target);
		motor2.pwm = (int)pid_all.pid_speed[2].f_cal_pid(&pid_all.pid_speed[2], encoder_2.g_encoder_date, encoder_2.g_encoder_target);
		motor3.pwm = (int)pid_all.pid_speed[3].f_cal_pid(&pid_all.pid_speed[3], encoder_3.g_encoder_date, encoder_3.g_encoder_target);
		motor4.pwm = (int)pid_all.pid_speed[4].f_cal_pid(&pid_all.pid_speed[4], encoder_4.g_encoder_date, encoder_4.g_encoder_target);
			
		motor1.pwm = (int)RCFilter((float)motor1.pwm, (float)motor1.pwm_L, 0.38f);
		motor1.pwm_L = motor1.pwm;
		
		motor2.pwm = (int)RCFilter((float)motor2.pwm, (float)motor2.pwm_L, 0.38f);
		motor2.pwm_L = motor2.pwm;
		
		motor3.pwm = (int)RCFilter((float)motor3.pwm, (float)motor3.pwm_L, 0.38f);
		motor3.pwm_L = motor3.pwm;
		
		motor4.pwm = (int)RCFilter((float)motor4.pwm, (float)motor4.pwm_L, 0.38f);
		motor4.pwm_L = motor4.pwm;

		
		motor1.motor_update_pwm(&motor1,1);
		motor2.motor_update_pwm(&motor2,2);
		motor3.motor_update_pwm(&motor3,3);
		motor4.motor_update_pwm(&motor4,4);
	}


		
  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
