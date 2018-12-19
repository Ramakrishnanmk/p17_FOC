/*
 * daq_meas_channels.h
 *
 *  Created on: 16-Aug-2018
 *      Author: Ram
 */

#ifndef DAQ_MEAS_CHANNELS_H_
#define DAQ_MEAS_CHANNELS_H_

#include "pll.h"
/******************************************************************************
* Enum: DaqMeasChannelsId_t
*
* Enumerated values for all the different signals we deal with. There are
* two different kinds of signals: Primary and Secondary. Primary signals
* come straight from the ADC. Secondary signals are derived from other
* signals (e.g., power is derived from current and votlage).
*****************************************************************************/
typedef enum {

    VINV_BC_LEFT,                      //
    IDC_LEFT,                          //
    IAC_SNS_PH_A_LEFT,                 //
    IAC_SNS_PH_B_LEFT,                 //
    IAC_SNS_PH_C_LEFT,                 //
    VINV_VAB_LEFT,                     //
    VINV_VAB_RIGHT,                    //
    IAC_SNS_PH_C_RIGHT,                //
    IAC_SNS_PH_B_RIGHT,                //
    IAC_SNS_PH_A_RIGHT,                //
    VDC_SNS_LEFT,                      //
    MUX_2_IN,                          //
    MUX_1_IN,                          //
    IDC_RIGHT,                         //
    VINV_VBC_RIGHT,                    //
    VINV_VCA_RIGHT,                    //
    V_BREAK_POS_SNS_RIGHT,             //
    V_BREAK_POS_SNS_LEFT,              //
    VINV_VCA_LEFT,                     //
    VDC_SNS_RIGHT,                     //
    DAQ_N_MEAS_CHANNELS                // Keep this at the end of the enum

} DaqMeasChannelId_t;

typedef enum {
    DAQ_MEAS_METHOD_NONE,
    DAQ_MEAS_METHOD_RMS,
    DAQ_MEAS_METHOD_AVG
} DAQCalMeasMethod_t;


typedef struct {
    float m;
    float b;
}AdcCalFactor_t;


//These initial values can be updated from eeprom during initialization.
AdcCalFactor_t DaqMeasChannels_initFactor[DAQ_N_MEAS_CHANNELS-2] = {
{    2.0,     -1.0,   },                //VBC_LEFT
{    1.0,     0.0,    },                //IDC_LEFT
{    2.0,     -1.0,   },                //IA_LEFT
{    2.0,     -1.0,   },                //IB_LEFT
{    2.0,     -1.0,   },                //IC_LEFT
{    2.0,     -1.0,   },                //VAB_LEFT
{    2.0,     -1.0,   },                //VAB_RIGHT
{    2.0,     -1.0,   },                //IC_RIGHT
{    2.0,     -1.0,   },                //IB_RIGHT
{    2.0,     -1.0,   },                //IA_RIGHT
{    1.0,     0.0,    },                //VDC_LEFT
//{    (2),     (-1.0),    },             //MUX_2_IN
//{    (2),     (-1.0),    },             //MUX_1_IN
{    1.0,     0.0,    },                //IDC_RIGHT
{    2.0,     -1.0,   },                //VBC_RIGHT
{    2.0,     -1.0,   },                //VCA_RIGHT
{    1.0,     0.0,    },                //BREAK_RIGHT
{    1.0,     0.0,    },                //BREAK_LEFT
{    1.0,     0.0,    },                //VCA_LEFT
{    1.0,     0.0,    },                //VDC_RIGHT

};

/******************************************************************************
* Typedef: DaqMeasChannel_t
* Encapsulates the measured channel description.
*****************************************************************************/
typedef struct {
    float offset;
    float gain;
    float normalizedValue;
    float scaledValue;
    float scaleFactor;
    float *pSampleBuf;
    Uint16 bufSize;
    Uint16 *pbufIndex;
} DaqMeasChannel_t;


extern DaqMeasChannel_t DaqMeasChannels[DAQ_N_MEAS_CHANNELS-2];


/*****************************************************************************/
//#ifdef DAQ_ADC_C


/******************************************************************************
 * Variable: DaqMeasChannels_index16
 *
 * An index which is incremented once in a line cycle (0-15) for buffering. It
 * is used to calculate 16 point moving average of any parameter such as Vload_rms.
******************************************************************************/

/******************************************************************************
* Buffers for channel samples.
*****************************************************************************/

