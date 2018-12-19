/*
 * inverter.c
 *
 *  Created on: 26-Oct-2018
 *      Author: Ram
 */

#include "inverter.h"
#include "adc.h"
#include "hw_abstraction.h"
#include "math.h"

#define ZONE1               1
#define ZONE2               2
#define ZONE3               3
#define ZONE4               4
#define ZONE5               5
#define ZONE6               6
#define KPHI                0.0128
#define SPEED_CONV_CONST    15              //120/8
#define RAD_CONV            0.0174533       //pi/180
#define SCALEFACTOR         84
#define EB_CONST            0.228           //Kphi*Peak*120/8
#define IQ_LOOP_SAT_POS     100.0
#define IQ_LOOP_SAT_NEG     -100.0
#define IQ_LOOP_SAT_ZERO     0.0
#define SPEED_LOOP_SAT_POS  50.0
#define SPEED_LOOP_SAT_NEG  -50.0
#define ID_LOOP_SAT_POS     5
#define ID_LOOP_SAT_NEG     -5
#define CARRIER_HEIGHT      6230
#define HALF_CARRIER_HEIGHT 3125
#define CARRIER_VALLEY      20
#define SAMPLING_TIME       0.000125
#define ONE_BY_THREE        0.3334
#define ONE_BY_ROOT_THREE   0.57735
#define PEAK_BACK_EMF       76.8
#define USE_FILTERED_FB    1
#define NO_FILTERED_FB     0
struct Angle my_angle={
                        0,
                        15,
                        0,
                        0,
                        0,
                        3,
                        0
};

struct hall_data signal={
                           0,
                           0,
                           0
};

controlLoopParams speed, Iq, Id;
controlLoopParams *signal_in;
finalDuty final;

float frequency_r, frequency_y;
Uint16 zcDetected = 0;

float Theta_Ref_Constant=0;
float Vout_ac_r,Iin_ac_rn,Iin_ac_r;
float Vout_ac_y,Iin_ac_yn,Iin_ac_y;
float Vout_ac_b,Iin_ac_bn,Iin_ac_b;

