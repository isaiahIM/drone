/**
 * @file compass_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief compass HAL Library header file
 * @version 0.2.1
 * @date 2019-11-30
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#ifndef COMPASS_LIB__H
#define COMPASS_LIB__H

#define _USE_MATH_DEFINES
#include <math.h>

#include "common_def.h"
#include "compass_driver.h"
#include "drone_types.h"
#include "time.h"


typedef int32_t compassType_t;

#define COMPASS_CONNECTED 0X00
#define COMPASS_DISCONNECTED 0X01

#define COMPASS_OK 0X00
#define COMPASS_SET_DATA_FAIL 0X01
#define COMPASS_GET_DATA_FAIL 0X01


#define COMPASS_UNKNOWN_DATA 0x01

#define COMPASS_HW_INIT_FAIL 0x01
#define COMPASS_MEMALLOC_FAIL 0x02

/**
 * @brief Compass data structure.
 * 
 */
typedef struct Compass_DataStructure
{
    compassType_t compass_x;///< compass x
    compassType_t compass_y;///< compass y
    compassType_t compass_z;///< compass z
    double yaw;///< yaw
    double pitch;///< pitch
    double roll;///< roll
} Compass_dataStruct;

/**
 * @brief Compass initalize structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Compass_InitalizeStructure
{
    uint8_t resolution;///< compass resolution bit
    uint32_t capture_freq;///< compass data capture frequency[Hz]
    uint32_t communication_freq;///< compass communication frequency[Hz]
} Compass_initStruct;

/**
 * @brief compass information structure.
 * 
 */
typedef struct Compass_information_structure
{
    uint8_t count;///< compass count
    Compass_dataStruct *data_arr;///< compass data information array
    Compass_initStruct *init_arr;///< compass initalize information array
} Compass_infoStruct;


/**
 * @brief compass H/W, system initalize
 * 
 * @param count compass count
 * @return ret initalize result
 *  @arg COMPASS_OK compass initalize success
 *  @arg COMPASS_HW_INIT_FAIL hardware initalize fail
 *  @arg COMPASS_MEMALLOC_FAIL memory initalize fail
 */
ret Compass_Init(uint8_t count);

/**
 * @brief compass connect check
 * 
 * @param num compass number
 * @return uint8_t connect status
 *  @arg COMPASS_CONNECTED compass is connected
 *  @arg COMPASS_DISCONNECTED compass is disconnected
 */
uint8_t Compass_ChkConnect(uint8_t num);


/**
 * @brief compass resolution setting
 * 
 * @param p_compass compass initalize structure pointer
 * @param resolution_bit compass data resolution bit [bit]
 * @return ret resolution setting result
 *  @arg COMPASS_OK resoluition setting success
 *  @arg COMPASS_SET_DATA_FAIL resolution setting fail
 */
ret Compass_SetResolution(Compass_initStruct *p_compass, uint8_t resolution_bit);

/**
 * @brief compass capture frequency set
 * 
 * @param p_compass compass initalize structure pointer
 * @param freq data capture frequency
 * @return ret frequency setting result
 *  @arg COMPASS_OK frequency setting success
 *  @arg COMPASS_SET_DATA_FAIL frequency setting fail
 */
ret Compass_SetCaptureFreq(Compass_initStruct *p_compass, uint32_t freq);

/**
 * @brief compass communicate frequency set
 * 
 * @param p_compass compass initalize structure pointer
 * @param freq communicate frequency [Hz]
 * @return ret frequency setting result
 *  @arg COMPASS_OK frequency setting success
 *  @arg COMPASS_SET_DATA_FAIL frequency setting fail
 */
ret Compass_SetCommunicateFreq(Compass_initStruct *p_compass, uint32_t freq);


/**
 * @brief get resolution in structure
 * 
 * @param compass compass initalize structure 
 * @return uint8_t resolution [bit]
 */
uint8_t Compass_GetResolution(Compass_initStruct compass);

/**
 * @brief get capture frequency in structure
 * 
 * @param compass compass initalize structure
 * @return uint32_t resolution[Hz]
 */
uint32_t Compass_GetCaptureFreq(Compass_initStruct compass);

/**
 * @brief get communication frequency in structure
 * 
 * @param compass compass initalize structure
 * @return uint32_t communication speed[Hz]
 */
uint32_t Compass_GetCommunicateFreq(Compass_initStruct compass);


/**
 * @brief get number of compass initalize information
 * 
 * @param num compass number
 * @param p_compass compass initalize structure pointer
 * @return ret get information result
 *  @arg COMPASS_OK get information success
 *  @arg COMPASS_UNKNOWN_DATA compass number is not exist
 */
ret Compass_GetInitalizeInfo(uint8_t num, Compass_initStruct **p_compass);


/**
 * @brief get number of compass data information
 * 
 * @param num compass number
 * @param p_compass compass data structure pointer
 * @return ret get information result
 *  @arg COMPASS_OK get information success
 *  @arg COMPASS_UNKNOWN_DATA compass number is not exist
 */
ret Compass_GetDataInfo(uint8_t num, Compass_dataStruct **p_compass);


/**
 * @brief compass update sensor data.
 * 
 * @param num compass number
 * @param p_compass compass dat structure pointer
 * @return ret get sensor data result
 *  @arg COMPASS_OK 
 *  @arg COMPASS_GET_DATA_FAIL 
 */
ret Compass_UpdateData(uint8_t num, Compass_dataStruct *p_compass);


/**
 * @brief get euler angle roll
 * 
 * @param compass compass data structure
 * @return double roll angle [range: 0' ~ 180', -1' ~ -179']
 */
double Compass_GetRoll(Compass_dataStruct compass);

/**
 * @brief get euler angle pitch
 * 
 * @param compass compass data structure
 * @return double pitch angle [range: 0' ~ 180', -1' ~ -179']
 */
double Compass_GetPitch(Compass_dataStruct compass);

/**
 * @brief get euler angle yaw
 * 
 * @param compass compass data structure
 * @return double yaw angle [range: 0' ~ 180', -1' ~ -179']
 */
double Compass_GetYaw(Compass_dataStruct compass);


/**
 * @brief get X axis in structure
 * 
 * @param compass compass data structure
 * @return compassType_t X axis data
 */
compassType_t Compass_Get_X(Compass_dataStruct compass);

/**
 * @brief get Y axis in structure
 * 
 * @param compass compass data structure
 * @return compassType_t Y axis data
 */
compassType_t Compass_Get_Y(Compass_dataStruct compass);

/**
 * @brief get Z axis in structure
 * 
 * @param compass compass data structure
 * @return compassType_t Z axis data
 */
compassType_t Compass_Get_Z(Compass_dataStruct compass);

/**
 * @brief terminate compass
 * 
 */
void Compass_Terminate(void);

#endif