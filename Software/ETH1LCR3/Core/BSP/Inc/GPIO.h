/*
 * GPIO.h
 *
 *  Created on: Apr 10, 2024
 *      Author: BehrensG
 */

#ifndef BSP_INC_GPIO_H_
#define BSP_INC_GPIO_H_

#include <stdbool.h>

#include "main.h"
#include "BSP.h"

// --------------------------------------------------------------------------------------------------------------------

bool GPIO_SelectGain(uint8_t gain);
void GPIO_DG419(bool state);
bool GPIO_CurrentRange(current_range_t current_range);
void GPIO_InputRelay(bool state);

#endif /* BSP_INC_GPIO_H_ */
