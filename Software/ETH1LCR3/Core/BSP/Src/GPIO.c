/*
 * GPIO.c
 *
 *  Created on: Apr 10, 2024
 *      Author: BehrensG
 */

// --------------------------------------------------------------------------------------------------------------------

#include "cmsis_os.h"

#include "GPIO.h"


// --------------------------------------------------------------------------------------------------------------------

bool GPIO_SelectGain(uint8_t gain)
{
	switch (gain)
	{
		case 1:
			{
				LL_GPIO_SetOutputPin(MCU_G1_GPIO_Port, MCU_G1_Pin);
				LL_GPIO_ResetOutputPin(MCU_G10_GPIO_Port, MCU_G10_Pin);
				LL_GPIO_ResetOutputPin(MCU_G100_GPIO_Port, MCU_G100_Pin);
			};break;

		case 10:
			{
				LL_GPIO_SetOutputPin(MCU_G10_GPIO_Port, MCU_G10_Pin);
				LL_GPIO_ResetOutputPin(MCU_G1_GPIO_Port, MCU_G1_Pin);
				LL_GPIO_ResetOutputPin(MCU_G100_GPIO_Port, MCU_G100_Pin);
			};break;

		case 100:
			{
				LL_GPIO_SetOutputPin(MCU_G100_GPIO_Port, MCU_G100_Pin);
				LL_GPIO_ResetOutputPin(MCU_G1_GPIO_Port, MCU_G1_Pin);
				LL_GPIO_ResetOutputPin(MCU_G10_GPIO_Port, MCU_G10_Pin);
			};break;

		default: return false;
	}

	return true;

}

// --------------------------------------------------------------------------------------------------------------------

bool GPIO_CurrentRange(current_range_t current_range)
{
	switch (current_range)
	{
		case mA :
			{
				vTaskDelay(pdMS_TO_TICKS(50));
				LL_GPIO_SetOutputPin(MCU_RLY_mA_GPIO_Port, MCU_RLY_mA_Pin);
				vTaskDelay(pdMS_TO_TICKS(50));
				LL_GPIO_ResetOutputPin(MCU_RLY_uA_GPIO_Port, MCU_RLY_uA_Pin);
				LL_GPIO_ResetOutputPin(MCU_RLY_nA_GPIO_Port, MCU_RLY_nA_Pin);
				vTaskDelay(pdMS_TO_TICKS(50));

			};break;

		case uA :
			{
				vTaskDelay(pdMS_TO_TICKS(50));
				LL_GPIO_SetOutputPin(MCU_RLY_uA_GPIO_Port, MCU_RLY_uA_Pin);
				vTaskDelay(pdMS_TO_TICKS(50));
				LL_GPIO_ResetOutputPin(MCU_RLY_mA_GPIO_Port, MCU_RLY_mA_Pin);
				LL_GPIO_ResetOutputPin(MCU_RLY_nA_GPIO_Port, MCU_RLY_nA_Pin);
				vTaskDelay(pdMS_TO_TICKS(50));

			};break;

		case nA :
			{
				vTaskDelay(pdMS_TO_TICKS(50));
				LL_GPIO_SetOutputPin(MCU_RLY_nA_GPIO_Port, MCU_RLY_nA_Pin);
				vTaskDelay(pdMS_TO_TICKS(50));
				LL_GPIO_ResetOutputPin(MCU_RLY_mA_GPIO_Port, MCU_RLY_mA_Pin);
				LL_GPIO_ResetOutputPin(MCU_RLY_uA_GPIO_Port, MCU_RLY_uA_Pin);
				vTaskDelay(pdMS_TO_TICKS(50));

			};break;

		default: return false;
	}

	return true;

}


// --------------------------------------------------------------------------------------------------------------------

void GPIO_DG419(bool state)
{
	(state) ? LL_GPIO_SetOutputPin(MCU_ZOFFS_GPIO_Port, MCU_ZOFFS_Pin) : LL_GPIO_ResetOutputPin(MCU_ZOFFS_GPIO_Port, MCU_ZOFFS_Pin);
}

// --------------------------------------------------------------------------------------------------------------------

void GPIO_InputRelay(bool state)
{
	vTaskDelay(pdMS_TO_TICKS(50));
	(state) ? LL_GPIO_SetOutputPin(MCU_RLY_OUT_GPIO_Port, MCU_RLY_OUT_Pin) : LL_GPIO_ResetOutputPin(MCU_RLY_OUT_GPIO_Port, MCU_RLY_OUT_Pin);
	vTaskDelay(pdMS_TO_TICKS(50));
}
