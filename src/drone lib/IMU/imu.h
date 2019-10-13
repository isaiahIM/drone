#ifndef IMU__H
#define IMU__H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "drone_types.h"
#include "gyro_lib.h"
#include "accel_lib.h"
#include "compass_lib.h"

typedef struct accelerator_YPL
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    struct accelerator_YPL *next;
} accel_YPLDataStruct;

typedef struct gyroscope_YPL
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    struct gyroscope_YPL *next;
} gyro_YPLDataStruct;

typedef struct compass_YPL
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    struct compass_YPL *next;
} compass_YPLDataStruct;

typedef struct accelerator_YPL
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    struct accelerator_YPL *next;
} accel_YPLData;

typedef struct drone_YPL
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    struct drone_YPL *next;
} drone_YPLData;

#endif