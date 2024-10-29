/*
 * input_reading.h
 *
 *  Created on: Oct 27, 2024
 *      Author: Admin
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "global.h"
#include "main.h"
#include <stdio.h>
#include <stm32f1xx_hal_gpio.h>

#define NORMAL_STATE		 	RESET
#define PRESSED_STATE 			SET


typedef struct {
	GPIO_TypeDef *button_port;
	int button_pin;
	int time_out;
	uint8_t button_flag;
	uint8_t button_status;
	int key_reg[4];
}button_t;


int isButtonPressed(int index);

void button_init(void);
void set_button(int index, GPIO_TypeDef *button_port, int button_pin);

void getKeyInput();

#endif /* INC_INPUT_READING_H_ */
