
#ifndef __INERTIAL_H__
#define __INERTIAL_H__


#include "main.h"
#include <stdbool.h>
#define Save_Num  10000
#define SAVE_TIME 200
typedef struct inertial_
{
	int save_run ;
	int save_time ;
	int in_index ;
	int encoder_all ;
	int in_index_all ;
	
	bool negitive[Save_Num] ;
	
	bool return_go;

	float save_in[Save_Num];
	
}inertial_x;

#define Inertial_Save_start  	1
#define Inertial_Save_stop  	2
#define Inertial_Run_ready		3
#define Inertial_Run			 		4
#define Inertial_Run_Stop			5

extern inertial_x inertial_car;

#endif 

