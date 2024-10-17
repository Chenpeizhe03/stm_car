#ifndef __MOTOR_PID_H
#define __MOTOR_PID_H

#include "main.h"


enum
{
    LLAST = 0,
    LAST = 1,
    NOW = 2,

    POSITION_PID,
    DELTA_PID,
};
typedef struct _pid_t
{
    float p;
    float i;
    float d;

    float set[3]; //目标值,包含NOW， LAST， LLAST上上次
    float get[3]; //测量值
    float err[3]; //误差

    float pout; //p输出
    float iout; //i输出
    float dout; //d输出

    float pos_out;      //本次位置式输出
    float last_pos_out; //上次输出
    float delta_u;      //本次增量值
    float delta_out;    //本次增量式输出 = last_delta_out + delta_u
    float last_delta_out;

    float max_err;
    float deadband; //err < deadband return
    uint32_t pid_mode;
    uint32_t MaxOutput;     //输出限幅
    uint32_t IntegralLimit; //积分限幅

    void (*f_param_init)(
					struct _pid_t *pid,
					uint32_t mode,
					uint32_t maxout,
					uint32_t intergral_limit,
					float 	kp,
					float 	ki,
					float 	kd,
					float 	max_err,
					float   deadband);
    void (*f_pid_reset)(struct _pid_t *pid, float p, float i, float d); //pid三个参数修改
					
		float (*f_cal_pid)(struct _pid_t* pid, float get, float set);
					
} pid__t;

typedef struct _pid_all
{
	pid__t pid_speed[5];
	pid__t pid_angle;
	pid__t pid_position;
					
	
} pid_all_;

extern pid_all_ pid_all;

void PID_struct_init(
    pid__t *pid,
    uint32_t mode,			//POSITION_PID or DELTA_PID
    uint32_t maxout,
    uint32_t intergral_limit,

    float kp,
    float ki,
    float kd,
    float max_err,
    float deadband);

float pid_calc(pid__t *pid, float fdb, float ref);

#endif
