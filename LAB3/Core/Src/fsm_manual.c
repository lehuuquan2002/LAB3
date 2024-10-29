/*
 * fsm_manual.c
 *
 *  Created on: Oct 28, 2024
 *      Author: Admin
 */

#include <input_reading.h>
#include <light_traffic.h>
#include <display7SEG.h>
#include <soft_timer.h>

void fsm_manual(void)
{
	int temp = 0;

	switch (mode) {
		case NORMAL:
			if (isButtonPressed(0))
			{
				clear_led_red_amber_green();
				value = time_red;
				mode = SET_TIME_RED;
				setTimer(TIMER_SET_LED, TIMER_SET_LED_DUR);
				updateLED7SEGBuffer(mode, value);
			}

			if (isButtonPressed(1))
			{

			}

			if (isButtonPressed(2))
			{

			}
			break;
		case SET_TIME_RED:

			if (isButtonPressed(0))
			{
				clear_led_red_amber_green();
				value = time_amber;
				mode = SET_TIME_AMBER;
			}

			if (isButtonPressed(1))
			{
				value++;
				if (value > 99)
				{
					value = 0;
				}
			}

			if (isButtonPressed(2))
			{
				temp = 0;
				temp = value - time_red;
				time_red = value;
				time_green += temp;

			}
			updateLED7SEGBuffer(mode, value);
			break;
		case SET_TIME_AMBER:
			if (isButtonPressed(0))
			{
				clear_led_red_amber_green();
				value = time_green;
				mode = SET_TIME_GREEN;
			}

			if (isButtonPressed(1))
			{
				value++;
				if (value > 99)
				{
					value = 0;
				}
			}

			if (isButtonPressed(2))
			{
				time_amber = value;
			}
			updateLED7SEGBuffer(mode, value);
			break;
		case SET_TIME_GREEN:
			if (isButtonPressed(0))
			{
				clear_led_red_amber_green();
				current_state = INIT;
				mode = NORMAL;
			}

			if (isButtonPressed(1))
			{
				value++;
				if (value > 99)
				{
					value = 0;
				}
			}

			if (isButtonPressed(2))
			{
				temp = 0;
				temp = value - time_green;
				time_green = value;
				time_red += temp;
			}
			updateLED7SEGBuffer(mode, value);
			break;
		default:
			break;
	}
}
