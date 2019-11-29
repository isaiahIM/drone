/**
 * @file accel_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief accelerator HAL Library header file
 * @version 0.1
 * @date 2019-10-11
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#ifndef ACCEL_LIB__H
#define ACCEL_LIB__H

#define _USE_MATH_DEFINES
#include <math.h>

#include "common_def.h"
#include "accel_driver.h"
#include "drone_types.h"

typedef int32_t accelType_t;

#define ACCEL_CONNECTED 0X00
#define ACCEL_DISCONNECTED 0X01

#define ACCEL_OK 0X00
#define ACCEL_SET_DATA_FAIL 0X01
#define ACCEL_GET_DATA_FAIL 0X01

#define ACCEL_UNKNOWN_DATA 0x01

#define ACCEL_HW_INIT_FAIL 0x01
#define ACCEL_MEMALLOC_FAIL 0x02

/**
 * @brief Accelerator data structure.
 * 
 */
typedef struct Accel_DataStructure
{
    accelType_t accel_x;///< accel x
    accelType_t accel_y;///< accel y
    accelType_t accel_z;///< accel z
    double roll;///< roll
    double pitch;///< pitch
} Accel_dataStruct;

/**
 * @brief Accelerator initalize structure.
 * 
 */
typedef struct Accel_InitalizeStructure
{
    uint8_t resolution;///< accel resolution bit
    uint32_t capture_freq;///< accel data capture frequency[Hz]
    uint32_t communication_freq;///< accel communication frequency[Hz]
} Accel_initStruct;

/**
 * @brief Accelerator information structure.
 * 
 */
typedef struct Accelinformation_structure
{
    uint8_t count;///< compass count
    Accel_dataStruct *data_arr;///< compass data information array
    Accel_initStruct *init_arr;///< compass initalize information array
} Accel_infoStruct;

/**
 * @brief accelerator H/W, system initalize
 * 
 * @param count accelerator count
 * @return ret initalize result
 *  @arg ACCEL_OK accel initalize success
 *  @arg ACCEL_HW_INIT_FAIL hardware initalize fail
 *  @arg ACCEL_MEMALLOC_FAIL memory initalize fail
 */
ret Accel_Init(uint8_t count);

/**
 * @brief accelerator connect check
 * 
 * @param num accelerator number
 * @return uint8_t connect status
 *  @arg ACCEL_CONNECTED accelerator is connected
 *  @arg ACCEL_DISCONNECTED accelerator is disconnected
 */
uint8_t Accel_ChkConnect(uint8_t num);


/**
 * @brief accelerator resolution setting
 * 
 * @param p_accel accel initalize structure pointer
 * @param resolution_bit accel data resolution bit [bit]
 * @return ret resolution setting result
 *  @arg ACCEL_OK resoluition setting success
 *  @arg ACCEL_SET_DATA_FAIL resolution setting fail
 */
ret Accel_SetResolution(Accel_initStruct *p_accel, uint8_t resolution_bit);

/**
 * @brief accelerator capture frequency set
 * 
 * @param accel p_accel initalize structure pointer
 * @param freq data capture frequency
 * @return ret frequency setting result
 *  @arg ACCEL_OK frequency setting success
 *  @arg ACCEL_SET_DATA_FAIL frequency setting fail
 */
ret Accel_SetCaptureFreq(Accel_initStruct *p_accel, uint32_t freq);

/**
 * @brief accelerator communicate frequency set
 * 
 * @param accel p_accel initalize structure pointer
 * @param freq communicate frequency [Hz]
 * @return ret frequency setting result
 *  @arg ACCEL_OK frequency setting success
 *  @arg ACCEL_SET_DATA_FAIL frequency setting fail
 */
ret Accel_SetCommunicateFreq(Accel_initStruct *p_accel, uint32_t freq);


/**
 * @brief get resolution in structure
 * 
 * @param accel accel initalize structure 
 * @return uint8_t resolution [bit]
 */
uint8_t Accel_GetResolution(Accel_initStruct accel);

/**
 * @brief get capture frequency in structure
 * 
 * @param accel accel initalize structure
 * @return uint32_t resolution[Hz]
 */
uint32_t Accel_GetCaptureFreq(Accel_initStruct accel);

/**
 * @brief get communication frequency in structure
 * 
 * @param accel accel initalize structure
 * @return uint32_t communication speed[Hz]
 */
uint32_t Accel_GetCommunicateFreq(Accel_initStruct accel);


/**
 * @brief get number of accel initalize information
 * 
 * @param num accel number
 * @param p_accel accel initalize structure pointer
 * @return ret get information result
 *  @arg ACCEL_OK get information success
 *  @arg ACCEL_UNKNOWN_DATA accel number is not exist
 */
ret Accel_GetInitalizeInfo(uint8_t num, Accel_initStruct **p_accel);


/**
 * @brief get number of accel data information
 * 
 * @param num accel number
 * @param p_accel accel data structure pointer
 * @return ret get information result
 *  @arg ACCEL_OK get information success
 *  @arg ACCEL_UNKNOWN_DATA accel number is not exist
 */
ret Accel_GetDataInfo(uint8_t num, Accel_dataStruct **p_accel);


/**
 * @brief accelerator sensor data update.
 * 
 * @param num accel number
 * @param p_accel accel dat structure pointer
 * @return ret get sensor data result
 *  @arg ACCEL_OK 
 *  @arg ACCEL_GET_DATA_FAIL 
 */
ret Accel_UpdateData(uint8_t num, Accel_dataStruct *p_accel);

/**
 * @brief get euler angle pitch
 * 
 * @return double pitch angle [range: 0' ~ 180', -1' ~ -179']
 */
double Accel_GetPitch(Accel_dataStruct accel);

/**
 * @brief get euler angle roll
 * 
 * @return double roll angle [range: 0 - +180, -1 ~ -179]
 */
double Accel_GetRoll(Accel_dataStruct accel);

/**
 * @brief get X axis in structure
 * 
 * @param accel accel data structure
 * @return accelType_t X axis data
 */
accelType_t Accel_Get_X(Accel_dataStruct accel);

/**
 * @brief get Y axis in structure
 * 
 * @param accel accel data structure
 * @return accelType_t Y axis data
 */
accelType_t Accel_Get_Y(Accel_dataStruct accel);

/**
 * @brief get Z axis in structure
 * 
 * @param accel accel data structure
 * @return accelType_t Z axis data
 */
accelType_t Accel_Get_Z(Accel_dataStruct accel);

/**
 * @brief terminate accelerator
 * 
 */
void Accel_Terminate(void);
#endif