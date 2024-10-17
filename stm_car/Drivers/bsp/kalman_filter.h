/*
 * FileName : kalman_filter.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : 2014/9/24 20:37:01
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef  _KALMAN_FILTER_H
#define  _KALMAN_FILTER_H


/* 
 * NOTES: n Dimension means the state is n dimension, 
 * measurement always 1 dimension 
 */

/* 1 Dimension */
typedef struct kalman1_state_
{
    float x;  /* state */
    float A;  /* x(n)=A*x(n-1)+u(n),u(n)~N(0,q) */
    float H;  /* z(n)=H*x(n)+w(n),w(n)~N(0,r)   */
    float q;  /* process(predict) noise convariance */
    float r;  /* measure noise convariance */
    float p;  /* estimated error convariance */
    float gain;
	
		void (*kalman1_param_init)(struct kalman1_state_ *state);
	
		float (*kalman1_filter)(struct kalman1_state_ *state, float z_measure);
	
} kalman1_state;

/* 2 Dimension */
typedef struct kalman2_state_
{
    float x[2];     /* state: [0]-angle [1]-diffrence of angle, 2x1 */
    float A[2][2];  /* X(n)=A*X(n-1)+U(n),U(n)~N(0,q), 2x2 */
    float H[2];     /* Z(n)=H*X(n)+W(n),W(n)~N(0,r), 1x2   */
    float q[2];     /* process(predict) noise convariance,2x1 [q0,0; 0,q1] */
    float r;        /* measure noise convariance */
    float p[2][2];  /* estimated error convariance,2x2 [p0 p1; p2 p3] */
    float gain[2];  /* 2x1 */
	
		void (*kalman2_param_init)(struct kalman2_state_ *state ,float A_0_1 );
	
		float (*kalman2_filter)(struct kalman2_state_ *state, float z_measure);
	
} kalman2_state;                   

extern kalman1_state state1;
extern kalman2_state state2;

void kalman2_struct_init( kalman2_state *state, float A_0_1 );

void kalman1_struct_init(
    kalman1_state *state,
    float init_x, float init_p);


#endif  /*_KALMAN_FILTER_H*/

