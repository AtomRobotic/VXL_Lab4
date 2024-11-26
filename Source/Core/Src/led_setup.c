/*
 * led_setup.c
 *
 *  Created on: Nov 26, 2024
 *      Author: ADMIN
 */

#include"led_setup.h"
#include "main.h"

void BlinkingRedLed(){
	HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);
}

void BlinkingGreenLed(){
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
}

void BlinkingYellowLed(){
	HAL_GPIO_TogglePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin);
}

void BlinkingBlueLed(){
	HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
}

void BlinkingPinkLed(){
	HAL_GPIO_TogglePin(PINK_LED_GPIO_Port, PINK_LED_Pin);
}
