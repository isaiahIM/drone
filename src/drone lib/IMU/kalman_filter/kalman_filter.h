#ifndef KALMAN_FILTER__H
#define KALMAN_FILTER__H

#include <math.h>
#include "common_def.h"
#include "drone_types.h"

#define KALMAN_OK 0X00
#define KALAMN_FAIL 0X01

/**
 * @brief kalman filter initalize structure
 * 
 */
typedef struct kalmanfiltet_initalizeStructure
{
    uint8_t num;///< kalman filter number
    struct kalmanfiltet_initalizeStructure *next;///< next node
} Kalman_initStruct;


/**
 * @brief kalman filter system initalize
 * 
 * @return ret initalize result
 *  @arg KALMAN_OK initalize success
 *  @arg KALAMN_FAIL initalize fail
 */
ret Kalman_Init(void);

/**
 * @brief add kalman filter
 * 
 * @param num kalman filter number
 * @param kalman kalman filter structure
 * @return ret kalman filter add result
 *  @arg KALMAN_OK add success
 *  @arg KALAMN_FAIL add fail
 */
ret Kalman_Add(uint8_t num, Kalman_initStruct kalman);

/**
 * @brief delete kalman filter
 * 
 * @param num kalman filter number
 * @return ret delete result
 *  @arg KALMAN_OK delete success
 *  @arg KALAMN_FAIL delete fail
 */
ret Kalman_Delete(uint8_t num);

/**
 * @brief get sensor fusing roll data using kalman filter
 * 
 * @param num kalman filter number
 * @param gy_roll gyro roll data
 * @param acc_roll accelerator roll data
 * @param comp_roll compass roll data
 * @return double sensor fusing roll data
 */
double Kalman_GetRoll(uint8_t num, double gy_roll, double acc_roll, double comp_roll);

/**
 * @brief get sensor fusing pitch data using kalman filter
 * 
 * @param num kalman filter number
 * @param gy_pitch gyro pitch data
 * @param acc_pitch accelerator pitch data
 * @param comp_pitch compass pitch data
 * @return double sensor fusing pitch data
 */
double Kalman_GetPitch(uint8_t num, double gy_pitch, double acc_pitch, double comp_pitch);

/**
 * @brief get sensor fusing yaw data using kalman filter
 * 
 * @param num kalman filter number
 * @param gy_yaw gyro yaw data
 * @param comp_yaw compass yaw data
 * @return double sensor fusing yaw data
 */
double Kalman_GetYaw(uint8_t num, double gy_yaw, double comp_yaw);

#endif