void init_invLoopParams(){
    Id.Kp = 2.1;
    Id.Ki = 0.05;
    Iq.Kp = 2.1;
    Iq.Ki = 0.05;
    speed.Kp = 0.2;
    speed.Ki = 0.6;
    speed.SpeedInput = 0.0;

    resetControlParams();
}
float Ialpha;
float Ibeta;
float ValphaOut;
float VbetaOut;
float vMax;
float vMin;
float Del_Theta = 0;
float BackEMF = 0;
float phaseAngle = 0;
Uint16 zone=0;
float ThetaDel = 0.07854, Theta = 0, SineRef = 0, CosRef = 0, Theta1 = 0, lineAngle = 0;
#pragma CODE_SECTION(invControl,".TI.ramfunc");
void invControl(){

    GPIO_WritePin(TEST_TOGGLE, 1);
    signal.sr = GPIO_ReadPin(HAL_A_INPUT);
    signal.sy = GPIO_ReadPin(HAL_B_INPUT);
    signal.sz = GPIO_ReadPin(HAL_C_INPUT);
    if (speed.SpeedInput != 0){
        Iin_ac_r = Iin_ac_rn;
        Iin_ac_y = Iin_ac_yn;
        Iin_ac_b = Iin_ac_bn;
        if((signal.sr == 1) && (signal.sy == 0) && (signal.sz == 1)){
            zone = ZONE1;
        }
        if((signal.sr == 1) && (signal.sy == 0) && (signal.sz == 0)){
            zone = ZONE2;
        }
        if ((signal.sr == 1) && (signal.sy == 1) && (signal.sz == 0)){
            zone = ZONE3;
        }
        if ((signal.sr == 0) && (signal.sy == 1) && (signal.sz == 0)){
            zone = ZONE4;
        }
        if ((signal.sr == 0) && (signal.sy == 1) && (signal.sz == 1)){
            zone = ZONE5;
        }
        if ((signal.sr == 0) && (signal.sy == 0) && (signal.sz == 1)){
            zone = ZONE6;
        }
        if(zone != my_angle.ZoneLast)
        {
            my_angle.SampleCount=my_angle.n;
            Del_Theta = (float) 60/my_angle.SampleCount;
            if(zone == ZONE1){
                Theta_Ref_Constant = 0;
            }
            else if(zone == ZONE4){
                Theta_Ref_Constant=180;
            }
            my_angle.n=0;
        }
        my_angle.n++;
        if(my_angle.SampleCount>=1000){
           my_angle.SampleCount=1000;
        }
        if (!zcDetected){
            if (Theta_Ref_Constant > 360.0){
                Theta_Ref_Constant = 0.0;
            }
            Del_Theta = 0.27;//Generate Initial anglular velocity @ 3Hz
        }
        Theta_Ref_Constant = (float)Theta_Ref_Constant + Del_Theta ;
        my_angle.ZoneLast = zone;
        lineAngle = Theta_Ref_Constant;
        if (lineAngle > 25.0){
            phaseAngle = lineAngle - 25;
        }
        else{
            phaseAngle = lineAngle + 335.0;
        }
        Theta = (float)(phaseAngle * RAD_CONV);
        if (Theta >= 6.283){
            Theta = 0;
        }
        SineRef = 1.0 * sin(Theta);
        if (Theta >= 4.712){
            Theta1 = Theta - 4.712;
        }
        else{
            Theta1 = Theta + 1.57;
        }
        if (Theta1 >= 6.283){
            Theta1 = 0;
        }
        else if (Theta1 < 0){
            Theta1 = 0;
        }
        CosRef = 1.0 * sin(Theta1);

        /// Speed loop controller starts here ///
        speed.Ref = fabs(speed.SpeedInput);
        speed.fb = (float)(SPEED_CONV_CONST * frequency_r);
        speed.fb_filt = expFilter(0.98, speed.fb_filt, speed.fb);
        pi_controller(SAMPLING_TIME, &speed, SPEED_LOOP_SAT_POS, SPEED_LOOP_SAT_NEG, USE_FILTERED_FB);
        Iq.Ref = speed.Out;

        /// 3-Phase to D-Q Current Transformations starts here ///
        Ialpha  = (float)(Iin_ac_r * 1.5);   // I_ALPHA = 1.5 x Iin_ac_r
        Ibeta   = (float)((Iin_ac_y - Iin_ac_b) * 0.866025);
        Id.fb    = (float)((Ialpha * CosRef) + (Ibeta * SineRef));
        Iq.fb    = (float)((Ibeta * CosRef)- (Ialpha * SineRef));

        /// D-Axis Current controller (for processing Q-Axis current IQ) starts here ///
        Id.Ref = 0.0;
        pi_controller(SAMPLING_TIME, &Id, ID_LOOP_SAT_POS, ID_LOOP_SAT_NEG, NO_FILTERED_FB);

        /// Q-Axis Current controller (for processing Q-Axis current IQ) starts here ///
        if (Iq.Ref > 0){
            pi_controller(SAMPLING_TIME, &Iq, IQ_LOOP_SAT_POS, IQ_LOOP_SAT_ZERO, NO_FILTERED_FB);
        }
        else{
            pi_controller(SAMPLING_TIME, &Iq, IQ_LOOP_SAT_ZERO, IQ_LOOP_SAT_NEG, NO_FILTERED_FB);
        }

        //BACK EMF COMPENSATION
        BackEMF = (float)(EB_CONST * frequency_r);
        if (BackEMF > PEAK_BACK_EMF){
            BackEMF = PEAK_BACK_EMF;
        }
        else if (BackEMF < 0.0){
            BackEMF = 0.0;
        }
        Iq.Out  = (float)(Iq.Out + BackEMF);

        /// Voltage DQ to three phase transformation ///
        ValphaOut = (float)((Id.Out * CosRef) - (Iq.Out * SineRef));
        VbetaOut  = (float)((Id.Out * SineRef) + (Iq.Out * CosRef));
        ValphaOut = (float)((ValphaOut * ONE_BY_THREE));

        Vout_ac_r   = (float)(ValphaOut * 2.0);
        if (speed.SpeedInput > 0){
            Vout_ac_y   = (float)((VbetaOut * ONE_BY_ROOT_THREE) - ValphaOut);
            Vout_ac_b   = (float)((-1.0 * ValphaOut) - (VbetaOut * ONE_BY_ROOT_THREE));
        }
        else{
            Vout_ac_b   = (float)((VbetaOut * ONE_BY_ROOT_THREE) - ValphaOut);
            Vout_ac_y   = (float)((-1.0 * ValphaOut) - (VbetaOut * ONE_BY_ROOT_THREE));
        }
        //////--------------------------------------------------------///////
        //Common mode signal derivation and addition for Conventional Space Vector PWM

        /********** Derivation of Maximum and Minimum of 3-phases Starts here *******************/
        vMax = fmaxf(Vout_ac_r, Vout_ac_y);
        vMax = fmaxf(vMax, Vout_ac_b);
        vMin = fminf(Vout_ac_r, Vout_ac_y);
        vMin = fminf(vMin, Vout_ac_b);
        vMax = (float)(vMax / 2.0);
        vMin = (float)(vMin / 2.0);

        Vout_ac_r = (float)((Vout_ac_r - vMax - vMin) * SCALEFACTOR);
        Vout_ac_y = (float)((Vout_ac_y - vMax - vMin) * SCALEFACTOR);
        Vout_ac_b = (float)((Vout_ac_b - vMax - vMin) * SCALEFACTOR);
        final.R = (Uint16)(Vout_ac_r + HALF_CARRIER_HEIGHT);
        final.Y = (Uint16)(Vout_ac_y + HALF_CARRIER_HEIGHT);
        final.B = (Uint16)(Vout_ac_b + HALF_CARRIER_HEIGHT);

        if (final.R > CARRIER_HEIGHT){
            final.R = CARRIER_HEIGHT;
        }
        else if (final.R < CARRIER_VALLEY){
            final.R = CARRIER_VALLEY;
        }
        if (final.Y > CARRIER_HEIGHT){
            final.Y = CARRIER_HEIGHT;
        }
        else if (final.Y < CARRIER_VALLEY){
            final.Y = CARRIER_VALLEY;
        }
        if (final.B > CARRIER_HEIGHT){
            final.B = CARRIER_HEIGHT;
        }
        else if (final.B < CARRIER_VALLEY){
            final.B = CARRIER_VALLEY;
        }
    }
    else{
        resetControlParams();
    }

    EPwm1Regs.CMPA.bit.CMPA = final.R;
    EPwm1Regs.CMPB.bit.CMPB = (CARRIER_HEIGHT - final.R);
    EPwm2Regs.CMPA.bit.CMPA = final.Y;
    EPwm2Regs.CMPB.bit.CMPB = (CARRIER_HEIGHT - final.Y);
    EPwm3Regs.CMPA.bit.CMPA = final.B;
    EPwm3Regs.CMPB.bit.CMPB = (CARRIER_HEIGHT - final.B);


    EPwm11Regs.CMPA.bit.CMPA = (Uint16)((SineRef + 1.0) * 230);
    EPwm11Regs.CMPB.bit.CMPB = (Uint16)(500 - (EPwm11Regs.CMPA.bit.CMPA));
    EPwm10Regs.CMPA.bit.CMPA = (Uint16)((0 + 1.0) * 230);
    EPwm10Regs.CMPB.bit.CMPB = (Uint16)(500 - (EPwm9Regs.CMPA.bit.CMPA));
    EPwm9Regs.CMPA.bit.CMPA = (Uint16)(((Iin_ac_r/10) + 1.0) * 230);
    EPwm9Regs.CMPB.bit.CMPB = (Uint16)(500 - (EPwm9Regs.CMPA.bit.CMPA));

    GPIO_WritePin(TEST_TOGGLE, 0);
}

