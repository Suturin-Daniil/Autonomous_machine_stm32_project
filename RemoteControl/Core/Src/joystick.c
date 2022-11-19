#include "joystick.h"

float* calibration(TIM_HandleTypeDef* htim, ADC_HandleTypeDef* hadc_forServo, ADC_HandleTypeDef* hadc_forMotor) 
{
	float* coef = NULL; // array of coefficients
	coef = (float*)malloc(4);
	coef[0] = -0.062;
	coef[1] = 255.;    // default values of cofficients
	coef[2] = -0.062;
	coef[3] = 255.;
	
	uint16_t data[4]; // limit values of joysticks
	uint8_t t = 0;
	
	lcd_put_cur(0,5);
	lcd_send_string("Let's");
	lcd_put_cur(1,3);
	lcd_send_string("calibrate");
	HAL_Delay(2000);
	lcd_clear();
	lcd_put_cur(0,0);
	
	lcd_send_string("Set dflt set-gs?");
	lcd_put_cur(1,0);
	lcd_send_string("press user btn");
	HAL_TIM_Base_Start(htim);
	__HAL_TIM_SetCounter(htim, 0);
	
	while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) != GPIO_PIN_SET)
	{
		t = (TIM2->CNT)/1000;
		lcd_put_cur(1,15);
		lcd_send_data(54-t);
		if (t == 6)
		{			
			lcd_clear();
			lcd_put_cur(0,0);
			lcd_send_string("Default settings");
			lcd_put_cur(1,0);
			lcd_send_string("have been seted");
			HAL_Delay(2000);
			lcd_clear();
			lcd_put_cur(0,0);
			break;
		}
	}
	
	if (t==6) return coef;
	lcd_clear();
	lcd_put_cur(0, 7);
	lcd_send_string("OK");
	HAL_Delay(2000);
	lcd_clear();
	
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) 
	{
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
		{
		lcd_put_cur(0,1);
		lcd_send_string("Unpush button");
		}
		lcd_clear();
		lcd_put_cur(0,0);
	}
	HAL_Delay(80);
	lcd_put_cur(0,0);
	
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) != GPIO_PIN_SET)
	{
		lcd_send_string("Put right stick");
		lcd_put_cur(1, 5);
		lcd_send_string("right");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("Whn u'l be ready");
		lcd_put_cur(1,2);
		lcd_send_string("hold usr btn");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0,0);
	}
	
	data[0] = getServoValue(hadc_forServo);
	lcd_put_cur(0, 7);
	lcd_send_string("OK");
	HAL_Delay(2000);
	lcd_clear();
	
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) 
	{
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
		{
		lcd_put_cur(0,1);
		lcd_send_string("Unpush button");
		}
	}
	HAL_Delay(80);
	lcd_clear();
	
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) != GPIO_PIN_SET)
	{
		lcd_put_cur(0,0);
		lcd_send_string("Put right stick");
		lcd_put_cur(1, 6);
		lcd_send_string("left");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("Whn u'l be ready");
		lcd_put_cur(1,2);
		lcd_send_string("hold usr btn");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0,0);
	}
	data[1] = getServoValue(hadc_forServo);
	lcd_put_cur(0, 7);
	lcd_send_string("OK");
	HAL_Delay(2000);
	
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) 
	{
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
		{
		lcd_put_cur(0,1);
		lcd_send_string("Unpush button");
		}
	}
	HAL_Delay(80);
	lcd_clear();
	
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) != GPIO_PIN_SET)
	{
		lcd_put_cur(0,1);
		lcd_send_string("Put left stick");
		lcd_put_cur(1, 7);
		lcd_send_string("up");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("Whn u'l be ready");
		lcd_put_cur(1,2);
		lcd_send_string("hold usr btn");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0,0);
	}
	data[2] = getStepValue(hadc_forMotor);
	lcd_put_cur(0, 7);
	lcd_send_string("OK");
	HAL_Delay(2000);
	
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) 
	{
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
		{
		lcd_put_cur(0,1);
		lcd_send_string("Unpush button");
		}
	}
	HAL_Delay(80);
	lcd_clear();
	
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) != GPIO_PIN_SET)
	{
		lcd_put_cur(0,1);
		lcd_send_string("Put left stick");
		lcd_put_cur(1, 6);
		lcd_send_string("down");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0, 0);
		lcd_send_string("Whn u'l be ready");
		lcd_put_cur(1,2);
		lcd_send_string("hold usr btn");
		HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0,0);
	}
	data[3] = getStepValue(hadc_forMotor);
	lcd_put_cur(0, 7);
	lcd_send_string("OK");
	HAL_Delay(1000);
	lcd_clear();
	lcd_put_cur(0,1);
	
	coef[0] = 255./(data[0] - data[1]);
	coef[1] = -coef[0]*data[1];
	coef[2] = 255./(data[2]-data[3]);
	coef[3] = -coef[2]*data[3];
	
	if (coef[1] >= 255) 
		coef[1] = 255;
	if (coef[3] >= 255) 
		coef[3] = 255;
		
		lcd_send_string("Calibration has");
		lcd_put_cur(1,4);
		lcd_send_string("been done");
	  HAL_Delay(2000);
		lcd_clear();
		lcd_put_cur(0,0);
		
		return coef;
}

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

uint8_t* getStateButton(void)
{
	uint8_t* buttonState = NULL;
	buttonState = (uint8_t*)malloc(1);
	
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == GPIO_PIN_SET)
		buttonState[0] = 1;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) != GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) != GPIO_PIN_SET)
		buttonState[0] = 0;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) != GPIO_PIN_SET)
		buttonState[0] = 2;
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) != GPIO_PIN_SET && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == GPIO_PIN_SET)
		buttonState[0] = 3;
	
	return buttonState;
}
