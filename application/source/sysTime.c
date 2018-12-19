/*
 * sysTime.c
 *
 *  Created on: 22-Sep-2017
 *      Author: Ram
 */

#include "sysTime.h"

SysTime_t d_sysTime;

void SysTime_init(void)
{
    d_sysTime.relUsec = SYS_TIME_USEC_TO_MSEC;
    d_sysTime.relMsec = SYS_TIME_MSEC_TO_SEC;
    d_sysTime.relSec = SYS_TIME_SEC_TO_MIN;

    d_sysTime.usec = 0;
    d_sysTime.msec = 0;
    d_sysTime.sec  = 0;
    d_sysTime.minute  = 0;
    d_sysTime.longMsec = 0;
}


/******************************************************************************
*
******************************************************************************/
//#pragma CODE_SECTION(SysTime_mainFunction_tick, "ramfuncs");
void SysTime_mainFunction_tick(void)
{
    if (d_sysTime.relUsec == 0) {
        d_sysTime.relUsec = SYS_TIME_USEC_TO_MSEC;
        d_sysTime.usec += (Uint32) (SYS_TIME_CFG_USEC_PER_TICK);
        if (d_sysTime.relMsec == 0) {
            d_sysTime.relMsec = SYS_TIME_MSEC_TO_SEC;
            d_sysTime.msec++;
            d_sysTime.longMsec++;
            if (d_sysTime.relSec == 0) {
                d_sysTime.relSec = SYS_TIME_SEC_TO_MIN;
                d_sysTime.sec++;
                d_sysTime.minute++;
            }
            else {
                d_sysTime.relSec--;
                d_sysTime.sec++;
            }
        }
        else {
            d_sysTime.relMsec--;
            d_sysTime.msec++;
            d_sysTime.longMsec++;
        }
    }
    else {
        d_sysTime.relUsec--;
        d_sysTime.usec += (Uint32) (SYS_TIME_CFG_USEC_PER_TICK);
    }
}


/******************************************************************************
*
******************************************************************************/
bool SysTime_usecIntervalElapsed(Uint32 startTime, Uint32 interval)
{
    return ((Uint32)(d_sysTime.usec - startTime) >= interval)?TRUE:FALSE;
}


bool SysTime_msecIntervalElapsed(Uint32 startTime, Uint32 interval)
{
    return ((Uint32)(d_sysTime.msec - startTime) >= interval)?TRUE:FALSE;
}


bool SysTime_secIntervalElapsed(Uint32 startTime, Uint32 interval)
{
    return ((Uint32)(d_sysTime.sec - startTime) >= interval)?TRUE:FALSE;
}


bool SysTime_minuteIntervalElapsed(Uint32 startTime, Uint32 interval)
{
    return ((Uint32)(d_sysTime.minute - startTime) >= interval)?TRUE:FALSE;
}


/******************************************************************************
*
******************************************************************************/
Uint32 SysTime_getUsec(void)
{
    return (d_sysTime.usec);
}


Uint32 SysTime_getMsec(void)
{
    return (d_sysTime.msec);
}
Uint64 SysTime_getlongMsec(void)
{
    return (d_sysTime.longMsec);
}

Uint32 SysTime_getSec(void)
{
    return (d_sysTime.sec);
}


Uint32 SysTime_getMinute(void)
{
    return (d_sysTime.minute);
}

void SysTime_setTime(Uint64 time_in_seconds)
{
    d_sysTime.longMsec = time_in_seconds;
    d_sysTime.longMsec = d_sysTime.longMsec * 1000;
}
