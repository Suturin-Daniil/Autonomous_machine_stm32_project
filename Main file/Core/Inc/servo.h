#include "stm32f4xx_hal.h" 
#include "step.h"

uint16_t obrabotka(uint16_t x);

void servoSetPosition(TIM_HandleTypeDef *htim, uint16_t x);

void servoStop(TIM_HandleTypeDef *htim);
