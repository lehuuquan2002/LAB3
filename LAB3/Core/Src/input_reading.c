/*
 * input_reading.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Admin
 */


#include <input_reading.h>
#include "main.h"

button_t button[10];

void button_init(void)
{
	for (uint8_t i = 0; i < 10; i++)
	{
		button[i].button_status = DISABLE;
		button[i].button_flag = 0;
		button[i].key_reg[3] = NORMAL_STATE;
		button[i].key_reg[2] = NORMAL_STATE;
		button[i].key_reg[1] = NORMAL_STATE;
		button[i].key_reg[0] = NORMAL_STATE;
	}
}

int isButtonPressed(int index)
{
	if (index >= 10)
		return 0;
	if (button[index].button_flag == 1)
	{
		button[index].button_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index)
{
	button[index].button_flag = 1;
}

void set_button(int index, GPIO_TypeDef *button_port, int button_pin)
{
	if (index >= 10)
		return;
	button[index].button_port = button_port;
	button[index].button_pin = button_pin;
	button[index].button_status = ENABLE;
}

void getKeyInput(){
	for (uint8_t i = 0; i < 10; i++)
	{
		if (button[i].button_status == DISABLE)
			continue;
		button[i].key_reg[2] = button[i].key_reg[1];
		button[i].key_reg[1] = button[i].key_reg[0];
		button[i].key_reg[0] = !HAL_GPIO_ReadPin(button[i].button_port, button[i].button_pin);

		if (!(button[i].key_reg[0]|button[i].key_reg[1]|button[i].key_reg[2]))
		{
			button[i].key_reg[3] = button[i].key_reg[2];
			continue;
		}

		if (button[i].key_reg[3] == 0)
		{
			button[i].key_reg[3] = 1;
			button[i].time_out = 100;
			subKeyProcess(i);
		}else {
			button[i].time_out--;
			if (button[i].time_out == 0)
			{
				button[i].time_out = 100;
			}
		}
	}
}
