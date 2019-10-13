#ifndef COMPASS_DRIVER__H
#define COMPASS_DRIVER__H

#define BSP_COMPASS_OK 0x00
#define BSP_COMPASS_FAIL 0x01

#define BSP_COMPASS_CONNECTED 0X00
#define BSP_COMPASS_DISCONNECTED 0X01

#include "compass_driver.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief compass peripheral initalize
 * 
 * @return uint8_t initalize result
 *  @arg BSP_COMPASS_OK peripheral initalize success
 *  @arg BSP_COMPASS_FAIL peripheral initalize fail
 */
uint8_t BSP_Compass_HW_Initalize(void);

/**
 * @brief compass connect check
 * 
 * @param num compass number
 * @return uint8_t connect result
 *  @arg BSP_COMPASS_CONNECTED compass connect
 *  @arg BSP_COMPASS_DISCONNECTED compass disconnected
 */
uint8_t BSP_Compass_ChkConnect(uint8_t num);

/**
 * @brief set compass data resolution
 * 
 * @param num compass nummer
 * @param resolution resolution [bit]
 * @return uint8_t resolution setting result
 *  @arg BSP_COMPASS_OK resolution setting success
 *  @arg BSP_COMPASS_FAIL resolution setting fail
 */
uint8_t BSP_Compass_SetReolution(uint8_t num, uint8_t resolution);

/**
 * @brief set compass data capture frequency
 * 
 * @param num compass number
 * @param freq capture frequency[HZ]
 * @return uint8_t capture frequency setting result
 *  @arg BSP_COMPASS_OK capture frequency setting success
 *  @arg BSP_COMPASS_FAIL capture frequency setting fail
 */
uint8_t BSP_Compass_SetCaptureFreq(uint8_t num, uint32_t freq);

/**
 * @brief set compass communicate frequency
 * 
 * @param num compass number
 * @param freq communication frequency[HZ]
 * @return uint8_t communication frequency setting result
 *  @arg BSP_COMPASS_OK communication frequency setting success
 *  @arg BSP_COMPASS_FAIL communication frequency setting fail
 */
uint8_t BSP_Compass_SetCommunicateFreq(uint8_t num, uint32_t freq);

/**
 * @brief get compass x data
 * 
 * @param num compass number
 * @param x x data
 * @return uint8_t get data result
 *  @arg BSP_COMPASS_OK data get success
 *  @arg BSP_COMPASS_FAIL data get fail
 */
uint8_t BSP_Compass_GetX(uint8_t num, uint32_t *x);

/**
 * @brief get compass y data
 * 
 * @param num compass number
 * @param y y data
 * @return uint8_t get data result
 *  @arg BSP_COMPASS_OK data get success
 *  @arg BSP_COMPASS_FAIL data get fail
 */
uint8_t BSP_Compass_GetY(uint8_t num, uint32_t *y);

/**
 * @brief get compass z data
 * 
 * @param num compass number
 * @param z z data
 * @return uint8_t get data result
 *  @arg BSP_COMPASS_OK data get success
 *  @arg BSP_COMPASS_FAIL data get fail
 */
uint8_t BSP_Compass_GetZ(uint8_t num, uint32_t *z);

#endif