#include "rtc_driver.h"

static uint16_t _years=0;
static uint8_t _month=0, _date=0, _day=0;
static uint8_t _hour=0, _min=0, _sec=0;

uint8_t BSP_RTC_Initalize(void)
{
    uint8_t ret_val=BSP_RTC_OK;
    printf("-----------START BSP_RTC_Initalize()-------------\n");
    printf("-----------END BSP_RTC_Initalize()-------------\n");
    
    return ret_val;
}

uint8_t BSP_RTC_SetCurDate(uint16_t years, uint8_t month, uint8_t date, uint8_t day)
{
    uint8_t ret_val=BSP_RTC_OK;
    printf("-----------START BSP_RTC_SetCurrentDate()-------------\n");
    _years=years;
    _month=month;
    _date=date;
    _day=day;

    printf("years: %d, month: %d, date: %d, day: %d\n", _years, _month, _date, _day);
    printf("-----------END BSP_RTC_SetCurrentDate()-------------\n");
    
    return ret_val;
}

uint8_t BSP_RTC_GetCurDate(uint16_t *p_years, uint8_t *p_month, uint8_t *p_date, uint8_t *p_day)
{
    uint8_t ret_val=BSP_RTC_OK;
    printf("-----------START BSP_RTC_GetCurDate()-------------\n");
    *p_years=_years;
    *p_month=_month;
    *p_date=_date;
    *p_day=_day;
    printf("-----------END BSP_RTC_GetCurDate()-------------\n");
    
    return ret_val;
}

uint8_t BSP_RTC_SetCurTime(uint8_t hour, uint8_t min, uint8_t sec)
{
    uint8_t ret_val=BSP_RTC_OK;
    printf("-----------START BSP_RTC_SetCurTime()-------------\n");
    _hour=hour;
    _min=min;
    _sec=sec;
    printf("hour: %d, min: %d, sec: %d\n", _hour, _min, _sec);
    printf("-----------END BSP_RTC_SetCurTime()-------------\n");
    
    return ret_val;
}

uint8_t BSP_RTC_GetCurTime(uint8_t *p_hour, uint8_t *p_min, uint8_t *p_sec)
{
    uint8_t ret_val=BSP_RTC_OK;
    printf("-----------START BSP_RTC_GetCurTime()-------------\n");
    *p_hour=_hour;
    *p_min=_min;
    *p_sec=_sec;
    printf("-----------END BSP_RTC_GetCurTime()-------------\n");
    
    return ret_val;
}