void resetControlParams(){
    final.R = 0;
    final.Y = 0;
    final.B = 0;
    Id.Integral = 0.0;
    Id.Out = 0.0;
    Id.Error = 0.0;
    Iq.Integral = 0.0;
    Iq.Out = 0.0;
    Iq.Ref = 0.0;
    Iq.Error = 0.0;
    speed.Out = 0.0;
    speed.Integral = 0.0;
    speed.fb = 0.0;
    speed.Ref = 0.0;
    speed.Error = 0.0;
    speed.SpeedInput = 0.0;
    speed.fb_filt = 0;
    zcDetected = 0;
    Theta_Ref_Constant = 0;
}

void pi_controller(float delTime, controlLoopParams* signal_in, float posSat, float negSat, bool useFilter){
    if (useFilter){
        signal_in->Error = (float)(signal_in->Ref - signal_in->fb_filt);
    }
    else{
        signal_in->Error = (float)(signal_in->Ref - signal_in->fb);
    }
    signal_in->Integral = (float)((signal_in->Error * delTime) + signal_in->Integral);
    if (signal_in->Integral >= posSat){
        signal_in->Integral = posSat;
    }
    else if (signal_in->Integral < negSat){
        signal_in->Integral = negSat;
    }
    signal_in->Out = (float)((signal_in->Error * signal_in->Kp) + (signal_in->Integral * signal_in->Ki));
    if (signal_in->Out > posSat){
        signal_in->Out = posSat;
    }
    else if (signal_in->Out < negSat){
        signal_in->Out = negSat;
    }
}

float expFilter(float alpha, float previous_out, float sample){
    return ((alpha * previous_out) + ((1.0 - alpha) * sample));
}
