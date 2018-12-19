/*
 * pll.c
 *
 *  Created on: 21-Aug-2018
 *      Author: Ram
 */
#include "pll.h"
#include "F28x_Project.h"
#include "inverter.h"


#define TIMER_FREQUENCY    200.0E6
#define MAXFREQUENCY    300

float frequency = 0;

void init_pll(){
    EALLOW;
    InitECap1Gpio(81);
    ECap1Regs.ECCTL1.bit.FREE_SOFT = 0x3;
    ECap1Regs.ECCTL1.bit.CAP1POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CAP2POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CAP3POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CAP4POL = EC_RISING;
    ECap1Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;
    ECap1Regs.ECCTL1.bit.CTRRST2 = EC_DELTA_MODE;
    ECap1Regs.ECCTL1.bit.CTRRST3 = EC_DELTA_MODE;
    ECap1Regs.ECCTL1.bit.CTRRST4 = EC_DELTA_MODE;
    ECap1Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
    ECap1Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
    ECap1Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
    ECap1Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
    ECap1Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
    ECap1Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;


    InitECap2Gpio(82);
    ECap2Regs.ECCTL1.bit.FREE_SOFT = 0x3;
    ECap2Regs.ECCTL1.bit.CAP1POL = EC_RISING;
    ECap2Regs.ECCTL1.bit.CAP2POL = EC_RISING;
    ECap2Regs.ECCTL1.bit.CAP3POL = EC_RISING;
    ECap2Regs.ECCTL1.bit.CAP4POL = EC_RISING;
    ECap2Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;
    ECap2Regs.ECCTL1.bit.CTRRST2 = EC_DELTA_MODE;
    ECap2Regs.ECCTL1.bit.CTRRST3 = EC_DELTA_MODE;
    ECap2Regs.ECCTL1.bit.CTRRST4 = EC_DELTA_MODE;
    ECap2Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
    ECap2Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
    ECap2Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
    ECap2Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
    ECap2Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
    ECap2Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;
    EDIS;

    InitECap3Gpio(83);
    ECap3Regs.ECCTL1.bit.FREE_SOFT = 0x3;
    ECap3Regs.ECCTL1.bit.CAP1POL = EC_RISING;
    ECap3Regs.ECCTL1.bit.CAP2POL = EC_RISING;
    ECap3Regs.ECCTL1.bit.CAP3POL = EC_RISING;
    ECap3Regs.ECCTL1.bit.CAP4POL = EC_RISING;
    ECap3Regs.ECCTL1.bit.CTRRST1 = EC_DELTA_MODE;
    ECap3Regs.ECCTL1.bit.CTRRST2 = EC_DELTA_MODE;
    ECap3Regs.ECCTL1.bit.CTRRST3 = EC_DELTA_MODE;
    ECap3Regs.ECCTL1.bit.CTRRST4 = EC_DELTA_MODE;
    ECap3Regs.ECCTL1.bit.CAPLDEN = EC_ENABLE;
    ECap3Regs.ECCTL1.bit.PRESCALE = EC_DIV1;
    ECap3Regs.ECCTL2.bit.CAP_APWM = EC_CAP_MODE;
    ECap3Regs.ECCTL2.bit.CONT_ONESHT = EC_CONTINUOUS;
    ECap3Regs.ECCTL2.bit.SYNCO_SEL = EC_SYNCO_DIS;
    ECap3Regs.ECCTL2.bit.SYNCI_EN = EC_DISABLE;
    ECap3Regs.ECCTL2.bit.TSCTRSTOP = EC_RUN;
    EDIS;
}

#pragma CODE_SECTION(pll_zx,".TI.ramfunc");
void pll_zx(){
    if (ECap1Regs.ECFLG.bit.CEVT1){
        zcDetected = 1;
        frequency = (float)(TIMER_FREQUENCY/ECap1Regs.CAP1);
        if (frequency > MAXFREQUENCY){
            frequency = 0;
        }
        ECap1Regs.ECCLR.bit.CEVT1 = 1;
    }
    else{
        if (speed.SpeedInput == 0){
            frequency_r = 0;
        }
    }
    if (ECap2Regs.ECFLG.bit.CEVT1){
        zcDetected = 1;
        ECap2Regs.ECCLR.bit.CEVT1 = 1;
    }
    if (ECap3Regs.ECFLG.bit.CEVT1){
        zcDetected = 1;
        ECap3Regs.ECCLR.bit.CEVT1 = 1;
    }
    frequency_r = frequency;
}

