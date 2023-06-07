#include "joystick.h"

uint16_t getServoValue(ADC_HandleTypeDef* hadc_forServo)
{
		HAL_ADC_Start(hadc_forServo);
		HAL_ADC_PollForConversion(hadc_forServo, 10);
		uint16_t readValueX = HAL_ADC_GetValue(hadc_forServo);
		HAL_ADC_Stop(hadc_forServo);
		return readValueX;
}

uint16_t getStepValue(ADC_HandleTypeDef* hadc_forMotor)
{
		HAL_ADC_Start(hadc_forMotor);
		HAL_ADC_PollForConversion(hadc_forMotor, 10);
		uint16_t readValueY = HAL_ADC_GetValue(hadc_forMotor);
		HAL_ADC_Stop(hadc_forMotor);
		return readValueY;
}

uint8_t getStateButton(void)
{
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) != GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) != GPIO_PIN_RESET)
		return 0;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) != GPIO_PIN_RESET)
		return 1;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) != GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == GPIO_PIN_RESET)
		return 2;
	return 0;
}
