/*
 * cu_state.c
 *
 *  Created on: 23-Oct-2017
 *      Author: Ram
 */
#include "cu_state.h"
#include "mcu_init.h"
#include "scheduler.h"
#include "pll.h"
#include "inverter.h"

//int test_left_pwm = 10000, test_right_pwm = 10000;                      //delete after test

CuState_t d_cuState = CuState_STARTUP_1OF3;
void CuState_startup_1of3(){
    McuInit_clockAndMemory();
    McuInit_interrupt();
    // Done with first part of startup change state.
    d_cuState = CuState_STARTUP_2OF3;
}


void CuState_startup_2of3()
{
    SysTime_init();
    McuInit_port();
    McuInit_pwm();
    ConfigAdc();
    Adc_init();
    McuInit_xint();
    init_pll();
    init_invLoopParams();
    d_cuState = CuState_STARTUP_3OF3;
}
void CuState_startup_3of3(){
    // This is where we initialize the higher layer components that require
    // interrupts, peripherals and scheduler to be turned ON before they
    // can be started.

    //qep_posspeed.init(&qep_posspeed);
    // Done with third part of startup.
    //Wdg_Init();        //Initialize WDG manager
    d_cuState = CuState_RUN;
}
void run(){
    // Stay running until it is time to shutdown...
    // while(!RequestShutDown){};

    //WDG_service();  // Service WDG just before enabling
     d_cuState = CuState_RUN;
}
void shutdown(){
    // Do graceful shutdown of components.
    // For example, allow eeprom write to finish
    d_cuState = CuState_SHUTDOWN;
}
void CuState_mainFunction(){

    switch(d_cuState) {
        case CuState_STARTUP_1OF3:
            CuState_startup_1of3();
            break;
        case CuState_STARTUP_2OF3:
            CuState_startup_2of3();
            break;
        case CuState_STARTUP_3OF3:
            CuState_startup_3of3();
            break;
        case CuState_RUN:
            run();
            break;
        case CuState_SHUTDOWN:
            shutdown();
            break;
        default:
            // Why are we lost? Recover by staying in while loop without
            // feeding the watch dog. Hence we get a watchdog reset and start
            // anew.
            while(1){};
    }
}

CuState_t CuState_get(){
    return(d_cuState);
}
