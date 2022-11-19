#include "display.h"

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (uint8_t data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_clear (void)
{
	lcd_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}

void lcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void displayControl(TIM_HandleTypeDef *htim, uint8_t receiveData[5])
 {
	//STATE====================================================
	char stateGo[2] = "GO";
	char stateStop[4] = "STOP";
	char stateReverseMode[10] = "REV-E MODE";
	char stateLoseConnection[10] = "BAD CONN-N";
	 
	 lcd_put_cur(0,6);
	switch (receiveData[1])
	{
		case 0:
			lcd_send_string(stateStop);
			break;
		case 1:
			lcd_send_string(stateGo);
			break;
		case 2:
			lcd_send_string(stateReverseMode);
			break;
		default:
			lcd_send_string(stateLoseConnection);
	}
	
	//VELOCITY=================================================
	lcd_put_cur(1,6);
	if (receiveData[2]!=255) lcd_send_data(48+receiveData[2]);
	else lcd_send_string("NONE");
	
	//TIME===================================================
	uint16_t currentTime;
	lcd_put_cur(1,15);
	currentTime = (__HAL_TIM_GET_COUNTER(htim))/1000;
	if (currentTime <= 9) lcd_send_data(48+currentTime);
	else if (currentTime >=10 && currentTime <=59)
	{
		lcd_send_data(48+(currentTime-currentTime/10*10));
		lcd_put_cur(1,14);
		lcd_send_data(48+(currentTime/10));
	}
	else if (currentTime >=600)
	{
		lcd_put_cur(1,12);
		lcd_send_data(48+currentTime/60/10);
		lcd_send_data(48+(currentTime/60 - currentTime/60/10*10));
		lcd_send_string("m");
	}
	else
	{
		uint8_t minutes = currentTime/60;
		uint8_t dseconds = (currentTime - minutes*60)/10;
		uint8_t seconds = currentTime - minutes*60 - dseconds*10;
		lcd_put_cur(1,12);
		lcd_send_data(48+minutes);
		lcd_put_cur(1,14);
		lcd_send_data(48+dseconds);
		lcd_send_data(48+seconds);
	}
}
 
