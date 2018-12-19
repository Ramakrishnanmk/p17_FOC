/*
 * interrupt.h
 *
 *  Created on: 23-Oct-2017
 *      Author: Ram
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
//#include "posspeed.h"

__interrupt void adc_isr(void);
void Int_install(void);
void inverterControl(void);

#define MOTOR_TIME_PRD  2000
#define R_RELEASE                               EPwm1Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm1Regs.AQCSFRC.bit.CSFB = 00;

#define Y_RELEASE                               EPwm2Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm2Regs.AQCSFRC.bit.CSFB = 00;

#define B_RELEASE                               EPwm3Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm3Regs.AQCSFRC.bit.CSFB = 00;

#define R_COMPLEMENTARY_FRC                     EPwm1Regs.DBCTL.bit.OUT_MODE = 3;\
                                                EPwm1Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm1Regs.AQCSFRC.bit.CSFB = 00;\
                                                EPwm1Regs.AQCSFRC.bit.CSFA = 01;\
                                                EPwm1Regs.AQCSFRC.bit.CSFB = 10;

#define Y_COMPLEMENTARY_FRC                     EPwm2Regs.DBCTL.bit.OUT_MODE = 3;\
                                                EPwm2Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm2Regs.AQCSFRC.bit.CSFB = 00;\
                                                EPwm2Regs.AQCSFRC.bit.CSFA = 01;\
                                                EPwm2Regs.AQCSFRC.bit.CSFB = 10;

#define B_COMPLEMENTARY_FRC                     EPwm3Regs.DBCTL.bit.OUT_MODE = 3;\
                                                EPwm3Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm3Regs.AQCSFRC.bit.CSFB = 00;\
                                                EPwm3Regs.AQCSFRC.bit.CSFA = 01;\
                                                EPwm3Regs.AQCSFRC.bit.CSFB = 10;

#define R_COMPLETE_FRC                          EPwm1Regs.DBCTL.bit.OUT_MODE = 0;\
                                                EPwm1Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm1Regs.AQCSFRC.bit.CSFB = 00;\
                                                EPwm1Regs.AQCSFRC.bit.CSFA = 01;\
                                                EPwm1Regs.AQCSFRC.bit.CSFB = 01;

#define Y_COMPLETE_FRC                          EPwm2Regs.DBCTL.bit.OUT_MODE = 0;\
                                                EPwm2Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm2Regs.AQCSFRC.bit.CSFB = 00;\
                                                EPwm2Regs.AQCSFRC.bit.CSFA = 01;\
                                                EPwm2Regs.AQCSFRC.bit.CSFB = 01;

#define B_COMPLETE_FRC                          EPwm3Regs.DBCTL.bit.OUT_MODE = 0;\
                                                EPwm3Regs.AQCSFRC.bit.CSFA = 00;\
                                                EPwm3Regs.AQCSFRC.bit.CSFB = 00;\
                                                EPwm3Regs.AQCSFRC.bit.CSFA = 01;\
                                                EPwm3Regs.AQCSFRC.bit.CSFB = 01;

#define DUTY_R(duty_r)                          EPwm1Regs.DBCTL.bit.OUT_MODE = 3;EPwm1Regs.CMPA.bit.CMPA = duty_r;

#define DUTY_Y(duty_y)                          EPwm2Regs.DBCTL.bit.OUT_MODE = 3;EPwm2Regs.CMPA.bit.CMPA = duty_y;

#define DUTY_B(duty_b)                          EPwm3Regs.DBCTL.bit.OUT_MODE = 3;EPwm3Regs.CMPA.bit.CMPA = duty_b;


#endif /* INTERRUPT_H_ */
