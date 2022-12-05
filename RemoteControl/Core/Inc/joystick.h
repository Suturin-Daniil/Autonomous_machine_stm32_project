#include "stm32f4xx_hal.h"
#include "display.h"
#include "stdlib.h"

float* calibration(TIM_HandleTypeDef* htim, ADC_HandleTypeDef* hadc_forServo, ADC_HandleTypeDef* hadc_forMotor); // do joysticks calibration

uint16_t getServoValue(ADC_HandleTypeDef* hadc_forServo); // return joystick value for servo

uint16_t getStepValue(ADC_HandleTypeDef* hadc_forMotor); // return joystick value for step motor

uint8_t getStateButton(void); // check states of buttons 
