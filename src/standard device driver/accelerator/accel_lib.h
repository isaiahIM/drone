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

#include "common_def.h"

#include "accel_driver.h"
#include "drone_types.h"


#define _USE_MATH_DEFINES
#include <math.h>

typedef int16_t accelType_t;

#define ACCEL_CONNECTED 0X00
#define ACCEL_DISCONNECTED 0X01

#define ACCEL_OK 0X00
#define ACCEL_SET_DATA_FAIL 0X01
#define ACCEL_GET_DATA_FAIL 0X01

#define ACCEL_ADD_FAIL 0X01
#define ACCEL_DELETE_FAIL 0X01

#define ACCEL_UNKNOWN_DATA 0x01

#define ACCEL_HW_INIT_FAIL 0x01
#define ACCEL_AP_INIT_FAIL 0x02

/*accel resolution define */
#define ACCEL_RESOLUTION_8BIT 0X01
#define ACCEL_RESOLUTION_16BIT 0X02
#define ACCEL_RESOLUTION_32BIT 0X03

/**
 * @brief Accelerator data structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Accel_DataStructure
{
    uint8_t num;///< accel number
    accelType_t accel_x;///< accel x
    accelType_t accel_y;///< accel y
    accelType_t accel_z;///< accel z
    double roll;///< roll
    double pitch;///< pitch
    struct Accel_DataStructure *next;///< next link
} Accel_dataStruct;

/**
 * @brief Accelerator initalize structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Accel_InitalizeStructure
{
    uint8_t num;///< accel number
    uint8_t resolution;///< accel resolution bit
    uint32_t capture_freq;///< accel data capture frequency[Hz]
    uint32_t communication_freq;///< accel communication frequency[Hz]
    struct Accel_InitalizeStructure *next;///< next link
} Accel_initStruct;



/*user functions*/

/**
 * @brief accelerator H/W, system initalize
 * 
 * @return ret initalize result
 *  @arg ACCEL_OK accel initalize success
 *  @arg ACCEL_HW_INIT_FAIL hardware initalize fail
 *  @arg ACCEL_AP_INIT_FAIL application initalize fail
 */
ret Accel_Init(void);

/**
 * @brief accelerator connect check
 * 
 * @param num accelerator number
 * @return uint8_t connect status
 *  @arg ACCEL_CONNECTED accelerator is connected
 *  @arg ACCEL_DISCONNECTED accelerator is disconnected
 */
uint8_t Accel_ConnectCheck(uint8_t num);


/**
 * @brief accelerator number setting
 * 
 * @param accel accel initalize structure pointer
 * @param num accel number
 * @return ret number setting result
 *  @arg ACCEL_OK number setting success
 *  @arg ACCEL_SET_DATA_FAIL number setting fail
 */
ret Accel_SetNum(Accel_initStruct *accel, uint8_t num);

/**
 * @brief accelerator resolution setting
 * 
 * @param accel accel initalize structure pointer
 * @param resolution_bit accel data resolution bit
 *  @arg ACCEL_RESOLUTION_8BIT accel data 8bit scale resolution
 *  @arg ACCEL_RESOLUTION_16BIT accel data 16bit scale resolution
 *  @arg ACCEL_RESOLUTION_32BIT accel data 32bit scale resolution
 * @return ret resolution setting result
 *  @arg ACCEL_OK resoluition setting success
 *  @arg ACCEL_SET_DATA_FAIL resolution setting fail
 */
ret Accel_SetResolution(Accel_initStruct *accel, uint8_t resolution_bit);

/**
 * @brief accelerator capture frequency set
 * 
 * @param accel accel initalize structure pointer
 * @param freq data capture frequency
 * @return ret frequency setting result
 *  @arg ACCEL_OK frequency setting success
 *  @arg ACCEL_SET_DATA_FAIL frequency setting fail
 */
ret Accel_SetCaptureFreq(Accel_initStruct *accel, uint32_t freq);

/**
 * @brief accelerator communicate frequency set
 * 
 * @param accel accel initalize structure pointer
 * @param freq communicate frequency [Hz]
 * @return ret frequency setting result
 *  @arg ACCEL_OK frequency setting success
 *  @arg ACCEL_SET_DATA_FAIL frequency setting fail
 */
