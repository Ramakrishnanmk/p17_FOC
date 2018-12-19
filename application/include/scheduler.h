/*
 * scheduler.h
 *
 *  Created on: 07-Dec-2017
 *      Author: Ram
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "cu_state.h"

void scheduler(void);
//#define WAITTIME4NEWCMD 500
void inttostring(int32 num);
void Ack_to_x86(void);
void Clr_regs(void);
#endif /* SCHEDULER_H_ */
