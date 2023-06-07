#include "display.h"
#include "stdlib.h"
#include "joystick.h"

extern uint8_t getData[1];
extern uint8_t end_data_transmition;


float* calibration(TIM_HandleTypeDef* htim, ADC_HandleTypeDef* hadc_forServo, ADC_HandleTypeDef* hadc_forMotor); // do joysticks calibration

void sendValue(UART_HandleTypeDef *huart, float* coef, uint16_t servoValue, uint16_t stepValue, uint8_t buttonState); // send 6 bytes data package to machine

uint8_t crc8(uint8_t* buffer, uint8_t len); // create check sum by using crc8 method

void checkMachineStatus(UART_HandleTypeDef *huart); // send check data package to verify machine status
