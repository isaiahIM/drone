#ifndef TIME__H
#define TIME__H

#include "drone_types.h"
#include "common_def.h"
#include "time_driver.h"
#include "rtc_driver.h"

#define TIME_SUCCESS 0x00
#define TIME_FAIL 0X01


typedef struct time_structure
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t date;
    uint16_t years;
} timeStruct;

/**
 * @brief time initalize
 * 
 * @return ret initalize result
 *  @arg TIME_SUCCESS time initalize success
 *  @arg TIME_FAIL time initalize fail
 */
ret Time_Init(void);

/**
 * @brief set current date
 * 
 * @param years years
 * @param month month
 *  @arg JAN January
 *  @arg FEB February
 *  @arg MAR March
 *  @arg APR April
 *  @arg MAY May
 *  @arg JUN June
 *  @arg JLY July
 *  @arg AUG August
 *  @arg SEP September
 *  @arg OCT October
 *  @arg NOV November
 *  @arg DEC December
 * @param date date
 * @param day day
 *  @arg SUN sunday
 *  @arg MON monday
 *  @arg TUE tuesday
 *  @arg WED wednesday
 *  @arg THU thursday
 *  @arg FRI friday
 *  @arg SAT saturday
 * @return ret date setting result
 *  @arg TIME_SUCCESS date setting success
 *  @arg TIME_FAIL date setting fail
 */
ret Time_SetCurDate(uint16_t years, uint8_t month, uint8_t date, uint8_t day);

/**
 * @brief get current date
 * 
 * @param p_years years pointer
 * @param p_month month pointer
 *  @arg JAN January
 *  @arg FEB February
 *  @arg MAR March
 *  @arg APR April
 *  @arg MAY May
 *  @arg JUN June
 *  @arg JLY July
 *  @arg AUG August
 *  @arg SEP September
 *  @arg OCT October
 *  @arg NOV November
 *  @arg DEC December
 * @param p_date date pointer
 * @param p_day day pointer
 *  @arg SUN sunday
 *  @arg MON monday
 *  @arg TUE tuesday
 *  @arg WED wednesday
 *  @arg THU thursday
 *  @arg FRI friday
 *  @arg SAT saturday
 * @return ret get date result
 *  @arg TIME_SUCCESS get date success
 *  @arg TIME_FAIL get date fail
 */
ret Time_GetCurDate(uint16_t *p_years, uint8_t *p_month, uint8_t *p_date, uint8_t *p_day);

/**
 * @brief set current time 
 * 
 * @param hour hour
 * @param min minute
 * @param sec seconds
 * @return ret current time set result
 *  @arg TIME_SUCCESS time set success
 *  @arg TIME_FAIL time set fail
 */
ret Time_SetCurTime(uint8_t hour, uint8_t min, uint8_t sec);

/**
 * @brief get current time
 * 
 * @param p_hour hour
 * @param p_min minute
 * @param p_sec seconds
 * @return ret current time get result
 *  @arg TIME_SUCCESS time get success
 *  @arg TIME_FAIL time get fail
 */
ret Time_GetCurTime(uint8_t *p_hour, uint8_t *p_min, uint8_t *p_sec);


/**
 * @brief get runtime[seconds]
 * 
 * @return double runtime[seconds]
 */
double Time_GetRunTimeSec(void);

/**
 * @brief get runtime[milliseconds]
 * 
 * @return double runtime[milliseconds]
 */
double Time_GetRunTimeMillis(void);

#endif