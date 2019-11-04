#ifndef TIME__DRIVER__H
#define TIME__DRIVER__H

#include <stdio.h>
#include "common_def.h"
#include "drone_types.h"

#define BSP_TIME_OK 0
#define BSP_TIME_FAIL 1

/**
 * @brief timer initalize
 * 
 * @return uint8_t initalize result
 *  @arg BSP_TIME_OK initalize success
 *  @arg BSP_TIME_FAIL initalize fail
 */
uint8_t BSP_Time_Initalize(void);

/**
 * @brief get runtime[second]
 * 
 * @return double runtime[second]
 */
double BSP_Time_GetRunTimeSeconds(void);

/**
 * @brief get runtime[millisecond]
 * 
 * @return double runtime[millisecond]
 */
double BSP_Time_GetRunTimeMillis(void);

#endif