float DaqMeasChannels_VINV_VBC_LEFT_buf[16];
float DaqMeasChannels_IDC_LEFT_buf[8];
float DaqMeasChannels_IAC_SNS_PH_A_LEFT_buf[64];
float DaqMeasChannels_IAC_SNS_PH_B_LEFT_buf[64];
float DaqMeasChannels_IAC_SNS_PH_C_LEFT_buf[64];
float DaqMeasChannels_VINV_VAB_LEFT_buf[16];
float DaqMeasChannels_VINV_VAB_RIGHT_buf[16];
float DaqMeasChannels_IAC_SNS_PH_C_RIGHT_buf[64];
float DaqMeasChannels_IAC_SNS_PH_B_RIGHT_buf[64];
float DaqMeasChannels_IAC_SNS_PH_A_RIGHT_buf[64];
float DaqMeasChannels_VDC_SNS_LEFT_buf[8];
float DaqMeasChannels_IDC_RIGHT_buf[8];
float DaqMeasChannels_VINV_VBC_RIGHT_buf[16];
float DaqMeasChannels_VINV_VCA_RIGHT_buf[16];
float DaqMeasChannels_V_BREAK_POS_SNS_RIGHT_buf[8];
float DaqMeasChannels_V_BREAK_POS_SNS_LEFT_buf[8];
float DaqMeasChannels_VINV_VCA_LEFT_buf[16];
float DaqMeasChannels_VDC_SNS_RIGHT_buf[8];


// The ADC_RESULT is left justified 12bit value stored in 16bits (FFF0).
// If you convert this result to normalized ADC_RESULT then
// 0000=0.0, 0x8000=0.5, 0xFFF0=0.97
// The following factors represent the constants in y=Mx + B that convert
// (0.0, 0.5, 0.97) to
// BIPOLAR             UNIPOLAR            UNIPOLAR_INVERTED  BIPOLAR_INVERTED
// (-1.0, 0.0, 1.0) or (0.0, 0.5, 0.97) or (1.0, 0.5, 0.0) or (1.0, 0.0, -0.97)
#define DAQMEASCHANNEL_BIPOLAR_MFACTOR            (2.0)
#define DAQMEASCHANNEL_BIPOLAR_BFACTOR            (-1.0)
#define DAQMEASCHANNEL_UNIPOLAR_MFACTOR           (1.0)
#define DAQMEASCHANNEL_UNIPOLAR_BFACTOR           (0.0)
#define DAQMEASCHANNEL_UNIPOLAR_INVERTED_MFACTOR  (-1.0)
#define DAQMEASCHANNEL_UNIPOLAR_INVERTED_BFACTOR  (1.0)
#define DAQMEASCHANNEL_BIPOLAR_INVERTED_MFACTOR   (-2.0)
#define DAQMEASCHANNEL_BIPOLAR_INVERTED_BFACTOR   (1.0)

#define DAQMEASCHANNEL_INIT_CHANNEL(name, type, scaleFactor, pBuf, bufSize, bufIndex)     \
    { DAQMEASCHANNEL_##type##_BFACTOR,                                  \
      DAQMEASCHANNEL_##type##_MFACTOR,                                  \
      0.0,                                                               \
      0.0,                                                               \
      scaleFactor,                                              \
      pBuf,                                                                   \
      bufSize,                                                                \
      bufIndex }





//////
#define     DaqMeasChannels_VINV_BC_LEFT_scaleFactor                1.0
#define     DaqMeasChannels_IDC_LEFT_scaleFactor                    1.0
#define     DaqMeasChannels_IAC_SNS_PH_A_LEFT_scaleFactor           1.0
#define     DaqMeasChannels_IAC_SNS_PH_B_LEFT_scaleFactor           1.0
#define     DaqMeasChannels_IAC_SNS_PH_C_LEFT_scaleFactor           1.0
#define     DaqMeasChannels_VINV_VAB_LEFT_scaleFactor               1.0
#define     DaqMeasChannels_VINV_VAB_RIGHT_scaleFactor              1.0
#define     DaqMeasChannels_IAC_SNS_PH_C_RIGHT_scaleFactor          1.0
#define     DaqMeasChannels_IAC_SNS_PH_B_RIGHT_scaleFactor          1.0
#define     DaqMeasChannels_IAC_SNS_PH_A_RIGHT_scaleFactor          1.0
#define     DaqMeasChannels_VDC_SNS_LEFT_scaleFactor                1.0
//#define     DaqMeasChannels_MUX_2_IN,                          //
//#define     DaqMeasChannels_MUX_1_IN,                          //
#define     DaqMeasChannels_IDC_RIGHT_scaleFactor                   1.0
#define     DaqMeasChannels_VINV_VBC_RIGHT_scaleFactor              1.0
#define     DaqMeasChannels_VINV_VCA_RIGHT_scaleFactor              1.0
#define     DaqMeasChannels_V_BREAK_POS_SNS_RIGHT_scaleFactor       1.0
#define     DaqMeasChannels_V_BREAK_POS_SNS_LEFT_scaleFactor        1.0
#define     DaqMeasChannels_VINV_VCA_LEFT_scaleFactor               1.0
#define     DaqMeasChannels_VDC_SNS_RIGHT_scaleFactor               1.0

