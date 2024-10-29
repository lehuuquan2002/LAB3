/*
 * fms_auto.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Admin
 */

#include "light_traffic.h"
#include "display7SEG.h"
#include "soft_timer.h"
#include "fsm_auto.h"
#include "global.h"

static int set_led_status = 0;

void fsm_auto(void)
{
	updateLed7SEG(index_led);
	if (getTimerFlag(TIMER_UPDATE_7SEG))
	{
		index_led++;
		if (index_led > 4)
		{
			index_led = 1;
		}
		setTimer(TIMER_UPDATE_7SEG, TIMER_UPDATE_7SEG_DUR);
	}
	switch (mode) {
		case NORMAL:

			if (getTimerFlag(TIMER_LIGHT_TRAFFIC))
			{
				updateTrafficLight();
				setTimer(TIMER_LIGHT_TRAFFIC, TIMER_LIGHT_TRAFFIC_DUR);
			}

			break;
		case SET_TIME_RED:
			updateLED7SEGBuffer(mode, time_red);
			if (getTimerFlag(TIMER_SET_LED))
			{
				HAL_GPIO_WritePin(RED13_GPIO_Port, RED13_Pin, set_led_status);
				HAL_GPIO_WritePin(RED24_GPIO_Port, RED24_Pin, set_led_status);
				set_led_status = !set_led_status;
				setTimer(TIMER_SET_LED, TIMER_SET_LED_DUR);
			}
			break;
		case SET_TIME_GREEN:
			updateLED7SEGBuffer(mode, time_green);
			if (getTimerFlag(TIMER_SET_LED))
			{
				HAL_GPIO_WritePin(GREEN13_GPIO_Port, GREEN13_Pin, set_led_status);
				HAL_GPIO_WritePin(GREEN24_GPIO_Port, GREEN24_Pin, set_led_status);
				set_led_status = !set_led_status;
				setTimer(TIMER_SET_LED, TIMER_SET_LED_DUR);
			}
			break;
		case SET_TIME_AMBER:
			updateLED7SEGBuffer(mode, time_amber);
			if (getTimerFlag(TIMER_SET_LED))
			{
				HAL_GPIO_WritePin(AMBER13_GPIO_Port, AMBER13_Pin, set_led_status);
				HAL_GPIO_WritePin(AMBER24_GPIO_Port, AMBER24_Pin, set_led_status);
				set_led_status = !set_led_status;
				setTimer(TIMER_SET_LED, TIMER_SET_LED_DUR);
			}
			break;
		default:
			break;
	}
}
