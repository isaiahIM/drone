#ifndef RTC_DRIVER__H
#define RTC_DRIVER__H

#define BSP_RTC_OK 0
#define BSP_RTC_FAIL 1

#include <stdint.h>
#include <stdio.h>
#include "common_def.h"

/**
 * @brief RTC initalize
 * 
 * @return uint8_t initalize result
 *  @arg BSP_RTC_OK initalize success
 *  @arg BSP_RTC_FAIL initalize fail
 */
uint8_t BSP_RTC_Initalize(void);

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
 *  @arg SUN Sunday
 *  @arg MON Monday
 *  @arg TUE Tuesday
 *  @arg WED Wednesday
 *  @arg THU Thursday
 *  @arg FRI Friday
 *  @arg SAT Saturday
 * @param day day
 * @return uint8_t setting result
 *  @arg BSP_RTC_OK setting success
 *  @arg BSP_RTC_FAIL setting fail
 */
uint8_t BSP_RTC_SetCurDate(uint16_t years, uint8_t month, uint8_t date, uint8_t day);

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
 *  @arg SUN Sunday
 *  @arg MON Monday
 *  @arg TUE Tuesday
 *  @arg WED Wednesday
 *  @arg THU Thursday
 *  @arg FRI Friday
 *  @arg SAT Saturday
 * @param p_day day pointer
 * @return uint8_t date get result
 *  @arg BSP_RTC_OK date get success
 *  @arg BSP_RTC_FAIL date get fail
 */
uint8_t BSP_RTC_GetCurDate(uint16_t *p_years, uint8_t *p_month, uint8_t *p_date, uint8_t *p_day);

/**
 * @brief set current time
 * 
 * @param hour hour
 * @param min minute
 * @param sec seconds
 * @return uint8_t set time result
 *  @arg BSP_RTC_OK time set success
 *  @arg BSP_RTC_FAIL time set fail
 */
uint8_t BSP_RTC_SetCurTime(uint8_t hour, uint8_t min, uint8_t sec);

/**
 * @brief get current time
 * 
 * @param p_hour hour
 * @param p_min minute
 * @param p_sec seconds
 * @return uint8_t get time result
 *  @arg BSP_RTC_OK time get success
 *  @arg BSP_RTC_FAIL time get fail
 */
uint8_t BSP_RTC_GetCurTime(uint8_t *p_hour, uint8_t *p_min, uint8_t *p_sec);

#endif