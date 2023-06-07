#include "stm32f4xx_hal.h"
#include "stdlib.h"

uint16_t getServoValue(ADC_HandleTypeDef* hadc_forServo); // return joystick value for servo

uint16_t getStepValue(ADC_HandleTypeDef* hadc_forMotor); // return joystick value for step motor

uint8_t getStateButton(void); // check states of buttons 
