/*
 * adc.c
 *
 *  Created on: 24-Oct-2018
 *      Author: Ram
 */
#include "adc.h"
#include "pll.h"
#include "inverter.h"


float normalisedResult = 0;
float DaqMeasItems_IA_LEFT_buf[64];
float DaqMeasItems_IB_LEFT_buf[64];
float DaqMeasItems_IC_LEFT_buf[64];
float DaqMeasItems_VAB_LEFT_buf[128];
float DaqMeasItems_VBC_LEFT_buf[16];
float DaqMeasItems_VCA_LEFT_buf[16];
float adc = 0;


typedef struct {
       float offset;
       float gain;
       float type;
       float offset_type;
} DaqMeasItem_t;
#define I_RES_VALUE     4
//DaqMeasItem_t DaqMeasItems[DAQ_N_MEAS_ITEMS];
DaqMeasItem_t DaqMeasItems[DAQ_N_MEAS_ITEMS] = {
    {0, (9.70588 * I_RES_VALUE), BIPOLAR, BIPOLAR_OFFSET},
    {0, (9.70588 * I_RES_VALUE), BIPOLAR, BIPOLAR_OFFSET},
    {0, (9.70588 * I_RES_VALUE), BIPOLAR, BIPOLAR_OFFSET},
    {0, 47.0, BIPOLAR, BIPOLAR_OFFSET},
    {0, 3.5, BIPOLAR, BIPOLAR_OFFSET},
    {0, 3.5, BIPOLAR, BIPOLAR_OFFSET}
};

#define publishSample(sample, channel, index)   \
    do{                         \
        float normalizedValue;  \
        float adcResultreg;  \
        adcResultreg = sample;\
        normalisedResult = ADC_TO_NORMAL(adcResultreg);\
        normalizedValue = ( normalisedResult * DaqMeasItems[channel].type ) + DaqMeasItems[channel].offset_type;\
        DaqMeasItems_##channel##_buf[index] = normalizedValue * DaqMeasItems[channel].gain;\
    }while(0);
void adc_mainFunction_foreground_1of2(){
    float normalizedValue = 0.0;
    float adcResultreg = 0.0;
    adcResultreg = (float) AdcaResultRegs.ADCRESULT0;
    normalizedValue = (float) ADC_TO_NORMAL(adcResultreg);
    Iin_ac_rn = ( normalizedValue * DaqMeasItems[0].type ) + DaqMeasItems[0].offset_type;
    Iin_ac_rn = Iin_ac_rn * DaqMeasItems[0].gain;
    adcResultreg = (float) AdcaResultRegs.ADCRESULT1;
    normalizedValue = (float) ADC_TO_NORMAL(adcResultreg);
    Iin_ac_yn = ( normalizedValue * DaqMeasItems[1].type ) + DaqMeasItems[1].offset_type;
    Iin_ac_yn = Iin_ac_yn * DaqMeasItems[1].gain;
    adcResultreg = (float) AdcaResultRegs.ADCRESULT2;
    normalizedValue = (float) ADC_TO_NORMAL(adcResultreg);
    Iin_ac_bn = ( normalizedValue * DaqMeasItems[2].type ) + DaqMeasItems[2].offset_type;
    Iin_ac_bn = Iin_ac_bn * DaqMeasItems[2].gain;
//    publishSample(ADC_IA_LEFT, IA_LEFT, Pll_result.index_64);
//    publishSample(ADC_IB_LEFT, IB_LEFT, Pll_result.index_64);
//    publishSample(ADC_IC_LEFT, IC_LEFT, Pll_result.index_64);
//    publishSample(ADC_VAB_LEFT, VAB_LEFT, Pll_result.index_128);
//    publishSample(ADC_VBC_LEFT, VBC_LEFT, Pll_result.index_16);
//    publishSample(ADC_VCA_LEFT, VCA_LEFT, Pll_result.index_16);
}


