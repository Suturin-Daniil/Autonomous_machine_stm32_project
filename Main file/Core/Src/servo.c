#include "servo.h"

uint16_t obrabotka(uint16_t x)
{
<<<<<<< HEAD
    return (uint16_t)(0.244*(float)x+1000.);
=======
    return ((1+ (x/4095.))*1000/3 + 1000); // Convert data from joystick to [1333:1666] value
>>>>>>> main
}

void servoSetPosition(TIM_HandleTypeDef *htim, uint16_t x)
{
<<<<<<< HEAD
	uint16_t Servo = (uint16_t)((float)x*16.06);
  htim->Instance->CCR3 = obrabotka(Servo);
=======
    htim->Instance->CCR3 = obrabotka(x); // I use CCR3, because of TIM3 PWM Channel is 3
>>>>>>> main
}

void servoStop(TIM_HandleTypeDef *htim)
{
    htim->Instance->CCR3 = 1500;
    stopMachine();
}
