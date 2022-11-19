#include "servo.h"

uint16_t obrabotka(uint16_t x)
{
    return (uint16_t)(0.244*(float)x+1000.);
}

void servoSetPosition(TIM_HandleTypeDef *htim, uint16_t x)
{
	uint16_t Servo = (uint16_t)((float)x*16.06);
  htim->Instance->CCR3 = obrabotka(Servo);
}

void servoStop(TIM_HandleTypeDef *htim)
{
    htim->Instance->CCR3 = 1500;
    stopMachine();
}
