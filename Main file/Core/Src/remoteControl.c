#include "remoteControl.h"

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

void sendValue(UART_HandleTypeDef *huart, float* coef, uint16_t servoValue, uint16_t stepValue)
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
	
	buffer[0] = 0;
	crc_buf[3] = buffer[0];
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = crc8(crc_buf, 4); // create check sum by using crc8 method
	HAL_UART_Transmit(huart, buffer, 1, 1);
	
	buffer[0] = 0x7E; // check byte
	HAL_UART_Transmit(huart, buffer, 1, 1);
		
	HAL_Delay(24);
}

void ProccesRevArr(TIM_HandleTypeDef* servo_tim, TIM_HandleTypeDef* step_tim, TIM_HandleTypeDef* main_tim, UART_HandleTypeDef *huart)
	{
		for(int i = 0; i < sizeofArr - 1; ++i)
		{
			__HAL_TIM_SetCounter(main_tim, 0);
			while(main_tim->Instance->CNT <= 40) // during 40 msec processing one of the servo and motor value, because of
				{																	 // in main.c part of code, which send servo and motor value takes 40 msec, so we don't use any time arrays
					servoSetPosition(servo_tim, Servo_reverse_array[i]);
					stepSetValue(step_tim, 3, Step_reverse_array[i]);
				}			
		}
	sizeofArr = 0;
	ButtonCnt = 0;
	float c[4] = {0,0,0,0};
	sendValue(huart, c, 0, 0); // send massage to remote control, that reverse mode has been done
}
