#include "stm32f4xx_hal.h" 
#include "step.h"

uint16_t aggregation(uint16_t x); // converte [0;4095] value to [1000;2000]

void servoSetPosition(TIM_HandleTypeDef *htim, uint8_t x);

void servoStop(TIM_HandleTypeDef *htim); // set servo in the middle position and stop motor
