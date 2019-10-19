/**
 * @file compass_lib.h
 * @author isaiah IM || isaiahim0214@gmail.com
 * @brief compass HAL Library header file
 * @version 0.1
 * @date 2019-09-22
 * 
 * @copyright Copyright (c) 2019 isaiah IM
 * 
 */
#ifndef COMPASS_LIB__H
#define COMPASS_LIB__H


#include "common_def.h"
#include "compass_driver.h"
#include "drone_types.h"

typedef int16_t compassType_t;

#define COMPASS_CONNECTED 0X00
#define COMPASS_DISCONNECTED 0X01

#define COMPASS_OK 0X00
#define COMPASS_SET_DATA_FAIL 0X01
#define COMPASS_GET_DATA_FAIL 0X01

#define COMPASS_ADD_FAIL 0X01
#define COMPASS_DELETE_FAIL 0X01

#define COMPASS_UNKNOWN_DATA 0x01

#define COMPASS_HW_INIT_FAIL 0x01
#define COMPASS_AP_INIT_FAIL 0x02

/*compass resolution define */
#define COMPASS_RESOLUTION_8BIT 0X01
#define COMPASS_RESOLUTION_16BIT 0X02
#define COMPASS_RESOLUTION_32BIT 0X03

/**
 * @brief Compass data structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Compass_DataStructure
{
    uint8_t num;///< compass number
    compassType_t compass_x;///< compass x
    compassType_t compass_y;///< compass y
    compassType_t compass_z;///< compass z
    struct Compass_DataStructure *next;///< next link
} Compass_dataStruct;

/**
 * @brief Compass initalize structure.
 * @detail This structure can working linked list
 * 
 */
typedef struct Compass_InitalizeStructure
{
    uint8_t num;///< compass number
    uint8_t resolution;///< compass resolution bit
    uint32_t capture_freq;///< compass data capture frequency[Hz]
    uint32_t communication_freq;///< compass communication frequency[Hz]
    struct Compass_InitalizeStructure *next;///< next link
} Compass_initStruct;



/*user functions*/

/**
 * @brief compass H/W, system initalize
 * 
 * @return ret initalize result
 *  @arg COMPASS_OK compass initalize success
 *  @arg COMPASS_HW_INIT_FAIL hardware initalize fail
 *  @arg COMPASS_AP_INIT_FAIL application initalize fail
 */
ret Compass_Init(void);

/**
 * @brief compass connect check
 * 
 * @param num compass number
 * @return uint8_t connect status
 *  @arg COMPASS_CONNECTED compass is connected
 *  @arg COMPASS_DISCONNECTED compass is disconnected
 */
uint8_t Compass_ConnectCheck(uint8_t num);


/**
 * @brief compass number setting
 * 
 * @param compass compass initalize structure pointer
 * @param num compass number
 * @return ret number setting result
 *  @arg COMPASS_OK number setting success
 *  @arg COMPASS_SET_DATA_FAIL number setting fail
 */
ret Compass_SetNum(Compass_initStruct *compass, uint8_t num);

/**
 * @brief compass resolution setting
 * 
 * @param compass compass initalize structure pointer
 * @param resolution_bit compass data resolution bit
 *  @arg COMPASS_RESOLUTION_8BIT compass data 8bit scale resolution
 *  @arg COMPASS_RESOLUTION_16BIT compass data 16bit scale resolution
 *  @arg COMPASS_RESOLUTION_32BIT compass data 32bit scale resolution
 * @return ret resolution setting result
 *  @arg COMPASS_OK resoluition setting success
 *  @arg COMPASS_SET_DATA_FAIL resolution setting fail
 */
ret Compass_SetResolution(Compass_initStruct *compass, uint8_t resolution_bit);

/**
 * @brief compass capture frequency set
 * 
 * @param compass compass initalize structure pointer
 * @param freq data capture frequency
 * @return ret frequency setting result
 *  @arg COMPASS_OK frequency setting success
 *  @arg COMPASS_SET_DATA_FAIL frequency setting fail
 */
ret Compass_SetCaptureFreq(Compass_initStruct *compass, uint32_t freq);

/**
 * @brief compass communicate frequency set
 * 
 * @param compass compass initalize structure pointer
 * @param freq communicate frequency [Hz]
 * @return ret frequency setting result
 *  @arg COMPASS_OK frequency setting success
 *  @arg COMPASS_SET_DATA_FAIL frequency setting fail
 */
