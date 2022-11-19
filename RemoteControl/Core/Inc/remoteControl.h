#include "display.h"
#include "stdlib.h"
#include "joystick.h"

void sendValue(UART_HandleTypeDef *huart, float* coef, uint16_t servoValue, uint16_t stepValue, uint8_t buffer[1]); // send 6 byte data package

uint8_t crc8(uint8_t* buffer, uint8_t len); // create check sum

void checkMachineStatus(void);
