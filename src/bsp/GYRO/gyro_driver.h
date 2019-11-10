#ifndef GYRO_DRIVER__H
#define GYRO_DRIVER__H

#define BSP_GYRO_OK 0x00
#define BSP_GYRO_FAIL 0x01

#define BSP_GYRO_CONNECTED 0X00
#define BSP_GYRO_DISCONNECTED 0X01

#include "gyro_driver.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief gyro peripheral initalize
 * 
 * @return uint8_t initalize result
 *  @arg BSP_GYRO_OK peripheral initalize success
 *  @arg BSP_GYRO_FAIL peripheral initalize fail
 */
uint8_t BSP_Gyro_HW_Initalize(void);

/**
 * @brief gyro connect check
 * 
 * @param num gyro number
 * @return uint8_t connect result
 *  @arg BSP_GYRO_CONNECTED gyroscope connect
 *  @arg BSP_GYRO_DISCONNECTED gyroscope disconnected
 */
uint8_t BSP_Gyro_ChkConnect(uint8_t num);

/**
 * @brief set gyro data resolution
 * 
 * @param num gyro nummer
 * @param resolution resolution [bit]
 * @return uint8_t resolution setting result
 *  @arg BSP_GYRO_OK resolution setting success
 *  @arg BSP_GYRO_FAIL resolution setting fail
 */
uint8_t BSP_Gyro_SetReolution(uint8_t num, uint8_t resolution);

/**
 * @brief set gyro data capture frequency
 * 
 * @param num gyro number
 * @param freq capture frequency[HZ]
 * @return uint8_t capture frequency setting result
 *  @arg BSP_GYRO_OK capture frequency setting success
 *  @arg BSP_GYRO_FAIL capture frequency setting fail
 */
uint8_t BSP_Gyro_SetCaptureFreq(uint8_t num, uint32_t freq);

/**
 * @brief set gyro communicate frequency
 * 
 * @param num gyro number
 * @param freq communication frequency[HZ]
 * @return uint8_t communication frequency setting result
 *  @arg BSP_GYRO_OK communication frequency setting success
 *  @arg BSP_GYRO_FAIL communication frequency setting fail
 */
uint8_t BSP_Gyro_SetCommunicateFreq(uint8_t num, uint32_t freq);

/**
 * @brief get gyro x data
 * 
 * @param num gyro number
 * @param p_x x data
 * @return uint8_t get data result
 *  @arg BSP_GYRO_OK data get success
 *  @arg BSP_GYRO_FAIL data get fail
 */
uint8_t BSP_Gyro_GetX(uint8_t num, int32_t *p_x);

/**
 * @brief get gyro y data
 * 
 * @param num gyro number
 * @param p_y y data
 * @return uint8_t get data result
 *  @arg BSP_GYRO_OK data get success
 *  @arg BSP_GYRO_FAIL data get fail
 */
uint8_t BSP_Gyro_GetY(uint8_t num, int32_t *p_y);

/**
 * @brief get gyro z data
 * 
 * @param num gyro number
 * @param p_z z data
 * @return uint8_t get data result
 *  @arg BSP_GYRO_OK data get success
 *  @arg BSP_GYRO_FAIL data get fail
 */
uint8_t BSP_Gyro_GetZ(uint8_t num, int32_t *p_z);

#endif