#include "remoteControl.h"

void checkMachineStatus(void)
{
	
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

void sendValue(UART_HandleTypeDef *huart, float* coef, uint16_t servoValue, uint16_t stepValue, uint8_t buffer[6])
{
	buffer[0] = 0x7E; // check byte
	
	buffer[1] = (uint8_t)(coef[0]*(float)servoValue + coef[1]); // convert servoValue to uint8_t type
	
	buffer[2] = (uint8_t)(coef[2]*(float)stepValue + coef[3]); // convert stepValue to uint8_t type
	
	buffer[4] = crc8(buffer, 4);
	
	buffer[5] = 0x7E; // check byte
		
	if (HAL_UART_Transmit(huart, buffer, 6, 10) != HAL_BUSY)
		HAL_UART_Transmit(huart, buffer, 6, 10);
}
