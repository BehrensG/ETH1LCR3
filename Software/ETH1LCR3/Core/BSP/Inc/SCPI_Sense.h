/*
 * SCPI_Sense.h
 *
 *  Created on: Jul 12, 2024
 *      Author: BehrensG
 */

#ifndef BSP_INC_SCPI_SENSE_H_
#define BSP_INC_SCPI_SENSE_H_

#include "scpi/scpi.h"

// --------------------------------------------------------------------------------------------------------------------

scpi_result_t SCPI_SenseCurrentRange(scpi_t * context);
scpi_result_t SCPI_SenseCurrentRangeQ(scpi_t * context);

scpi_result_t SCPI_SenseInputRelay(scpi_t * context);
scpi_result_t SCPI_SenseInputRelayQ(scpi_t * context);

#endif /* BSP_INC_SCPI_SENSE_H_ */
