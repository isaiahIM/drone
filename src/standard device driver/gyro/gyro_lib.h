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

#include "common_def.h"
#include "gyro_driver.h"
#include "drone_types.h"
#include "time.h"

typedef int16_t gyroType_t;

#define GYRO_CONNECTED 0X00
#define GYRO_DISCONNECTED 0X01

#define GYRO_OK 0X00
#define GYRO_SET_DATA_FAIL 0X01
#define GYRO_GET_DATA_FAIL 0X01

#define GYRO_UNKNOWN_DATA 0x01

#define GYRO_HW_INIT_FAIL 0x01
#define GYRO_MEMALLOC_FAIL 0X02

/**
 * @brief Gyroscope data structure.
 * 
 */
typedef struct Gyro_DataStructure
{
    gyroType_t gyro_x;///< Angular velocity x [degree/S]
    gyroType_t gyro_y;///< Angular velocity y [degree/S]
    gyroType_t gyro_z;///< Angular velocity z [degree/S]
    double yaw;///< yaw
    double pitch;///< pitch
    double roll;///< roll
    double cap_sec;///< data capture time[second]
} Gyro_dataStruct;

/**
 * @brief Gyroscope initalize structure.
 * 
 */
typedef struct Gyro_InitalizeStructure
{
    uint8_t resolution;///< gyro resolution bit
    uint32_t capture_freq;///< gyro data capture frequency[Hz]
    uint32_t communication_freq;///< gyro communication frequency[Hz]
} Gyro_initStruct;

/**
 * @brief gyro information structure
 * 
 */
typedef struct Gyro_information_structure
{
    uint8_t count;///< gyro count
    Gyro_dataStruct *data_arr;///< gyro data information array
    Gyro_initStruct *init_arr;///< gyro initalize information array
} Gyro_infoStruct;

/*user functions*/

/**
 * @brief gyroscope H/W, system initalize
 * 
 * @param count gyroscope count
 * @return ret initalize result
 *  @arg GYRO_OK gyro initalize success
 *  @arg GYRO_HW_INIT_FAIL hardware initalize fail
 *  @arg GYRO_MEMALLOC_FAIL memory initalize fail
 */
ret Gyro_Init(uint8_t count);

/**
 * @brief gyroscope connect check
 * 
 * @param num gyroscope number
 * @return uint8_t connect status
 *  @arg GYRO_CONNECTED gyroscope is connected
 *  @arg GYRO_DISCONNECTED gyroscope is disconnected
 */
uint8_t Gyro_ChkConnect(uint8_t num);


/**
 * @brief gyroscope resolution setting
 * 
 * @param p_gyro gyro initalize structure pointer
 * @param resolution_bit gyro data resolution bit [bit]
 * @return ret resolution setting result
 *  @arg GYRO_OK resoluition setting success
 *  @arg GYRO_SET_DATA_FAIL resolution setting fail
 */
ret Gyro_SetResolution(Gyro_initStruct *p_gyro, uint8_t resolution_bit);

/**
 * @brief gyroscope capture frequency set
 * 
 * @param gyro gyro initalize structure pointer
 * @param freq data capture frequency [HZ]
 * @return ret frequency setting result
 *  @arg GYRO_OK frequency setting success
 *  @arg GYRO_SET_DATA_FAIL frequency setting fail
 */
ret Gyro_SetCaptureFreq(Gyro_initStruct *p_gyro, uint32_t freq);

/**
 * @brief gyroscope communicate frequency set
 * 
 * @param gyro gyro initalize structure pointer
 * @param freq communicate frequency [Hz]
 * @return ret frequency setting result
 *  @arg GYRO_OK frequency setting success
 *  @arg GYRO_SET_DATA_FAIL frequency setting fail
 */
ret Gyro_SetCommunicateFreq(Gyro_initStruct *p_gyro, uint32_t freq);


/**
 * @brief get resolution in structure
 * 
 * @param gyro gyro initalize structure 
 * @return uint8_t resolution [bit]
 */
uint8_t Gyro_GetResolution(Gyro_initStruct gyro);

/**
 * @brief get capture frequency in structure
 * 
 * @param gyro gyro initalize structure
 * @return uint32_t resolution [Hz]
 */
uint32_t Gyro_GetCaptureFreq(Gyro_initStruct gyro);

/**
 * @brief get communication frequency in structure
 * 
 * @param gyro gyro initalize structure
 * @return uint32_t communication speed [Hz]
 */
uint32_t Gyro_GetCommunicateFreq(Gyro_initStruct gyro);


/**
 * @brief get number of gyro initalize information
 * 
 * @param num gyro number
 * @param gyro gyro initalize structure pointer
 * @return ret get information result
 *  @arg GYRO_OK get information success
 *  @arg GYRO_UNKNOWN_DATA gyro number is not exist
 */
ret Gyro_GetInitalizeInfo(uint8_t num, Gyro_initStruct **p_gyro);


/**
 * @brief get number of gyro data information
 * 
 * @param num gyro number
 * @param gyro gyro data structure pointer
 * @return ret get information result
 *  @arg GYRO_OK get information success
 *  @arg GYRO_UNKNOWN_DATA gyro number is not exist
 */
ret Gyro_GetDataInfo(uint8_t num, Gyro_dataStruct **p_gyro);


/**
 * @brief gyroscope update sensor data.
 * 
 * @param num gyro number
 * @param gyro gyro data structure pointer
 * @return ret get sensor data result
 *  @arg GYRO_OK 
 *  @arg GYRO_GET_DATA_FAIL 
 */
ret Gyro_Update(uint8_t num, Gyro_dataStruct *p_gyro);

/**
 * @brief get euler angle roll
 * 
 * @param gyro gyro data structure
 * @return double roll angle [range: 0' ~ 180', -1' ~ -179']
 */
double Gyro_GetRoll(Gyro_dataStruct gyro);

/**
 * @brief get euler angle pitch
 * 
 * @param gyro gyro data structure
 * @return double pitch angle [range: 0' ~ 180', -1' ~ -179']
 */
double Gyro_GetPitch(Gyro_dataStruct gyro);

/**
 * @brief get euler angle yaw
 * 
 * @param gyro gyro data structure
 * @return double yaw angle [range: 0' ~ 180', -1' ~ -179']
 */
double Gyro_GetYaw(Gyro_dataStruct gyro);

/**
 * @brief get X axis in structure
 * 
 * @param gyro gyro data structure
 * @return gyroType_t X axis data
 */
gyroType_t Gyro_Get_X(Gyro_dataStruct gyro);

/**
 * @brief get Y axis in structure
 * 
 * @param gyro gyro data structure
 * @return gyroType_t Y axis data
 */
gyroType_t Gyro_Get_Y(Gyro_dataStruct gyro);

/**
 * @brief get Z axis in structure
 * 
 * @param gyro gyro data structure
 * @return gyroType_t Z axis data
 */
gyroType_t Gyro_Get_Z(Gyro_dataStruct gyro);


/**
 * @brief terminate gyroscope
 * 
 */
void Gyro_Terminate(void);
#endif