#include "remoteControl.h"

void checkMachineStatus(UART_HandleTypeDef *huart)
{
	float c[4] = {0,0,0,0}; // fictitious coefficients array to check machine status 
	uint8_t buttonState = 0;
	
	while (buttonState != 1) // Before pressing usr btn, make sure that machine is online
	{                                                          	// else machine will not get data, because of the data is sent once
		lcd_put_cur(0,0);
		lcd_send_string("Hold usr btn to");
		lcd_put_cur(1,2);
		lcd_send_string("check conn-on");
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) buttonState = 1;
		HAL_Delay(1500);
		lcd_clear();
		lcd_put_cur(0,1);
		lcd_send_string("MAKE SURE THAT");
		lcd_put_cur(1,2);
		lcd_send_string("MACHINE IS ONLINE");
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) buttonState = 1;
		HAL_Delay(2000);
	}
	
	lcd_clear();
	lcd_put_cur(0,1);
	lcd_send_string("Try to connect");
	
	sendValue(huart, c, 0,0,0);
	while (end_data_transmition != 1)
	{
		HAL_UART_Receive_IT(huart, getData, 1);
	}
	end_data_transmition = 0;
	
	lcd_clear();
	lcd_put_cur(0,2);
	lcd_send_string("CONNECTION");
	lcd_put_cur(1,2);
	lcd_send_string("ESTABLISHED");
	HAL_Delay(2000);
	lcd_clear();
	lcd_put_cur(0,0);
}

uint8_t crc8(uint8_t* buffer, uint8_t len)
{
	/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 byte
*/
	uint8_t crc = 0xFF;
	uint8_t i;
	
	while(len--)
	{
		crc ^= *buffer++;
		
		for(i=0; i<8; i++)
		crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
	}
	
	return crc;
}

void sendValue(UART_HandleTypeDef *huart, float* coef, uint16_t servoValue, uint16_t stepValue, uint8_t buttonState)
{
	uint8_t crc_buf[4]; // buffer with data for check sum
	uint8_t buffer[1];
	
	buffer[0] = 0x7E; // check byte
	crc_buf[0] = buffer[0];
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = (uint8_t)(coef[0]*(float)servoValue + coef[1]); // convert servoValue to uint8_t type
	crc_buf[1] = buffer[0];
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = (uint8_t)(coef[2]*(float)stepValue + coef[3]); // convert stepValue to uint8_t type
	crc_buf[2] = buffer[0];
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = buttonState;
	crc_buf[3] = buffer[0];
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = crc8(crc_buf, 4); // create check sum by using crc8 method
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = 0x7E; // check byte
	HAL_UART_Transmit(huart, buffer, 1, 1);
		
	HAL_Delay(24); // it isn't random delay number, during 24 mlsec machine is working and cannot receive any massages
}

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
	
	lcd_send_string("PRESS USR BTN TO");
	lcd_put_cur(1,0);
	lcd_send_string("SET CUSTOM STGS");
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
