/*
 * mcu_init.h
 *
 *  Created on: 23-Oct-2017
 *      Author: Ram
 */

#ifndef MCU_INIT_H_
#define MCU_INIT_H_
#include "F28x_Project.h"
//#include "posspeed.h"
#include "sysTime.h"


void McuInit_clockAndMemory(void);
void McuInit_interrupt(void);
void McuInit_port        (void);
void McuInit_gpt         (void);
//void McuInit_ecap          (void);
void McuInit_pwm       (void);
//void McuInit_adc_1of2      (void);
//void McuInit_adc_2of2      (void);
void McuInit_scib           (void);
void McuInit_wdg        (void);
void Epwm1_init         (void);
void Epwm2_init         (void);
void Epwm3_init         (void);
void Epwm4_init         (void);
void Epwm5_init         (void);
void Epwm6_init         (void);
void Epwm7_init         (void);
void Epwm8_init         (void);
void McuInit_xint       (void);
//void McuInit_xint1         (void);  //ram
//void McuInit_xint2         (void);
//void McuInit_xint3         (void);
//void McuInit_xint7         (void);
void McuInit_ecan      (void);
void McuInit_eqep      (void);
void initEpwm             (void);
void McuInit_i2c         (void);
void McuInit_Leds(void);
void InitI2cAGpio(void);
void toggle_LED(Uint16 GPIO, Uint16 no_of_times, Uint16 delay);
void InitElockGpio(void);
void InitRearmotorGpio(void);
void InitBuzzerGpio(void);
void ConfigAdc  (void);
void Adc_init         (void);

#endif /* MCU_INIT_H_ */
