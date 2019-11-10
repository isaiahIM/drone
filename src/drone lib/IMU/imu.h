#ifndef IMU__H
#define IMU__H

#include <math.h>

#include "common_def.h"
#include "drone_types.h"
#include "gyro_lib.h"
#include "accel_lib.h"
#include "compass_lib.h"
#include "kalman_filter.h"

#define IMU_SUCCESS 0
#define IMU_FAIL 1
#define IMU_CONNECTED 0
#define IMU_DISCONNECTED 1

/**
 * @brief IMU data structure
 *  This structure included yaw/pitch/roll data, yaw/pitch/roll, zero position, increment/decrement scales of yaw/pitch/roll
 */
typedef struct IMU_DataStructure
{
    uint8_t num;///< imu number

    double yaw;///< yaw
    double pitch;///< pitch
    double roll;///< roll

    double yaw_zero;///< yaw zero position
    double pitch_zero;///< pitch zero position
    double roll_zero;///< roll zero position

    double yaw_inc_scale;///< yaw increment scale
    double yaw_dec_scale;///< yaw decrement scale
    double pitch_inc_scale;///< pitch increment scale
    double ptich_dec_scale;///< pitch decrement scale
    double roll_inc_scale;///< roll increment scalec
    double roll_dec_scale;///< roll decrement scale
} IMU_dataStruct;


/**
 * @brief IMU initalize
 * 
 * @param imu_count imu count
 * @return ret initalize result
 *  @arg IMU_SUCCESS initalize success
 *  @arg IMU_FAIL initalize fail
 */
ret IMU_Init(uint8_t imu_count);

/**
 * @brief IMU connect check
 * 
 * @param num IMU number
 * @return ret connect status
 *  @arg IMU_CONNECTED IMU connect
 *  @arg IMU_DISCONNECTED IMU disconnect
 */
ret IMU_ChkConnect(uint8_t num);

/**
 * @brief update IMU data
 * 
 * @return ret update result
 *  @arg IMU_SUCCESS update success
 *  @arg IMU_FAIL update fail
 */
ret IMU_UpdateData(uint8_t num);

/**
 * @brief IMU roll calibrate
 * 
 * @param num IMU number
 * @param roll_zero roll zero position
 * @param roll_pos90 roll 90' position
 * @param roll_neg90 roll -90' position
 * @return ret calibrate result
 *  @arg IMU_SUCCESS calibrate success
 *  @arg IMU_FAIL calibrate fail
 */
ret IMU_CalibrateRoll(uint8_t num, double roll_zero, double roll_pos90, double roll_neg90);

/**
 * @brief IMU pitch calibrate
 * 
 * @param num IMU number
 * @param pitch_zero pitch zero position
 * @param pitch_pos90 pitch 90' position
 * @param pitch_neg90 pitch -90' position
 * @return ret calibrate result
 *  @arg IMU_SUCCESS calibrate success
 *  @arg IMU_FAIL calibrate fail
 */
ret IMU_CalibratePitch(uint8_t num, double pitch_zero, double pitch_pos90, double pitch_neg90);

/**
 * @brief IMU yaw calibrate
 * 
 * @param num IMU number
 * @param yaw_zero yaw zero position
 * @param yaw_pos90 yaw 90' position
 * @param yaw_neg90 yaw -90' position
 * @return ret calibrate result
 *  @arg IMU_SUCCESS calibrate success
 *  @arg IMU_FAIL calibrate fail
 */
ret IMU_CalibrateYaw(uint8_t num, double yaw_zero, double yaw_pos90, double yaw_neg90);

/**
 * @brief get roll in IMU
 * 
 * @param num IMU number
 * @return double roll [range: -90' - +90']
 */
double IMU_GetRoll(uint8_t num);

/**
 * @brief get pitch in IMU
 * 
 * @param num IMU number
 * @return double pitch [range: -90' - +90']
 */
double IMU_GetPitch(uint8_t num);

/**
 * @brief get yaw in IMU
 * 
 * @param num IMU number
 * @return double yaw [range: -90' - +90']
 */
double IMU_GetYaw(uint8_t num);


#endif