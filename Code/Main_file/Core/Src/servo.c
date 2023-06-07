#include "servo.h"

uint16_t aggregation(uint16_t x)
{
    return (uint16_t)(-0.244*(float)x+2000.); 
}

void servoSetPosition(TIM_HandleTypeDef *htim, uint8_t x)
{
	uint16_t Servo = aggregation((uint16_t)((float)x*16.06)); // converte joystick value to [0;4095] and send to aggregation function 
  htim->Instance->CCR3 = Servo;
}

void servoStop(TIM_HandleTypeDef *htim)
{
    htim->Instance->CCR3 = 1500;
}
