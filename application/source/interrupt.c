/*
 * interrupt.c
 *
 *  Created on: 23-Oct-2017
 *      Author: Ram
 */
#include "interrupt.h"
#include "sysTime.h"
#include "mcu_init.h"
#include "pll.h"
#include "adc.h"
#include "inverter.h"
#include "hw_abstraction.h"

//void adc_mainFunction_foreground_1of2(void);
void Int_install(){
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.ADCA1_INT = &adc_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers
}
__interrupt void adc_isr(void){
//    GPIO_WritePin(TEST_TOGGLE, 1);
    SysTime_mainFunction_tick();
    adc_mainFunction_foreground_1of2();
    invControl();
//    GPIO_WritePin(TEST_TOGGLE, 0);
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
