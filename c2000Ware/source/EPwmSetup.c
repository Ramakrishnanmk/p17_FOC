//###########################################################################
//
// FILE:    Example_EpwmSetup.c
//
// TITLE:   Pos speed measurement using EQEP peripheral
//
// DESCRIPTION:
//
// This file contains source for the ePWM initialization for the
// pos/speed module
//
//###########################################################################
// $TI Release: F2837xD Support Library v210 $
// $Release Date: Tue Nov  1 14:46:15 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
//#include "rearWheelControl.h"

//
// Defines
//
#define TB_CLK    100e6
#define PWM_CLK   5e3              // 10kHz frequency for PWM in up-down count mode
#define SP        TB_CLK/(2*PWM_CLK)
#define TBCTLVAL  0x200A           // up-down count, timebase=SYSCLKOUT


#define REARMOTOR_TIMER_TBPRD  2000      //2000  // Period register

#define DISABLE_INT                                                     0
#define ENABLE_INT                                                      1
#define CLKDIV_1                                                        0
#define COUNT_UP_AFTER_SYNC_EVENT                                       1
#define ENABLE_PHASE_SYNC_AT_CTR_ZERO                                   1
#define DISABLE_PHASE_SYNC                                              3
#define PHASE_SYNC_AT_CTR_ZERO                                          1
#define DISABLE_PHASE                                                   0
#define ENABLE_PHASE                                                    1
#define UP_MODE                                                         0
#define DOWN_MODE                                                       1
#define UP_DOWN_MODE                                                    2
#define DIV_1                                                           0
#define LOAD_IN_SHADOW_REG                                              0
#define LOAD_DURING_UNDERFLOW                                           0
#define PULL_HIGH                                                       2
#define PULL_LOW                                                        1
#define POLARITY                                        				2

