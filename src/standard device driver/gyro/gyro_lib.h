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

#define GYRO_ADD_FAIL 0X01
#define GYRO_DELETE_FAIL 0X01

#define GYRO_UNKNOWN_DATA 0x01

#define GYRO_HW_INIT_FAIL 0x01
#define GYRO_AP_INIT_FAIL 0x02

/*gyro resolution define */
#define GYRO_RESOLUTION_8BIT 0X01
#define GYRO_RESOLUTION_16BIT 0X02
#define GYRO_RESOLUTION_32BIT 0X03

/**
 * @brief Gyroscope data structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Gyro_DataStructure
{
    uint8_t num;///< gyro number
    gyroType_t gyro_x;///< Angular velocity x [degree/S]
    gyroType_t gyro_y;///< Angular velocity y [degree/S]
    gyroType_t gyro_z;///< Angular velocity z [degree/S]
    double yaw;///< yaw
    double pitch;///< pitch
    double roll;///< roll
    double cap_sec;///< data capture time[second]
    struct Gyro_DataStructure *next;///< next link
} Gyro_dataStruct;

/**
 * @brief Gyroscope initalize structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Gyro_InitalizeStructure
{
    uint8_t num;///< gyro number
    uint8_t resolution;///< gyro resolution bit
    uint32_t capture_freq;///< gyro data capture frequency[Hz]
    uint32_t communication_freq;///< gyro communication frequency[Hz]
    struct Gyro_InitalizeStructure *next;///< next link
} Gyro_initStruct;



/*user functions*/

/**
 * @brief gyroscope H/W, system initalize
 * 
 * @return ret initalize result
 *  @arg GYRO_OK gyro initalize success
 *  @arg GYRO_HW_INIT_FAIL hardware initalize fail
 *  @arg GYRO_AP_INIT_FAIL application initalize fail
 */
ret Gyro_Init(void);

/**
 * @brief gyroscope connect check
 * 
 * @param num gyroscope number
 * @return uint8_t connect status
 *  @arg GYRO_CONNECTED gyroscope is connected
 *  @arg GYRO_DISCONNECTED gyroscope is disconnected
 */
uint8_t Gyro_ConnectCheck(uint8_t num);


/**
 * @brief gyroscope number setting
 * 
 * @param gyro gyro initalize structure pointer
 * @param num gyro number
 * @return ret number setting result
 *  @arg GYRO_OK number setting success
 *  @arg GYRO_SET_DATA_FAIL number setting fail
 */
ret Gyro_SetNum(Gyro_initStruct *gyro, uint8_t num);

/**
 * @brief gyroscope resolution setting
 * 
 * @param gyro gyro initalize structure pointer
 * @param resolution_bit gyro data resolution bit
 *  @arg GYRO_RESOLUTION_8BIT gyro data 8bit scale resolution
 *  @arg GYRO_RESOLUTION_16BIT gyro data 16bit scale resolution
 *  @arg GYRO_RESOLUTION_32BIT gyro data 32bit scale resolution
 * @return ret resolution setting result
 *  @arg GYRO_OK resoluition setting success
 *  @arg GYRO_SET_DATA_FAIL resolution setting fail
 */
ret Gyro_SetResolution(Gyro_initStruct *gyro, uint8_t resolution_bit);

/**
 * @brief gyroscope capture frequency set
 * 
 * @param gyro gyro initalize structure pointer
 * @param freq data capture frequency
 * @return ret frequency setting result
 *  @arg GYRO_OK frequency setting success
 *  @arg GYRO_SET_DATA_FAIL frequency setting fail
 */
ret Gyro_SetCaptureFreq(Gyro_initStruct *gyro, uint32_t freq);

/**
 * @brief gyroscope communicate frequency set
 * 
 * @param gyro gyro initalize structure pointer
 * @param freq communicate frequency [Hz]
 * @return ret frequency setting result
 *  @arg GYRO_OK frequency setting success
 *  @arg GYRO_SET_DATA_FAIL frequency setting fail
 */
ret Gyro_SetCommunicateFreq(Gyro_initStruct *gyro, uint32_t freq);


/**
 * @brief get resolution in structure
 * 
 * @param gyro gyro initalize structure 
 * @return uint8_t resolution
 *  @arg GYRO_RESOLUTION_8BIT resolution 8 bit
 *  @arg GYRO_RESOLUTION_16BIT resolution 16 bit
 *  @arg GYRO_RESOLUTION_32BITresolution 32 bit
 */
