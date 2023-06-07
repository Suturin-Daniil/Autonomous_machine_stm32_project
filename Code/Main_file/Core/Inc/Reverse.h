#include "stm32f4xx_hal.h"

extern uint8_t Servo_array[5000];
extern uint8_t Servo_reverse_array[5000] ;

extern uint8_t Step_array[5000];
extern uint8_t Step_reverse_array[5000];

//extern uint32_t Time_array[3000];
//extern uint32_t Time_reverse_array[3000];

extern uint16_t sizeofArr;

void WrittingArr(uint8_t Servo, uint8_t Step); // place servo and motor values in array

void CreateReverseArr(void); // create array with reverse servo and motor value
