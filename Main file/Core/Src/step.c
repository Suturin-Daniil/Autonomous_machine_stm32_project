#include "step.h"

void stopMachine(void)
{
		HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET);   // IN4
}

uint16_t setDelay(uint16_t y)
{
	uint16_t delay;
	if ( (y > 2048 && y <= 2192) || (y > 1904 && y <= 2048) )
		delay = 0;
	
	else if (y > 2192 && y <= 2336)
		delay = 2848;
	else if (y > 2336 && y <= 2480)
		delay = 2694;
	else if (y > 2480 && y <= 2624)
		delay = 2540;
	else if (y > 2624 && y <= 2768)
		delay = 2386;
	else if (y > 2768 && y <= 2912)
		delay = 2232;
	else if (y > 2912 && y <= 3056)
		delay = 2078;
	else if (y > 3056 && y <= 3200)
		delay = 1924;
	else if (y > 3200 && y <= 3344)
		delay = 1770;
	else if (y > 3344 && y <= 3488)
		delay = 1616;
	else if (y > 3488 && y <= 3632)
		delay = 1462;
	else if (y > 3632 && y <= 3776)
		delay = 1308;
	else if (y > 3776 && y <= 3920)
		delay = 1154;
	else if (y > 3920 && y <= 4095)
		delay = 1000;
	
	else if (y > 1760 && y <= 1904)
		delay = 2848;
	else if (y > 1616 && y <= 1760)
		delay = 2694;
	else if (y > 1472 && y <= 1616)
		delay = 2540;
	else if (y > 1328 && y <= 1472)
		delay = 2386;
	else if (y > 1184 && y <= 1328)
		delay = 2232;
	else if (y > 1040 && y <= 1184)
		delay = 2078;
	else if (y > 896 && y <= 1040)
		delay = 1924;
	else if (y > 752 && y <= 896)
		delay = 1770;
	else if (y > 608 && y <= 752)
		delay = 1616;
	else if (y > 464 && y <= 608)
		delay = 1462;
	else if (y > 320 && y <= 464)
		delay = 1308;
	else if (y > 176 && y <= 320)
		delay = 1154;
	else if (y >= 0. && y <= 176)
		delay = 1000;
	
	return delay;
}

void microDelay (TIM_HandleTypeDef *htim, uint16_t delay)
{
	__HAL_TIM_SET_COUNTER(htim, 0);
  while (__HAL_TIM_GET_COUNTER(htim) < delay);
}

void stepSetValue(TIM_HandleTypeDef *htim, int steps, uint16_t y)
{
	uint16_t delay = setDelay(y);
	if (delay == 0)
		stopMachine();
	else if (y >= 2048)
		stepCCV(htim, steps, delay);
	else
		stepCV(htim, steps, delay);
}

void stepCCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay) // CCV - Counter Clockwise
{
  for(int x=0; x<steps; x=x+1)
  {
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim, delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim, delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    microDelay(htim,delay);
  }
}

void stepCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay) // CV - Clockwise
{
  for(int x=0; x<steps; x=x+1)
  {
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    microDelay(htim, delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_SET);   // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_SET);   // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_RESET); // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_SET);   // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
    HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, GPIO_PIN_SET);   // IN1
    HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, GPIO_PIN_RESET); // IN2
    HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, GPIO_PIN_RESET); // IN3
    HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, GPIO_PIN_RESET); // IN4
    microDelay(htim,delay);
  }
}