void initEpwm()
{
    // InitEPwm1
      EPwm1Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM1_INT
      EPwm1Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
      EPwm1Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
      EPwm1Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
      EPwm1Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
      EPwm1Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
      EPwm1Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
      EPwm1Regs.TBCTR = 0;
      EPwm1Regs.TBPRD = 6250; //2000;
      EPwm1Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
      EPwm1Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
      EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
      EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
      EPwm1Regs.CMPA.bit.CMPA = 0;
      EPwm1Regs.CMPB.bit.CMPB = 0;
      EPwm1Regs.DBCTL.bit.POLSEL = POLARITY;
      EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
      EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;
      EPwm1Regs.AQCTLA.bit.CAU = PULL_HIGH;
      EPwm1Regs.AQCTLA.bit.CAD = PULL_LOW;
      EPwm1Regs.AQCTLB.bit.CBU = PULL_LOW;
      EPwm1Regs.AQCTLB.bit.CBD = PULL_HIGH;
      EPwm1Regs.DBFED.bit.DBFED = 50; //1us
      EPwm1Regs.DBRED.bit.DBRED = 50; //1us
      EPwm1Regs.TBPHS.bit.TBPHS = 0;
      EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;  // SOCA on CMPA event
      EPwm1Regs.ETSEL.bit.SOCBSEL = ET_CTR_PRD;  // SOCB on CMPA event
      EPwm1Regs.ETSEL.bit.SOCAEN = 0x1;              // Enable SOC on A group
      EPwm1Regs.ETSEL.bit.SOCBEN = 0x1;              // Enable SOC on B group
      EPwm1Regs.ETPS.bit.SOCAPRD = ET_1ST;         // Trigger on every event
      EPwm1Regs.ETPS.bit.SOCBPRD = ET_1ST;         // Trigger on every event
//      EPwm1Regs.TBCTL.bit.FREE_SOFT = 0x10;

      // InitEPwm2
      EPwm2Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM2_INT
      EPwm2Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
      EPwm2Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
      EPwm2Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
      EPwm2Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
      EPwm2Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
      EPwm2Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
      EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
      EPwm2Regs.TBCTR = 0;
      EPwm2Regs.TBPRD = 6250; //2000;
      EPwm2Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
      EPwm2Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
      EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
      EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
      EPwm2Regs.CMPA.all = 0;
      EPwm2Regs.CMPB.all = 0;
      EPwm2Regs.DBCTL.bit.POLSEL = POLARITY;
      EPwm2Regs.DBCTL.bit.OUT_MODE = 3;
      EPwm2Regs.TBPHS.bit.TBPHS = 0;
      EPwm2Regs.TBCTL.bit.PHSDIR = 0;
      EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;
      EPwm2Regs.AQCTLA.bit.CAU = PULL_HIGH;
      EPwm2Regs.AQCTLA.bit.CAD = PULL_LOW;
      EPwm2Regs.AQCTLB.bit.CBU = PULL_LOW;
      EPwm2Regs.AQCTLB.bit.CBD = PULL_HIGH;
      EPwm2Regs.DBFED.bit.DBFED = 50; //1us
      EPwm2Regs.DBRED.bit.DBRED = 50; //1us
//      EPwm2Regs.TBCTL.bit.FREE_SOFT = 0x10;
    // InitEPwm3
      EPwm3Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM2_INT
      EPwm3Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
      EPwm3Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
      EPwm3Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
      EPwm3Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
      EPwm3Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
      EPwm3Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
      EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
      EPwm3Regs.TBCTR = 0;
      EPwm3Regs.TBPRD = 6250; //2000;
      EPwm3Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
      EPwm3Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
      EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
      EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
      EPwm3Regs.CMPA.all = 0;
      EPwm3Regs.CMPB.all = 0;
      EPwm3Regs.DBCTL.bit.POLSEL = POLARITY;
      EPwm3Regs.DBCTL.bit.OUT_MODE = 3;
      EPwm3Regs.TBCTL.bit.PHSDIR = 0;
      EPwm3Regs.TBCTL.bit.SYNCOSEL = 0;
      EPwm3Regs.TBPHS.bit.TBPHS = 0;
      EPwm3Regs.AQCTLA.bit.CAU = PULL_HIGH;
      EPwm3Regs.AQCTLA.bit.CAD = PULL_LOW;
      EPwm3Regs.AQCTLB.bit.CBU = PULL_LOW;
      EPwm3Regs.AQCTLB.bit.CBD = PULL_HIGH;
//      EPwm3Regs.TBCTL.bit.FREE_SOFT = 0x10;
      EPwm3Regs.DBFED.bit.DBFED = 50; //1us
      EPwm3Regs.DBRED.bit.DBRED = 50; //1us

    // InitEPwm4
    EPwm4Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM2_INT
    EPwm4Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
    EPwm4Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
    EPwm4Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
    EPwm4Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
    EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm4Regs.TBCTR = 0;
    EPwm4Regs.TBPRD = 6250; //2000;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPA.all = 0;
    EPwm4Regs.CMPB.all = 0;
    EPwm4Regs.DBCTL.bit.POLSEL = 1;
    EPwm4Regs.DBCTL.bit.OUT_MODE = 3;
    EPwm4Regs.TBCTL.bit.PHSDIR = 0;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = 0;
    EPwm4Regs.TBPHS.bit.TBPHS = 0;
    EPwm4Regs.AQCTLA.bit.CAU = PULL_HIGH;
    EPwm4Regs.AQCTLA.bit.CAD = PULL_LOW;
    EPwm4Regs.AQCTLB.bit.CBU = PULL_LOW;
    EPwm4Regs.AQCTLB.bit.CBD = PULL_HIGH;
    EPwm4Regs.TBCTL.bit.FREE_SOFT = 0x10;
    EPwm4Regs.DBFED.bit.DBFED = 50; //1us
    EPwm4Regs.DBRED.bit.DBRED = 50; //1us

    EPwm9Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM1_INT
    EPwm9Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
    EPwm9Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
    EPwm9Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
    EPwm9Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
    EPwm9Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
    EPwm9Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
    EPwm9Regs.TBCTR = 0;
    EPwm9Regs.TBPRD = 500; //2000;
    EPwm9Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
    EPwm9Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
    EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm9Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm9Regs.CMPA.bit.CMPA = 0;
    EPwm9Regs.CMPB.bit.CMPB = 0;
    EPwm9Regs.DBCTL.bit.POLSEL = 1;
    EPwm9Regs.DBCTL.bit.OUT_MODE = 3;
    EPwm9Regs.TBCTL.bit.SYNCOSEL = 0;
    EPwm9Regs.AQCTLA.bit.CAU = PULL_HIGH;
    EPwm9Regs.AQCTLA.bit.CAD = PULL_LOW;
    EPwm9Regs.AQCTLB.bit.CBU = PULL_LOW;
    EPwm9Regs.AQCTLB.bit.CBD = PULL_HIGH;
    EPwm9Regs.DBFED.bit.DBFED = 50; //1us
    EPwm9Regs.DBRED.bit.DBRED = 50; //1us
    EPwm9Regs.TBPHS.bit.TBPHS = 0;
    EPwm9Regs.TBCTL.bit.FREE_SOFT = 0x10;

    // InitEPwm2
    EPwm11Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM2_INT
    EPwm11Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
    EPwm11Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
    EPwm11Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
    EPwm11Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
    EPwm11Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
    EPwm11Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
    EPwm11Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm11Regs.TBCTR = 0;
    EPwm11Regs.TBPRD = 500; //2000;
    EPwm11Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
    EPwm11Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
    EPwm11Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm11Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm11Regs.CMPA.all = 0;
    EPwm11Regs.CMPB.all = 0;
    EPwm11Regs.DBCTL.bit.POLSEL = 1;
    EPwm11Regs.DBCTL.bit.OUT_MODE = 3;
    EPwm11Regs.TBPHS.bit.TBPHS = 0;
    EPwm11Regs.TBCTL.bit.PHSDIR = 0;
    EPwm11Regs.TBCTL.bit.SYNCOSEL = 0;
    EPwm11Regs.AQCTLA.bit.CAU = PULL_HIGH;
    EPwm11Regs.AQCTLA.bit.CAD = PULL_LOW;
    EPwm11Regs.AQCTLB.bit.CBU = PULL_LOW;
    EPwm11Regs.AQCTLB.bit.CBD = PULL_HIGH;
    EPwm11Regs.DBFED.bit.DBFED = 50; //1us
    EPwm11Regs.DBRED.bit.DBRED = 50; //1us
    EPwm11Regs.TBCTL.bit.FREE_SOFT = 0x10;
    // InitEPwm3
    EPwm10Regs.ETSEL.bit.INTEN = DISABLE_INT;         // Disable EPWM2_INT
    EPwm10Regs.TBCTL.bit.CLKDIV = CLKDIV_1;
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = DIV_1;
    EPwm10Regs.TBCTL.bit.SYNCOSEL = DISABLE_PHASE_SYNC;
    EPwm10Regs.TBCTL.bit.PRDLD = LOAD_IN_SHADOW_REG;
    EPwm10Regs.TBCTL.bit.PHSEN = DISABLE_PHASE;
    EPwm10Regs.TBCTL.bit.CTRMODE = UP_DOWN_MODE;
    EPwm10Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm10Regs.TBCTR = 0;
    EPwm10Regs.TBPRD = 500; //2000;
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = LOAD_IN_SHADOW_REG;
    EPwm10Regs.CMPCTL.bit.SHDWAMODE = LOAD_IN_SHADOW_REG;
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm10Regs.CMPA.all = 0;
    EPwm10Regs.CMPB.all = 0;
    EPwm10Regs.DBCTL.bit.POLSEL = 1;
    EPwm10Regs.DBCTL.bit.OUT_MODE = 3;
    EPwm10Regs.TBCTL.bit.PHSDIR = 0;
    EPwm10Regs.TBCTL.bit.SYNCOSEL = 0;
    EPwm10Regs.TBPHS.bit.TBPHS = 0;
    EPwm10Regs.AQCTLA.bit.CAU = PULL_HIGH;
    EPwm10Regs.AQCTLA.bit.CAD = PULL_LOW;
    EPwm10Regs.AQCTLB.bit.CBU = PULL_LOW;
    EPwm10Regs.AQCTLB.bit.CBD = PULL_HIGH;
    EPwm10Regs.TBCTL.bit.FREE_SOFT = 0x10;
    EPwm10Regs.DBFED.bit.DBFED = 50; //1us
    EPwm10Regs.DBRED.bit.DBRED = 50; //1us
}


//
// End of file
//
