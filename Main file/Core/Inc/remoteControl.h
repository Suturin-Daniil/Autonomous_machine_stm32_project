#include "stdlib.h"
#include "stm32f4xx_hal.h"
#include "step.h"
#include "servo.h"

extern uint8_t ButtonCnt;
extern uint8_t connection;
extern uint8_t response[6];
extern uint8_t getData[1];
extern uint8_t end_data_transmition;
extern uint16_t sizeofArr;

extern uint8_t Servo_array[5000];
extern uint8_t Servo_reverse_array[5000] ;

extern uint8_t Step_array[5000];
extern uint8_t Step_reverse_array[5000];

// extern uint32_t Time_array[5000];
// extern uint32_t Time_reverse_array[5000];

void sendValue(UART_HandleTypeDef *huart, float* coef, uint16_t servoValue, uint16_t stepValue); // send 6 byte data package

uint8_t crc8(uint8_t* buffer, uint8_t len); // create check sum

void ProccesRevArr(TIM_HandleTypeDef* servo_tim, TIM_HandleTypeDef* step_tim, TIM_HandleTypeDef* main_tim, UART_HandleTypeDef *huart); // reverse mode processing