ret Accel_SetCommunicateFreq(Accel_initStruct *accel, uint32_t freq);


/**
 * @brief get resolution in structure
 * 
 * @param accel accel initalize structure 
 * @return uint8_t resolution
 *  @arg ACCEL_RESOLUTION_8BIT resolution 8 bit
 *  @arg ACCEL_RESOLUTION_16BIT resolution 16 bit
 *  @arg ACCEL_RESOLUTION_32BITresolution 32 bit
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
 * @brief get get initalize number
 * 
 * @param accel accel initalize structure
 * @return uint8_t accel number
 */
uint8_t Accel_GetInitNum(Accel_initStruct accel);


/**
 * @brief add new accelerator
 * 
 * @param accel accel initalize structure
 * @return ret initalize result
 *  @arg ACCEL_OK accelerator add success
 *  @arg ACCEL_SET_DATA_FAIL accelerator add fail
 */
ret Accel_AddAccel(Accel_initStruct accel);

/**
 * @brief delete accel information
 * 
 * @param num accel number
 * @return ret delete result
 *  @arg ACCEL_OK delete success
 *  @arg ACCEL_DELETE_FAIL delete fail
 */
ret Accel_DeleteAccel(uint8_t num);


/**
 * @brief add accel initalize structure in list
 * 
 * @param accel initlaize structure
 * @return ret add result
 *  @arg ACCEL_OK add success
 *  @arg ACCEL_ADD_FAIL add fail
 */
ret Accel_AddInitalizeInfo(Accel_initStruct accel);

/**
 * @brief get number of accel initalize information
 * 
 * @param num accel number
 * @param accel accel initalize structure pointer
 * @return ret get information result
 *  @arg ACCEL_OK get information success
 *  @arg ACCEL_UNKNOWN_DATA accel number is not exist
 */
ret Accel_GetInitalizeInfo(uint8_t num, Accel_initStruct **accel);

/**
 * @brief delete initalize information in list
 * 
 * @param num delete number
 * @return ret delete result
 *  @arg ACCEL_OK delete success
 *  @arg ACCEL_DELETE_FAIL delete fail
 */
ret Accel_DeleteInitalizeInfo(uint8_t num);


/**
 * @brief add accel data structure in list
 * 
 * @param accel data structure
 * @return ret add result
 *  @arg ACCEL_OK add success
 *  @arg ACCEL_ADD_FAIL add fail
 */
ret Accel_AddDataInfo(Accel_dataStruct accel);

/**
 * @brief get number of accel data information
 * 
 * @param num accel number
 * @param accel accel data structure pointer
 * @return ret get information result
 *  @arg ACCEL_OK get information success
 *  @arg ACCEL_UNKNOWN_DATA accel number is not exist
 */
ret Accel_GetDataInfo(uint8_t num, Accel_dataStruct **accel);

/**
 * @brief delete data information in list
 * 
 * @param num delete number
 * @return ret delete result
 *  @arg ACCEL_OK delete success
 *  @arg ACCEL_DELETE_FAIL delete fail
 */
ret Accel_DeleteDataInfo(uint8_t num);

/**
 * @brief accelerator sensor data update.
 * 
 * @param num accel number
 * @param accel accel dat structure pointer
 * @return ret get sensor data result
 *  @arg ACCEL_OK 
 *  @arg ACCEL_GET_DATA_FAIL 
 */
ret Accel_UpdateData(uint8_t num, Accel_dataStruct *accel);

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
 * @brief get data number
 * 
 * @param accel accel data structure pointer
 * @return uint8_t accel data number
 */
uint8_t Accel_GetDataNum(Accel_dataStruct accel);

/**
 * @brief set data number
 * 
 * @param accel accel data structure pointer
 * @param num number
 * @return ret setting result
 *  @arg ACCEL_OK setting success
 */
ret Accel_SetDataNum(Accel_dataStruct *accel, uint8_t num);

/**
 * @brief accelerator count encrement 1
 * 
 */
void Accel_CountIncrement(void);

/**
 * @brief accelerator count decrement 1
 * 
 */
void Accel_CountDecrement(void);


/**
 * @brief reset current data position
 * 
 */
void Accel_ResetDataPos(void);

/**
 * @brief reset current initalize position
 * 
 */
void Accel_ResetInitPos(void);


#endif