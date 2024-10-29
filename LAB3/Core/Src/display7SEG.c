/*
 * display7SEG.c
 *
 *  Created on: Oct 27, 2024
 *      Author: Admin
 */

#include <display7SEG.h>
#include "main.h"
#include "stm32f1xx.h"

int NUM [10][7]=
{
	{0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1},
	{0,0,1,0,0,1,0},
	{0,0,0,0,1,1,0},
	{1,0,0,1,1,0,0},
	{0,1,0,0,1,0,0},
	{0,1,0,0,0,0,0},
	{0,0,0,1,1,1,1},
	{0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0}
};

int led7SEGBuffer[4] = {0 ,0 ,0 ,0};
int index_led = 1;

static void display7SEG(int num)
{
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, NUM[num][0]);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, NUM[num][1]);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, NUM[num][2]);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, NUM[num][3]);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, NUM[num][4]);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, NUM[num][5]);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, NUM[num][6]);
}

static void clearLed7SEG(){
	HAL_GPIO_WritePin(GPIOA, EN1_Pin | EN2_Pin | EN3_Pin | EN4_Pin , SET);
}

void updateLED7SEGBuffer(int value_1, int value_2)
{
	led7SEGBuffer[0] = value_1/10;
	led7SEGBuffer[1] = value_1%10;
	led7SEGBuffer[2] = value_2/10;
	led7SEGBuffer[3] = value_2%10;
}

void updateLed7SEG(int index)
{
	switch (index) {
		case 1:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_SET);
			display7SEG(led7SEGBuffer[index - 1]);
			break;
		case 2:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_SET);
			display7SEG(led7SEGBuffer[index - 1]);
			break;
		case 3:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_SET);
			display7SEG(led7SEGBuffer[index - 1]);
			break;
		case 4:
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(EN4_GPIO_Port, EN4_Pin, GPIO_PIN_RESET);
			display7SEG(led7SEGBuffer[index - 1]);
			break;
		default:
			break;
	}
}