uint8_t Gyro_GetResolution(Gyro_initStruct gyro);

/**
 * @brief get capture frequency in structure
 * 
 * @param gyro gyro initalize structure
 * @return uint32_t resolution[Hz]
 */
uint32_t Gyro_GetCaptureFreq(Gyro_initStruct gyro);

/**
 * @brief get communication frequency in structure
 * 
 * @param gyro gyro initalize structure
 * @return uint32_t communication speed[Hz]
 */
uint32_t Gyro_GetCommunicateFreq(Gyro_initStruct gyro);

/**
 * @brief get get initalize number
 * 
 * @param gyro gyro initalize structure
 * @return uint8_t gyro number
 */
uint8_t Gyro_GetInitNum(Gyro_initStruct gyro);


/**
 * @brief add new gyroscope
 * 
 * @param gyro gyro initalize structure
 * @return ret initalize result
 *  @arg GYRO_OK gyroscope add success
 *  @arg GYRO_SET_DATA_FAIL gyroscope add fail
 */
ret Gyro_AddGyro(Gyro_initStruct gyro);

/**
 * @brief delete gyro information
 * 
 * @param num gyro number
 * @return ret delete result
 *  @arg GYRO_OK delete success
 *  @arg GYRO_DELETE_FAIL delete fail
 */
ret Gyro_DeleteGyro(uint8_t num);


/**
 * @brief add gyro initalize structure in list
 * 
 * @param gyro initlaize structure
 * @return ret add result
 *  @arg GYRO_OK add success
 *  @arg GYRO_ADD_FAIL add fail
 */
ret Gyro_AddInitalizeInfo(Gyro_initStruct gyro);

/**
 * @brief get number of gyro initalize information
 * 
 * @param num gyro number
 * @param gyro gyro initalize structure pointer
 * @return ret get information result
 *  @arg GYRO_OK get information success
 *  @arg GYRO_UNKNOWN_DATA gyro number is not exist
 */
ret Gyro_GetInitalizeInfo(uint8_t num, Gyro_initStruct **gyro);

/**
 * @brief delete initalize information in list
 * 
 * @param num delete number
 * @return ret delete result
 *  @arg GYRO_OK delete success
 *  @arg GYRO_DELETE_FAIL delete fail
 */
ret Gyro_DeleteInitalizeInfo(uint8_t num);


/**
 * @brief add gyro data structure in list
 * 
 * @param gyro data structure
 * @return ret add result
 *  @arg GYRO_OK add success
 *  @arg GYRO_ADD_FAIL add fail
 */
ret Gyro_AddDataInfo(Gyro_dataStruct gyro);

/**
 * @brief get number of gyro data information
 * 
 * @param num gyro number
 * @param gyro gyro data structure pointer
 * @return ret get information result
 *  @arg GYRO_OK get information success
 *  @arg GYRO_UNKNOWN_DATA gyro number is not exist
 */
ret Gyro_GetDataInfo(uint8_t num, Gyro_dataStruct **gyro);

/**
 * @brief delete data information in list
 * 
 * @param num delete number
 * @return ret delete result
 *  @arg GYRO_OK delete success
 *  @arg GYRO_DELETE_FAIL delete fail
 */
ret Gyro_DeleteDataInfo(uint8_t num);

/**
 * @brief gyroscope update sensor data.
 * 
 * @param num gyro number
 * @param gyro gyro data structure pointer
 * @return ret get sensor data result
 *  @arg GYRO_OK 
 *  @arg GYRO_GET_DATA_FAIL 
 */
ret Gyro_UpdateData(uint8_t num, Gyro_dataStruct *gyro);

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
 * @brief get data number
 * 
 * @param gyro gyro data structure pointer
 * @return uint8_t gyro data number
 */
uint8_t Gyro_GetDataNum(Gyro_dataStruct gyro);

/**
 * @brief set data number
 * 
 * @param gyro gyro data structure pointer
 * @param num number
 * @return ret setting result
 *  @arg GYRO_OK setting success
 */
ret Gyro_SetDataNum(Gyro_dataStruct *gyro, uint8_t num);

/**
 * @brief gyroscope count encrement 1
 * 
 */
void Gyro_CountIncrement(void);

/**
 * @brief gyroscope count decrement 1
 * 
 */
void Gyro_CountDecrement(void);


/**
 * @brief reset current data position
 * 
 */
void Gyro_ResetDataPos(void);

/**
 * @brief reset current initalize position
 * 
 */
void Gyro_ResetInitPos(void);


#endif