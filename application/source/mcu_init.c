/*
 * mcu_init.c
 *
 *  Created on: 23-Oct-2017
 *      Author: Ram
 */
#include "mcu_init.h"
#include "F28x_Project.h"
#include "cu_state.h"
#include "hw_abstraction.h"
#include "inverter.h"

void McuInit_clockAndMemory(){

    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2837xD_SysCtrl.c file.

    InitSysCtrl();
    EALLOW;
    ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 2;
    EDIS;
}

void McuInit_interrupt(){
    EALLOW;
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    IER |= M_INT1;// Enable CPU INT1 which is connected to ADCA1:
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
//    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
//    CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
//    CpuSysRegs.PCLKCR2.bit.EPWM3 = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    EDIS;
}
void McuInit_port()
{
    InitEPwmGpio();
    GPIO_SetupPinMux(HAL_A_INPUT, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(HAL_A_INPUT, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(HAL_B_INPUT, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(HAL_B_INPUT, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(HAL_C_INPUT, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(HAL_C_INPUT, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(TEST_TOGGLE, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(TEST_TOGGLE, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(DECODER_IN, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(DECODER_IN, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_WritePin(DECODER_IN, 1);
    GPIO_SetupPinMux(LATCH_DISABLE, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(LATCH_DISABLE, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_WritePin(LATCH_DISABLE, 1);
}
void McuInit_pwm(){
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;  // This bit reset to 0 stops all PWM clocks.
    initEpwm();
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1; // This bit set to 1 turns ON all pwm clocks at the same time
    EDIS;
}
void ConfigAdc (){
    extern void DSP28x_usDelay(Uint32 Count);
    EALLOW;
        AdcaRegs.ADCCTL2.bit.PRESCALE = 2; //div by 1
        AdcbRegs.ADCCTL2.bit.PRESCALE = 2;
        AdccRegs.ADCCTL2.bit.PRESCALE = 2;
        AdcdRegs.ADCCTL2.bit.PRESCALE = 2;
        AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
        AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
        AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
        AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
        AdcaRegs.ADCCTL1.bit.INTPULSEPOS   = 1;
        AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
        AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
        AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
        AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;
        (*Device_cal)();
    EDIS;
//        DELAY_US(1000);
}
void Adc_init (){
    EALLOW;
    AdcaRegs.ADCCTL2.bit.SIGNALMODE = 0; //Single ended
    AdcbRegs.ADCCTL2.bit.SIGNALMODE = 0;
    AdccRegs.ADCCTL2.bit.SIGNALMODE = 0; //Single ended
    AdcdRegs.ADCCTL2.bit.SIGNALMODE = 0;
    //ADCINT1
    AdcaRegs.ADCINTSEL1N2.bit.INT1E       = 1;        //Enabled ADCINT1
    AdcaRegs.ADCINTFLGCLR.all = 0x000F;
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT    = 0;        //Disable ADCINT1 Continuous mode
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL     = 0x05;       //setup EOC6 to trigger ADCINT1 to fire

    AdcaRegs.ADCSOC0CTL.bit.CHSEL    = 4;  //set SOC0 channel select to Ia
    AdcaRegs.ADCSOC1CTL.bit.CHSEL    = 3;  //set SOC6 channel select to Ib
    AdcaRegs.ADCSOC2CTL.bit.CHSEL    = 2;  //set SOC4 channel select to Ic
    AdcaRegs.ADCSOC3CTL.bit.CHSEL    = 1;  //set SOC5 channel select to Y phase voltage
    AdcaRegs.ADCSOC4CTL.bit.CHSEL    = 0;  //set SOC2 channel select to Y phase current
    AdcaRegs.ADCSOC5CTL.bit.CHSEL    = 5;  //set SOC3 channel select to B phase current

//    AdcaRegs.ADCSOC6CTL.bit.CHSEL    = 6;  //set SOC1 channel select to R phase current
//
//    AdcaRegs.ADCSOC7CTL.bit.CHSEL    = 7;  //set SOC7 channel select to DC Bus Neg voltage
//    AdcaRegs.ADCSOC8CTL.bit.CHSEL    = 8;  //set SOC8 channel select to DC Bus Pos voltage
//    AdcaRegs.ADCSOC9CTL.bit.CHSEL    = 9;  //set SOC9 channel select to Heat Sink Temp
//    AdcaRegs.ADCSOC10CTL.bit.CHSEL   = 10;
//    AdcaRegs.ADCSOC11CTL.bit.CHSEL   = 11;
//    AdcaRegs.ADCSOC12CTL.bit.CHSEL   = 12;
//    AdcaRegs.ADCSOC13CTL.bit.CHSEL   = 13;
//    AdcaRegs.ADCSOC14CTL.bit.CHSEL   = 14;
//    AdcaRegs.ADCSOC15CTL.bit.CHSEL   = 15;

    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x5;
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x5;
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 0x5;
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 0x5;
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 0x5;
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC7CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC8CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC9CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC10CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC11CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC12CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC13CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC14CTL.bit.TRIGSEL = 0x5;
//    AdcaRegs.ADCSOC15CTL.bit.TRIGSEL = 0x5;

    AdcaRegs.ADCSOC0CTL.bit.ACQPS  = 30;     //set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcaRegs.ADCSOC1CTL.bit.ACQPS  = 30;     //set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcaRegs.ADCSOC2CTL.bit.ACQPS  = 30;     //set SOC2 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcaRegs.ADCSOC3CTL.bit.ACQPS  = 30;     //set SOC3 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcaRegs.ADCSOC4CTL.bit.ACQPS  = 30;     //set SOC4 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    AdcaRegs.ADCSOC5CTL.bit.ACQPS  = 30;     //set SOC5 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC6CTL.bit.ACQPS  = 58;     //set SOC6 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC7CTL.bit.ACQPS  = 58;     //set SOC7 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC8CTL.bit.ACQPS  = 58;     //set SOC8 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC9CTL.bit.ACQPS  = 58;     //set SOC9 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC10CTL.bit.ACQPS = 58;     //set SOC10 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC11CTL.bit.ACQPS = 58;     //set SOC11 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC12CTL.bit.ACQPS = 58;     //set SOC12 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC13CTL.bit.ACQPS = 58;     //set SOC13 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
//    AdcaRegs.ADCSOC14CTL.bit.ACQPS = 58;     //set SOC14 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)

    EDIS;
}
void McuInit_xint(){
    EALLOW;
//    XintRegs.XINT1CR.bit.POLARITY = 01;
//    XintRegs.XINT1CR.bit.ENABLE = 1;
//    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;         // GPIO
//    GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;          // input
//    GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;        // XINT1 Synch to SYSCLKOUT only
    EDIS;
}
