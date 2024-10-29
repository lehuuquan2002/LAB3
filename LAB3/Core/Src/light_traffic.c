/*
 * light_traffic.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Admin
 */


#include "global.h"
#include "display7SEG.h"
#include "light_traffic.h"

void led_red_and_green(void)
{
	HAL_GPIO_WritePin(RED13_GPIO_Port, RED13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GREEN24_GPIO_Port, GREEN24_Pin, GPIO_PIN_SET);
}

void led_red_and_yellow(void)
{
	HAL_GPIO_WritePin(RED13_GPIO_Port, RED13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AMBER24_GPIO_Port, AMBER24_Pin, GPIO_PIN_SET);
}

void led_yellow_and_red(void)
{
	HAL_GPIO_WritePin(AMBER13_GPIO_Port, AMBER13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED24_GPIO_Port, RED24_Pin, GPIO_PIN_SET);
}

void led_green_and_red(void)
{
	HAL_GPIO_WritePin(GREEN13_GPIO_Port, GREEN13_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RED24_GPIO_Port, RED24_Pin, GPIO_PIN_SET);
}


void updateTrafficLight(void)
{
	clear_led_red_amber_green();
	switch (current_state) {
		case INIT:
			updateLED7SEGBuffer(0, 0);
			//HAL_GPIO_WritePin(GPIOA, RED13_Pin | RED24_Pin | AMBER13_Pin | AMBER24_Pin  | GREEN13_Pin | GREEN24_Pin  , SET);
			counter_red = time_red;
			counter_amber = time_amber;
			counter_green = time_green;
			break;
		case RED13_AMBER24:
			updateLED7SEGBuffer(counter_red, counter_amber);
			counter_amber--;
			counter_red--;
			if (counter_amber == 0)
			{
				counter_red = time_red;
				counter_amber = time_amber;
				counter_green = time_green;
				state = GREEN13_RED24;
			}
			led_red_and_yellow();
			break;
		case RED13_GREEN24:
			updateLED7SEGBuffer(counter_red, counter_green);
			led_red_and_green();
			counter_red--;
			counter_green--;
			if (counter_green == 0)
			{
				state = RED13_AMBER24;
			}
			break;
		case AMBER13_RED24:
			updateLED7SEGBuffer(counter_amber, counter_red);
			led_yellow_and_red();
			counter_amber--;
			counter_red--;
			if (counter_amber == 0)
			{
				counter_red = 5;
				counter_green = 3;
				counter_amber = 2;
				state = RED13_GREEN24;
			}
			break;
		case GREEN13_RED24:
			updateLED7SEGBuffer(counter_green, counter_red);
			led_green_and_red();
			counter_red--;
			counter_green--;
			if (counter_green == 0)
			{
				state = AMBER13_RED24;
			}
			break;
		default:
			break;
	}
	current_state = state;
}





