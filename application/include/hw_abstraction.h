/*
 * hw_abstraction.h
 *
 *  Created on: 18-Sep-2018
 *      Author: Ram
 */

#ifndef SOURCE_INCLUDES_HW_ABSTRACTION_H_
#define SOURCE_INCLUDES_HW_ABSTRACTION_H_
//#include
//#define DEVBOARD
//#define DEVBOARD_SIM
#ifdef DEVBOARD_SIM
#define HAL_A_INPUT                 61//0
#define HAL_B_INPUT                 123//1
#define HAL_C_INPUT                 122//2
#else
#ifndef DEVBOARD
#define HAL_A_INPUT                 81
#define HAL_B_INPUT                 82
#define HAL_C_INPUT                 83
#else
#define HAL_A_INPUT                 81//0
#define HAL_B_INPUT                 82//1
#define HAL_C_INPUT                 83//2

#endif
#endif
#define TEST_TOGGLE                 71
#define DECODER_IN                  85
#define LATCH_DISABLE               88


#define STATUS_LED_GPIO0            0
#define LED_1_GPIO22                22
#define LED_2_GPIO21                21
#define LED_3_GPIO20                20
#define MOT1_DIR_GPIO               79
#define MOT2_DIR_GPIO               78
#define UART_RX_JETSON_GPIO         87
#define UART_TX_JETSON_GPIO         86
#define I2C_SDA_GPIO                32
#define I2C_SCL_GPIO                33
#define ELOCK1_GPIO                 83
#define ELOCK2_GPIO                 82

#define REAR_PWM_GPIO               28
#define REAR_DIR_GPIO               29
#define REAR_DIS_GPIO               30


//#define REAR_DIR                    7
#define REAR_DIS                    17

//#define BUZZER_GPIO                 15                      //LA1_DIR configured for buzzer






#endif /* SOURCE_INCLUDES_HW_ABSTRACTION_H_ */
