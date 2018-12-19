//###########################################################################
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
#include "scheduler.h"
#include "cu_state.h"
#include "interrupt.h"
#include "mcu_init.h"

// Main

void main(void)
{
    CuState_startup_1of3();
    Int_install();
    CuState_startup_2of3();
    CuState_startup_3of3();
    EINT;
    ERTM;
   for(;;)
   {
       scheduler();
   }
}
// End of file
