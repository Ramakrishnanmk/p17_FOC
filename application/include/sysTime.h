/*
 * sysTime.h
 *
 *  Created on: 22-Sep-2017
 *      Author: Ram
 */

#ifndef SYSTIME_H_
#define SYSTIME_H_

#include "F2837xD_device.h"

#define SYS_TIME_CFG_USEC_PER_TICK 40
#define SYS_TIME_USEC_TO_MSEC  (Uint16)((1000.0f / SYS_TIME_CFG_USEC_PER_TICK)-1)
#define SYS_TIME_MSEC_TO_SEC   999
#define SYS_TIME_SEC_TO_MIN    59

typedef struct {
    Uint32 usec;        // System timers since power up
    Uint32 msec;
    Uint32 sec;
    Uint32 minute;
    Uint32 relSec;      // System timer wheels relative to fundamental tick.
    Uint32 relMsec;
    Uint32 relUsec;
    Uint32 longMsec;    //64bit
} SysTime_t;

//SysTime_t d_sysTime;

void SysTime_init(void);


/******************************************************************************
*
******************************************************************************/
void SysTime_mainFunction_tick(void);


/******************************************************************************
*
******************************************************************************/
Uint32 SysTime_getUsec(void);

Uint32 SysTime_getMsec(void);

Uint64 SysTime_getlongMsec(void);

Uint32 SysTime_getSec(void);

Uint32 SysTime_getMinute(void);

void SysTime_setTime(Uint64 time_in_seconds);

/******************************************************************************
*
******************************************************************************/
bool SysTime_usecIntervalElapsed(Uint32 startTime, Uint32 interval);

bool SysTime_msecIntervalElapsed(Uint32 startTime, Uint32 interval);

bool SysTime_secIntervalElapsed(Uint32 startTime, Uint32 interval);

bool SysTime_minuteIntervalElapsed(Uint32 startTime, Uint32 interval);

enum  status {FALSE = 0, TRUE};

#endif /* SYSTIME_H_ */
