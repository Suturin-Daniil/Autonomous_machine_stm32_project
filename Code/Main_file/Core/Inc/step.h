#include "stm32f4xx_hal.h"
#include "Reverse.h"

#define IN1_PIN GPIO_PIN_6
#define IN1_PORT GPIOA
#define IN2_PIN GPIO_PIN_5
#define IN2_PORT GPIOA
#define IN3_PIN GPIO_PIN_3
#define IN3_PORT GPIOA
#define IN4_PIN GPIO_PIN_2
#define IN4_PORT GPIOA

extern uint8_t Data[6];
extern uint8_t ButtonCnt;

void stopMachine(void); // stop motor
uint16_t setDelay(uint16_t y); // for each value from the joystick returns the delay for stepCCV and stepCV function
void microDelay (TIM_HandleTypeDef *htim, uint16_t delay); // makes delay by using timer
void stepSetValue(TIM_HandleTypeDef *htim, int steps, uint8_t y); // using all function to send value to motor
void stepCCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay); // CCV - Counter Clockwise;
void stepCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay); // CV - Clockwise
