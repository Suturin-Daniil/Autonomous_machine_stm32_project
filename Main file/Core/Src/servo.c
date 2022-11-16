#include "servo.h"

uint16_t obrabotka(uint16_t x)
{
    return ((1+ (x/4095.))*1000/3 + 1000); // Convert data from joystick to [1333:1666] value
}

void servoSetPosition(TIM_HandleTypeDef *htim, uint16_t x)
{
    htim->Instance->CCR3 = obrabotka(x); // I use CCR3, because of TIM3 PWM Channel is 3
}

void servoStop(TIM_HandleTypeDef *htim)
{
    htim->Instance->CCR3 = 1500;
    stopMachine();
}
