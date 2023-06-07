#include "step.h"
uint8_t flag = 0; // is used for indicate servo and motor value saving by using WrittingArr function
									// if flag is 0 servo and motor values have not been placed in array 
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
	if ( (y > 2048 && y <= 2292) || (y > 1804 && y <= 2048) ) // if joystick is in the middle position => machine doesn't move
		delay = 0; // if delay is 0 => stopMachine()
	
	else if ( (y > 2292) || (y <= 1804) ) // We use only one motor rate, so if joystick isn't in the middle position => delay = 1000
		delay = 1000;
	/**else if (y > 2192 && y <= 2336)
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
	**/
	return delay;
}

void microDelay (TIM_HandleTypeDef *htim, uint16_t delay) // in StepCV and StepCCV functions we use microdelay which takes 1 msec
{																													// using this time we can put servo and motor values in array if reverse mod is enabled
	__HAL_TIM_SET_COUNTER(htim, 0);
  while (__HAL_TIM_GET_COUNTER(htim) < delay)
	{
		if (flag == 0)
		{
		if (ButtonCnt == 1)
		{
			WrittingArr(Data[1], Data[2]);
		}
		flag = 1; // flag is 1 => servo and motor value have been placed in array
	}
	}
}

void stepSetValue(TIM_HandleTypeDef *htim, int steps, uint8_t y)
{
	uint16_t Step = (uint16_t)((float)y*16.06); // converte joystick value to [0;4095]
	uint16_t delay = setDelay(Step);
	if (delay == 0)
		stopMachine();
	else if (Step > 2292)
		stepCCV(htim, steps, delay);
	else if (Step <= 1804)
		stepCV(htim, steps, delay);
}

void stepCCV (TIM_HandleTypeDef *htim, int steps, uint16_t delay) // CCV - Counter Clockwise
{
	flag = 0;
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
	flag = 0;
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
