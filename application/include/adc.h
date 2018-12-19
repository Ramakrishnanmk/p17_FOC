/*
 * adc.h
 *
 *  Created on: 24-Oct-2018
 *      Author: Ram
 */

#ifndef SOURCE_ADC_H_
#define SOURCE_ADC_H_
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#define NOMINAL_FREQUENCY   50
#define PLL_INDEX_INC_RATE  10/NOMINAL_FREQUENCY
#define ADC_TO_NORMAL(A)   (A /(4095));
//#define SAT(x, Max, Min) ((x > Max) ? Max : ((x < Min) ? Min : x))
#define BIPOLAR     -2
#define BIPOLAR_OFFSET     1

typedef enum {
    IA_LEFT = 0,
    IB_LEFT,
    IC_LEFT,
    VAB_LEFT,
    VBC_LEFT,
    VCA_LEFT,
    DAQ_N_MEAS_ITEMS
} DaqMeasItemsId_t;


#define ADC_IA_LEFT    AdcaResultRegs.ADCRESULT0
#define ADC_IB_LEFT    AdcaResultRegs.ADCRESULT1
#define ADC_IC_LEFT    AdcaResultRegs.ADCRESULT2
#define ADC_VAB_LEFT    AdcaResultRegs.ADCRESULT3
#define ADC_VBC_LEFT    AdcaResultRegs.ADCRESULT4
#define ADC_VCA_LEFT    AdcaResultRegs.ADCRESULT5

extern void adc_mainFunction_foreground_1of2(void);

extern float DaqMeasItems_IA_LEFT_buf[64];
extern float DaqMeasItems_IB_LEFT_buf[64];
extern float DaqMeasItems_IC_LEFT_buf[64];
extern float DaqMeasItems_VAB_LEFT_buf[128];
extern float DaqMeasItems_VBC_LEFT_buf[16];
extern float DaqMeasItems_VCA_LEFT_buf[16];
#endif /* SOURCE_ADC_H_ */
