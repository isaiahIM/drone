/**
 * @file gyro_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief gyroscope HAL Library header file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#ifndef GYRO_LIB__H
#define GYRO_LIB__H

#include "gyro_lib.c"
#include "gyro_dirver.h"

typedef uint16_t gyroType_t;

#define GYRO_CONNECTED 0X00
#define GYRO_DISCONNECTED 0X01

#define GYRO_OK 0X00
#define GYRO_INIT_FAIL 0X01
/**
 * @brief Gyroscope data structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Gyro_DataStructure
{
    uint8_t num;///< gyro number
    gyroType_t gyro_x;///< gyro x
    gyroType_t gyro_y;///< gyro y
    gyroType_t gyro_z;///< gyro z
    struct Gyro_DataStructure *next;///< next link
} Gyro_DataStruct;

/**
 * @brief Gyroscope initalize structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Gyro_InitalizeStructure
{
    uint8_t num;///< gyro number
    uint8_t gyro_resolution;///< gyro resolution bit
    struct Gyro_InitalizeStructure *next;///< next link
} Gyro_initStruct;

Gyro_DataStruct *prev, *cur, *head;
Gyro_initStruct *prev, cur, *head;

/**
 * @brief gyroscope connect check
 * 
 * @return uint8_t connect status
 *  @arg GYRO_CONNECTED gyroscope is connected
 *  @arg GYRO_DISCONNECTED gyroscope is disconnected
 */
uint8_t Gyro_ConnectCheck(void);

/**
 * @brief gyroscope initalize
 * 
 * @param num gyro number
 * @param resolution gyro data resolution
 * @return ret initalize result
 *  @arg GYRO_OK gyroscope initalize success
 *  @arg GYRO_INIT_FAIL gyroscope initalze fail
 */
ret Gyro_Initalize(uint8_t num, uint8_t resolution);

/**
 * @brief 
 * 
 * @param num 
 * @param gyro_x 
 * @return ret 
 */
ret Gyro_Get_X(uint8_t num, gyroType_t *gyro_x);
ret Gyro_Get_Y(uint8_t num, gyroType_t *gyro_y);
ret Gyro_Get_Z(uint8_t num, gyroType_t *gyro_z);

#endif