#include "remoteControl.h"

void checkMachineStatus(UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim)
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
