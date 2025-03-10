/*
 * ee24.c
 *
 *  Created on: Feb 10, 2023
 *      Author: grzegorz
 */

#include <EE24.h>

#if (_EEPROM_USE_FREERTOS == 1)
#include "cmsis_os.h"
#define ee24_delay(x)   vTaskDelay(pdMS_TO_TICKS(x))
#else
#define ee24_delay(x)   HAL_Delay(x)
#endif

#if (_EEPROM_SIZE_KBIT == 1) || (_EEPROM_SIZE_KBIT == 2)
#define _EEPROM_PSIZE     8
#elif (_EEPROM_SIZE_KBIT == 4) || (_EEPROM_SIZE_KBIT == 8) || (_EEPROM_SIZE_KBIT == 16)
#define _EEPROM_PSIZE     16
#else
#define _EEPROM_PSIZE     32
#endif

uint8_t ee24_lock = 0;
//################################################################################################################
bool ee24_isConnected(uint8_t eeprom_address)
{
  #if (_EEPROM_USE_WP_PIN==1)
  HAL_GPIO_WritePin(_EEPROM_WP_GPIO,_EEPROM_WP_PIN,GPIO_PIN_SET);
  #endif
  if (HAL_I2C_IsDeviceReady(&_EEPROM_I2C, eeprom_address, 2, 1000)==HAL_OK)
    return true;
  else
    return false;
}
//################################################################################################################
bool ee24_write(uint8_t eeprom_address, uint16_t address, uint8_t *data, size_t len)
{
  if (ee24_lock == 1)
    return false;
  ee24_lock = 1;
  uint16_t w;
  uint32_t startTime = HAL_GetTick();
  #if	(_EEPROM_USE_WP_PIN==1)
  HAL_GPIO_WritePin(_EEPROM_WP_GPIO, _EEPROM_WP_PIN,GPIO_PIN_RESET);
  #endif
  while (1)
  {
    w = _EEPROM_PSIZE - (address  % _EEPROM_PSIZE);
    if (w > len)
      w = len;
    #if ((_EEPROM_SIZE_KBIT==1) || (_EEPROM_SIZE_KBIT==2))
    if (HAL_I2C_Mem_Write(&_EEPROM_I2C, eeprom_address, address, I2C_MEMADD_SIZE_8BIT, data, w, 1000) == HAL_OK)
    #elif (_EEPROM_SIZE_KBIT==4)
    if (HAL_I2C_Mem_Write(&_EEPROM_I2C, eeprom_address | ((address & 0x0100) >> 7), (address & 0xff), I2C_MEMADD_SIZE_8BIT, data, w, 1000) == HAL_OK)
    #elif (_EEPROM_SIZE_KBIT==8)
    if (HAL_I2C_Mem_Write(&_EEPROM_I2C, eeprom_address | ((address & 0x0300) >> 7), (address & 0xff), I2C_MEMADD_SIZE_8BIT, data, w, 1000) == HAL_OK)
    #elif (_EEPROM_SIZE_KBIT==16)
    if (HAL_I2C_Mem_Write(&_EEPROM_I2C, eeprom_address | ((address & 0x0700) >> 7), (address & 0xff), I2C_MEMADD_SIZE_8BIT, data, w, 1000) == HAL_OK)
    #else
    if (HAL_I2C_Mem_Write(&_EEPROM_I2C, eeprom_address, address, I2C_MEMADD_SIZE_16BIT, data, w, 1000) == HAL_OK)
    #endif
    {
      ee24_delay(10);
      len -= w;
      data += w;
      address += w;
      if (len == 0)
      {
        #if (_EEPROM_USE_WP_PIN==1)
        HAL_GPIO_WritePin(_EEPROM_WP_GPIO, _EEPROM_WP_PIN, GPIO_PIN_SET);
        #endif
        ee24_lock = 0;
        return true;
      }
      if (HAL_GetTick() - startTime >= 20000)
      {
        ee24_lock = 0;
        return false;
      }
    }
    else
    {
      #if (_EEPROM_USE_WP_PIN==1)
      HAL_GPIO_WritePin(_EEPROM_WP_GPIO, _EEPROM_WP_PIN, GPIO_PIN_SET);
      #endif
      ee24_lock = 0;
      return false;
    }
  }
}
//################################################################################################################
bool ee24_read(uint8_t eeprom_address, uint16_t address, uint8_t *data, size_t len)
{
  if (ee24_lock == 1)
    return false;
  ee24_lock = 1;
  #if (_EEPROM_USE_WP_PIN==1)
  HAL_GPIO_WritePin(_EEPROM_WP_GPIO, _EEPROM_WP_PIN, GPIO_PIN_SET);
  #endif
  #if ((_EEPROM_SIZE_KBIT==1) || (_EEPROM_SIZE_KBIT==2))
  if (HAL_I2C_Mem_Read(&_EEPROM_I2C, eeprom_address, address, I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK)
  #elif (_EEPROM_SIZE_KBIT == 4)
  if (HAL_I2C_Mem_Read(&_EEPROM_I2C, eeprom_address | ((address & 0x0100) >> 7), (address & 0xff), I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK)
  #elif (_EEPROM_SIZE_KBIT == 8)
  if (HAL_I2C_Mem_Read(&_EEPROM_I2C, eeprom_address | ((address & 0x0300) >> 7), (address & 0xff), I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK)
  #elif (_EEPROM_SIZE_KBIT==16)HAL_I2C_Mem_Read
  if (HAL_I2C_Mem_Read(&_EEPROM_I2C, eeprom_address | ((address & 0x0700) >> 7), (address & 0xff), I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK)
  #else
  if (HAL_I2C_Mem_Read(&_EEPROM_I2C, eeprom_address, address, I2C_MEMADD_SIZE_16BIT, data, len, 1000) == HAL_OK)
  #endif
  {
    ee24_lock = 0;
    return true;
  }
  else
  {
    ee24_lock = 0;
    return false;
  }
}
//################################################################################################################
bool ee24_eraseChip(uint8_t eeprom_address)
{
  const uint8_t eraseData[32] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF\
    , 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint32_t bytes = 0;
  while ( bytes < (_EEPROM_SIZE_KBIT * 256))
  {
    if (ee24_write(eeprom_address, bytes, (uint8_t*)eraseData, sizeof(eraseData)) == false)
      return false;
    bytes += sizeof(eraseData);
  }
  return true;
}
//################################################################################################################

