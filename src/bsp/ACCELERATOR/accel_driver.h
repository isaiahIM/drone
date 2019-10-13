#ifndef ACCEL_DRIVER__H
#define ACCEL_DRIVER__H

#define BSP_ACCEL_OK 0x00
#define BSP_ACCEL_FAIL 0x01

#define BSP_ACCEL_CONNECTED 0X00
#define BSP_ACCEL_DISCONNECTED 0X01

#include "accel_driver.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief accel peripheral initalize
 * 
 * @return uint8_t initalize result
 *  @arg BSP_ACCEL_OK peripheral initalize success
 *  @arg BSP_ACCEL_FAIL peripheral initalize fail
 */
uint8_t BSP_Accel_HW_Initalize(void);

/**
 * @brief accel connect check
 * 
 * @param num accel number
 * @return uint8_t connect result
 *  @arg BSP_ACCEL_OK accelerator connect
 *  @arg BSP_ACCEL_DISCONNECTED accelator disconnected
 */
uint8_t BSP_Accel_ChkConnect(uint8_t num);

/**
 * @brief set accel data resolution
 * 
 * @param num accel nummer
 * @param resolution resolution [bit]
 * @return uint8_t resolution setting result
 *  @arg BSP_ACCEL_OK resolution setting success
 *  @arg BSP_ACCEL_FAIL resolution setting fail
 */
uint8_t BSP_Accel_SetReolution(uint8_t num, uint8_t resolution);

/**
 * @brief set accel data capture frequency
 * 
 * @param num accel number
 * @param freq capture frequency[HZ]
 * @return uint8_t capture frequency setting result
 *  @arg BSP_ACCEL_OK capture frequency setting success
 *  @arg BSP_ACCEL_FAIL capture frequency setting fail
 */
uint8_t BSP_Accel_SetCaptureFreq(uint8_t num, uint32_t freq);

/**
 * @brief set accel communicate frequency
 * 
 * @param num accel number
 * @param freq communication frequency[HZ]
 * @return uint8_t communication frequency setting result
 *  @arg BSP_ACCEL_OK communication frequency setting success
 *  @arg BSP_ACCEL_FAIL communication frequency setting fail
 */
uint8_t BSP_Accel_SetCommunicateFreq(uint8_t num, uint32_t freq);

/**
 * @brief get accel x data
 * 
 * @param num accel number
 * @param x x data
 * @return uint8_t get data result
 *  @arg BSP_ACCEL_OK data get success
 *  @arg BSP_ACCEL_FAIL data get fail
 */
uint8_t BSP_Accel_GetX(uint8_t num, uint32_t *x);

/**
 * @brief get accel y data
 * 
 * @param num accel number
 * @param y y data
 * @return uint8_t get data result
 *  @arg BSP_ACCEL_OK data get success
 *  @arg BSP_ACCEL_FAIL data get fail
 */
uint8_t BSP_Accel_GetY(uint8_t num, uint32_t *y);

/**
 * @brief get accel z data
 * 
 * @param num accel number
 * @param z z data
 * @return uint8_t get data result
 *  @arg BSP_ACCEL_OK data get success
 *  @arg BSP_ACCEL_FAIL data get fail
 */
uint8_t BSP_Accel_GetZ(uint8_t num, uint32_t *z);

#endif