/******************************************************************************
* Descriptor for each measured item.
*****************************************************************************/
DaqMeasChannel_t DaqMeasChannels[DAQ_N_MEAS_CHANNELS-2] = {
    DAQMEASCHANNEL_INIT_CHANNEL(VINV_BC_LEFT ,       BIPOLAR,      40.0,    DaqMeasChannels_VINV_VBC_LEFT_buf,           16, &(Pll_result.index_16) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IDC_LEFT,            UNIPOLAR,     1.0,    DaqMeasChannels_IDC_LEFT_buf,              8,   &(Pll_result.index_8) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IAC_SNS_PH_A_LEFT,   BIPOLAR,      3.5,    DaqMeasChannels_IAC_SNS_PH_A_LEFT_buf,    64,   &(Pll_result.index_64) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IAC_SNS_PH_B_LEFT,   BIPOLAR,      3.5,    DaqMeasChannels_IAC_SNS_PH_B_LEFT_buf,    64,   &(Pll_result.index_64) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IAC_SNS_PH_C_LEFT,   BIPOLAR,      3.5,    DaqMeasChannels_IAC_SNS_PH_C_LEFT_buf,    64,   &(Pll_result.index_64) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VINV_VAB_LEFT,       BIPOLAR,      40.0,    DaqMeasChannels_VINV_VAB_LEFT_buf,         16, &(Pll_result.index_16) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VINV_VAB_RIGHT,      BIPOLAR,      1.0,    DaqMeasChannels_VINV_VAB_RIGHT_buf,        16, &(Pll_result.index_16) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IAC_SNS_PH_C_RIGHT,  BIPOLAR,      1.0,    DaqMeasChannels_IAC_SNS_PH_C_RIGHT_buf,   64,   &(Pll_result.index_64) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IAC_SNS_PH_B_RIGHT,  BIPOLAR,      1.0,    DaqMeasChannels_IAC_SNS_PH_B_RIGHT_buf,   64,   &(Pll_result.index_64) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IAC_SNS_PH_A_RIGHT,  BIPOLAR,      1.0,    DaqMeasChannels_IAC_SNS_PH_A_RIGHT_buf,   64,   &(Pll_result.index_64) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VDC_SNS_LEFT,        UNIPOLAR,     1.0,    DaqMeasChannels_VDC_SNS_LEFT_buf,          8,   &(Pll_result.index_8) ),
    DAQMEASCHANNEL_INIT_CHANNEL(IDC_RIGHT,           UNIPOLAR,     1.0,    DaqMeasChannels_IDC_RIGHT_buf,             8,   &(Pll_result.index_8) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VINV_VBC_RIGHT,      BIPOLAR,      1.0,    DaqMeasChannels_VINV_VBC_RIGHT_buf,         16, &(Pll_result.index_16) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VINV_VCA_RIGHT,      BIPOLAR,      1.0,    DaqMeasChannels_VINV_VCA_RIGHT_buf,         16, &(Pll_result.index_16) ),
    DAQMEASCHANNEL_INIT_CHANNEL(V_BREAK_POS_SNS_RIGHT,UNIPOLAR,   1.0,    DaqMeasChannels_V_BREAK_POS_SNS_RIGHT_buf,  8,   &(Pll_result.index_8) ),
    DAQMEASCHANNEL_INIT_CHANNEL(V_BREAK_POS_SNS_LEFT,UNIPOLAR,   1.0,    DaqMeasChannels_V_BREAK_POS_SNS_LEFT_buf,  8,   &(Pll_result.index_8) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VINV_VCA_LEFT,       BIPOLAR,      1.0,    DaqMeasChannels_VINV_VCA_LEFT_buf,          16, &(Pll_result.index_16) ),
    DAQMEASCHANNEL_INIT_CHANNEL(VDC_SNS_RIGHT,       UNIPOLAR,     1.0,    DaqMeasChannels_VDC_SNS_RIGHT_buf,          8,   &(Pll_result.index_8) ),
};

#endif /* DAQ_MEAS_CHANNELS_H_ */
