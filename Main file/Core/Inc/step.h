#include "stm32f4xx_hal.h"

#define IN1_PIN GPIO_PIN_6
#define IN1_PORT GPIOA
#define IN2_PIN GPIO_PIN_5
#define IN2_PORT GPIOA
#define IN3_PIN GPIO_PIN_3
#define IN3_PORT GPIOA
#define IN4_PIN GPIO_PIN_2
#define IN4_PORT GPIOA

void stopMachine(void);
uint16_t setDelay(uint16_t y);
void microDelay (TIM_HandleTypeDef *htim, uint16_t delay);
void stepSetValue(TIM_HandleTypeDef *htim, int steps, uint8_t y);
void stepCCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay); // CCV - Counter Clockwise;
void stepCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay); // CV - Clockwise
