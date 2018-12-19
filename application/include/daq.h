/*
 * daq.h
 *
 *  Created on: 21-Aug-2018
 *      Author: Ram
 */

#ifndef DAQ_H_
#define DAQ_H_
//#include "daq_meas_channels.h"


typedef enum
{
    DAQ_CALIB_RESET_IDLE = 0,
    DAQ_CALIB_RESET_REQUESTED,
    DAQ_CALIB_RESET_CONFIRMED


}DAQ_CALIBRESET_States_t;

/******************************************************************************
*
******************************************************************************/
//void daq_init(void);
//void DaqAdc_setFactor(DaqMeasChannelId_t channelId, float m, float b);
//void DaqAdc_setFactorM(DaqMeasChannelId_t channelId, float m);
//void DaqAdc_setFactorB(DaqMeasChannelId_t channelId, float b);
//void daq_initFactor(DaqMeasChannelId_t channelId);
//void inline DaqAdc_healthCheck(void);
//void DaqADC_resetCalib(UINT16 cmd);

/******************************************************************************
*
******************************************************************************/
extern void Daq_mainFunction_foreground_1of2(void);
extern void Daq_mainFunction_foreground_2of2(void);
//extern void DaqAdc_mainFunction_foreground_default(void);

/******************************************************************************
 * Function: DaqAdc_getSampledValue
 * Functional macro to encapsulate getting the calibrated AND SCALED sample
 * value for the specified signal.
******************************************************************************/
#define DaqAdc_getSampledValue(MEASITEM)   (DaqMeasChannels[MEASITEM].scaledValue)


/******************************************************************************
 * Function: DaqAdc_getNormalizedValue
 * Functional macro to encapsulate getting the calibrated AND UN-SCALED sample
 * value for the specified signal.
******************************************************************************/
#define DaqAdc_getNormalizedValue(MEASITEM)   (DaqMeasChannels[MEASITEM].normalizedValue)


/******************************************************************************
 * Function: DaqAdc_addSample
 *
 * Add a sample to a sample buffer for the given signal, indexed by the
 * variable given in the descriptor. As such, this treats the buffer as a
 * circular buffer which resets when index resets.
 *
 *
 * Arguments:
 *  measItem - <DaqMeasItemId_t> : specifies which signal the sample belongs
 *  to.
 *
 *  sample   - <_iq> : The sample value,  but normalized (unscaled) and in
 *  the appropriate Q-format, for instance, by <DaqAdc_getSampledValue>.
 *
******************************************************************************/
//#define DaqAdc_addSample(MEASITEM, SAMPLE)    \
//    DaqMeasItems_##MEASITEM##_buf[*(DaqMeasItems[(MEASITEM)].pbufIndex)] = (SAMPLE)
//
//extern const UINT16 daqCalib_Ch_ulinkQFormat[];
//extern const UINT32 daqCalib_Ch_Select_ulinkTarget_BF[];
//extern const DAQCalMeasMethod_t daqCal_Meas_Method[];




#endif /* DAQ_H_ */
