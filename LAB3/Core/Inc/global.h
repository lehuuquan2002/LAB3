/*
 * global.h
 *
 *  Created on: Oct 27, 2024
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <input_reading.h>
#include "soft_timer.h"
#include "display7SEG.h"

#define INIT 						0
#define RED13_GREEN24 				1
#define RED13_AMBER24 				2
#define GREEN13_RED24 				3
#define AMBER13_RED24 				4

#define NORMAL 						11
#define SET_TIME_RED 				12
#define SET_TIME_AMBER 				13
#define SET_TIME_GREEN 				14

#define TIMER_UPDATE_7SEG 			1
#define TIMER_UPDATE_7SEG_DUR		250

#define TIMER_LIGHT_TRAFFIC			0
#define TIMER_LIGHT_TRAFFIC_DUR	 	1000

#define TIMER_SET_LED				2
#define TIMER_SET_LED_DUR		 	250



extern int state,current_state;
extern int time_red,time_amber,time_green;
extern int index_led;
extern int mode;
extern int counter_red, counter_amber, counter_green;

extern int value;

void clear_led_red_amber_green();

#endif /* INC_GLOBAL_H_ */
