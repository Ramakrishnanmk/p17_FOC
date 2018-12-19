/*
 * scheduler.c
 *
 *  Created on: 07-Dec-2017
 *      Author: Ram
 */
#include "F28x_Project.h"
#include "scheduler.h"
#include "sysTime.h"
#include "math.h"
#include "cu_state.h"
#include "pll.h"

Uint32 plltime = 0;
void scheduler(){
    while(1){
        pll_zx();
    }
}



