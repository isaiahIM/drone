#ifndef IMU__H
#define IMU__H

#include <math.h>
#include "common_def.h"
#include "drone_types.h"
#include "gyro_lib.h"
#include "accel_lib.h"
#include "compass_lib.h"

#define IMU_SUCCESS 0
#define IMU_FAIL 1

/**
 * @brief accelerator euler angular structure structure
 * 
 */
typedef struct accelerator_EulerAngleStructure
{
    int16_t pitch;
    int16_t roll;
} accel_angleStruct;

/**
 * @brief gyroscope euler angular structure structure
 * 
 */
typedef struct gyroscope_EulerAngleStructure
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
} gyro_angleStruct;

/**
 * @brief compass euler angular structure structure
 * 
 */
typedef struct compass_EulerAngleStructure
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
} compass_angleStruct;

/**
 * @brief drone euler angular structure structure
 * 
 */
typedef struct drone_EulerAngleStructure
{
    uint8_t num;
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
} drone_angleStruct;

#endif