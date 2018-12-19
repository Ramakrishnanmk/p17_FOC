/*
 * cu_state.h
 *
 *  Created on: 23-Oct-2017
 *      Author: Ram
 */

#ifndef CU_STATE_H_
#define CU_STATE_H_

extern int test_left_pwm;
extern int test_right_pwm;

typedef enum {
    CuState_STARTUP_1OF3,
    CuState_STARTUP_2OF3,
    CuState_STARTUP_3OF3,
    CuState_RUN,
    CuState_SHUTDOWN
} CuState_t;

void CuState_startup_1of3(void);
void CuState_startup_2of3(void);
void CuState_startup_3of3(void);
void run(void);
void shutdown(void);
void CuState_mainFunction(void);
CuState_t CuState_get    (void);
void Delay_ms(float delay_ms);
void Openloop_pwmtest(int duty_l, int duty_r);
#endif /* CU_STATE_H_ */
