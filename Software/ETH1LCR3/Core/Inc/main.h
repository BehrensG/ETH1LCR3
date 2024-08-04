/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_crs.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_exti.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCU_DEFAULT_Pin LL_GPIO_PIN_2
#define MCU_DEFAULT_GPIO_Port GPIOE
#define MCU_G1_Pin LL_GPIO_PIN_0
#define MCU_G1_GPIO_Port GPIOA
#define MCU_G100_Pin LL_GPIO_PIN_3
#define MCU_G100_GPIO_Port GPIOA
#define MCU_G10_Pin LL_GPIO_PIN_4
#define MCU_G10_GPIO_Port GPIOA
#define MCU_ZOFFS_Pin LL_GPIO_PIN_5
#define MCU_ZOFFS_GPIO_Port GPIOA
#define MCU_RLY_nA_Pin LL_GPIO_PIN_7
#define MCU_RLY_nA_GPIO_Port GPIOE
#define MCU_RLY_OUT_Pin LL_GPIO_PIN_8
#define MCU_RLY_OUT_GPIO_Port GPIOE
#define MCU_RLY_uA_Pin LL_GPIO_PIN_9
#define MCU_RLY_uA_GPIO_Port GPIOE
#define MCU_RLY_mA_Pin LL_GPIO_PIN_10
#define MCU_RLY_mA_GPIO_Port GPIOE
#define LED_BLUE_Pin LL_GPIO_PIN_6
#define LED_BLUE_GPIO_Port GPIOC
#define LED_RED_Pin LL_GPIO_PIN_7
#define LED_RED_GPIO_Port GPIOC
#define LED_GREEN_Pin LL_GPIO_PIN_8
#define LED_GREEN_GPIO_Port GPIOC
#define EEPROM_nWP_Pin LL_GPIO_PIN_5
#define EEPROM_nWP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