ret Compass_SetCommunicateFreq(Compass_initStruct *compass, uint32_t freq);


/**
 * @brief get resolution in structure
 * 
 * @param compass compass initalize structure 
 * @return uint8_t resolution
 *  @arg COMPASS_RESOLUTION_8BIT resolution 8 bit
 *  @arg COMPASS_RESOLUTION_16BIT resolution 16 bit
 *  @arg COMPASS_RESOLUTION_32BITresolution 32 bit
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
 * @brief get get initalize number
 * 
 * @param compass compass initalize structure
 * @return uint8_t compass number
 */
uint8_t Compass_GetInitNum(Compass_initStruct compass);


/**
 * @brief add new compass
 * 
 * @param compass compass initalize structure
 * @return ret initalize result
 *  @arg COMPASS_OK compass add success
 *  @arg COMPASS_SET_DATA_FAIL compass add fail
 */
ret Compass_AddCompass(Compass_initStruct compass);

/**
 * @brief delete compass information
 * 
 * @param num compass number
 * @return ret delete result
 *  @arg COMPASS_OK delete success
 *  @arg COMPASS_DELETE_FAIL delete fail
 */
ret Compass_DeleteCompass(uint8_t num);


/**
 * @brief add compass initalize structure in list
 * 
 * @param compass initlaize structure
 * @return ret add result
 *  @arg COMPASS_OK add success
 *  @arg COMPASS_ADD_FAIL add fail
 */
ret Compass_AddInitalizeInfo(Compass_initStruct compass);

/**
 * @brief get number of compass initalize information
 * 
 * @param num compass number
 * @param compass compass initalize structure pointer
 * @return ret get information result
 *  @arg COMPASS_OK get information success
 *  @arg COMPASS_UNKNOWN_DATA compass number is not exist
 */
ret Compass_GetInitalizeInfo(uint8_t num, Compass_initStruct **compass);

/**
 * @brief delete initalize information in list
 * 
 * @param num delete number
 * @return ret delete result
 *  @arg COMPASS_OK delete success
 *  @arg COMPASS_DELETE_FAIL delete fail
 */
ret Compass_DeleteInitalizeInfo(uint8_t num);


/**
 * @brief add compass data structure in list
 * 
 * @param compass data structure
 * @return ret add result
 *  @arg COMPASS_OK add success
 *  @arg COMPASS_ADD_FAIL add fail
 */
ret Compass_AddDataInfo(Compass_dataStruct compass);

/**
 * @brief get number of compass data information
 * 
 * @param num compass number
 * @param compass compass data structure pointer
 * @return ret get information result
 *  @arg COMPASS_OK get information success
 *  @arg COMPASS_UNKNOWN_DATA compass number is not exist
 */
ret Compass_GetDataInfo(uint8_t num, Compass_dataStruct **compass);

/**
 * @brief delete data information in list
 * 
 * @param num delete number
 * @return ret delete result
 *  @arg COMPASS_OK delete success
 *  @arg COMPASS_DELETE_FAIL delete fail
 */
ret Compass_DeleteDataInfo(uint8_t num);

/**
 * @brief compass sensor data read.
 * 
 * @param num compass number
 * @param compass compass dat structure pointer
 * @return ret get sensor data result
 *  @arg COMPASS_OK 
 *  @arg COMPASS_GET_DATA_FAIL 
 */
ret Compass_GetCompassData(uint8_t num, Compass_dataStruct *compass);

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
 * @brief get data number
 * 
 * @param compass compass data structure pointer
 * @return uint8_t compass data number
 */
uint8_t Compass_GetDataNum(Compass_dataStruct compass);

/**
 * @brief set data number
 * 
 * @param compass compass data structure pointer
 * @param num number
 * @return ret setting result
 *  @arg COMPASS_OK setting success
 */
ret Compass_SetDataNum(Compass_dataStruct *compass, uint8_t num);

/**
 * @brief compass count encrement 1
 * 
 */
void Compass_CountIncrement(void);

/**
 * @brief compass count decrement 1
 * 
 */
void Compass_CountDecrement(void);


/**
 * @brief reset current data position
 * 
 */
void Compass_ResetDataPos(void);

/**
 * @brief reset current initalize position
 * 
 */
void Compass_ResetInitPos(void);


#endif