#include "servo.h"

uint16_t obrabotka(uint16_t x)
{
    return ((1+ (x/4095.))*1000/3 + 1000);
}

void servoSetPosition(TIM_HandleTypeDef *htim, uint16_t x)
{
    htim->Instance->CCR3 = obrabotka(x);
}

void servoStop(TIM_HandleTypeDef *htim)
{
    htim->Instance->CCR1 = 1500;
    stopMachine();
}
