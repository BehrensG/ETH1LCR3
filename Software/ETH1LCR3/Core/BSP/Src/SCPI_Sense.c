/*
 * SCPI_Sense.c
 *
 *  Created on: Jul 12, 2024
 *      Author: BehrensG
 */

// --------------------------------------------------------------------------------------------------------------------

#include "SCPI_Sense.h"
#include "BSP.h"
#include "GPIO.h"
#include "Utility.h"

// --------------------------------------------------------------------------------------------------------------------

extern bsp_t bsp;

// --------------------------------------------------------------------------------------------------------------------

scpi_choice_def_t current_range_select[] =
{
    {"mA", mA},
    {"uA", uA},
	{"nA", nA},
    SCPI_CHOICE_LIST_END
};


scpi_result_t SCPI_SenseCurrentRange(scpi_t * context)
{
	int32_t value;

	if (!SCPI_ParamChoice(context, current_range_select, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.current_range = (current_range_t)value;

	GPIO_CurrentRange(bsp.current_range);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseCurrentRangeQ(scpi_t * context)
{

	switch (bsp.current_range)
	{
		case mA : SCPI_ResultCharacters(context, "mA", 2); break;
		case uA : SCPI_ResultCharacters(context, "uA", 2); break;
		case nA : SCPI_ResultCharacters(context, "nA", 2); break;
		default : SCPI_ResultCharacters(context, "mA", 2); break;
	}

	return SCPI_RES_OK;
}

// --------------------------------------------------------------------------------------------------------------------

scpi_result_t SCPI_SenseInputRelay(scpi_t * context)
{
	scpi_bool_t value;

	if(!SCPI_ParamBool(context, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.input_relay = value;

	GPIO_InputRelay(bsp.input_relay);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseInputRelayQ(scpi_t * context)
{
	SCPI_ResultBool(context, bsp.input_relay);
	return SCPI_RES_OK;
}

