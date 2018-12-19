/*
 * inverter.h
 *
 *  Created on: 26-Oct-2018
 *      Author: Ram
 */

#ifndef SOURCE_INVERTER_H_
#define SOURCE_INVERTER_H_
#include "F2837xD_device.h"
//#include "IQmathLib.h"
#include "math.h"


void invControl(void);
void speedLoop(void);
extern void init_invLoopParams(void);
void resetControlParams(void);

typedef struct {
    float   Kp;
    float   Ki;
    float   Integral;
    float   Ref;
    float   Error;
    float   Out;
    float   fb;
    float   fb_filt;
    float   SpeedInput;

} controlLoopParams;
extern controlLoopParams speed, Iq, Id;

typedef struct {
    int16   R;
    int16   Y;
    int16   B;
} finalDuty;

struct Angle {
                float R_theta;
                Uint16 R_freq;
                Uint16 R_PreviousTheta;
                Uint16 ZoneLast;
                Uint16 Ele_theta;
                Uint16 SampleCount;
                Uint16 n;
};

struct hall_data{
                Uint16 sr;
                Uint16 sy;
                Uint16 sz;
};


void pi_controller(float, controlLoopParams*, float, float, bool);
float expFilter(float, float, float);
extern float frequency_r;
extern float frequency_y;
extern float Iin_ac_rn;
extern float Iin_ac_yn;
extern float Iin_ac_bn;
extern Uint16 zcDetected;

#endif /* SOURCE_INVERTER_H_ */
