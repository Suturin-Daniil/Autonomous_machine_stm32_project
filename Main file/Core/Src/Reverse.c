#include "Reverse.h"

void WrittingArr(uint8_t Servo, uint8_t Step, uint32_t Time)
{
		Servo_array[sizeofArr] = Servo;  // Servo
		Step_array[sizeofArr] = Step;   // Motor
		Time_array[sizeofArr] = Time;  // Time
		sizeofArr += 1;
}

void CreateReverseArr(void)
{
	for(int i = 0; i < sizeofArr; i++)
	{
		Servo_reverse_array[i] = (uint8_t)(Servo_array[sizeofArr - 1 - i]);
		Step_reverse_array[i] = (uint8_t)(255 - Step_array[sizeofArr - 1 - i]);
		Time_reverse_array[i] = (uint32_t)(Time_array[sizeofArr - 1] - Time_array[sizeofArr - 1 - i]);
	} 
}
