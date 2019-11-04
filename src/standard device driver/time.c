#include "time.h"

ret Time_Init(void)
{
    ret ret_val=TIME_SUCCESS;

    ret_val|=BSP_Time_Initalize();
    ret_val|=BSP_RTC_Initalize();

    if(ret_val!=TIME_SUCCESS)
    {
        ret_val=TIME_FAIL; 
    }

    return ret_val;
}

ret Time_SetCurDate(uint16_t years, uint8_t month, uint8_t date, uint8_t day)
{
    ret ret_val=TIME_SUCCESS;

    ret_val|=BSP_RTC_SetCurDate(years, month, date, day);
    
    if(ret_val!=TIME_SUCCESS)
    {
        ret_val=TIME_FAIL; 
    }

    return ret_val;
}

ret Time_GetCurDate(uint16_t *years, uint8_t *month, uint8_t *date, uint8_t *day)
{
    ret ret_val=TIME_SUCCESS;

    ret_val|=BSP_RTC_GetCurDate(years, month, date, day);

    if(ret_val!=TIME_SUCCESS)
    {
        ret_val=TIME_FAIL; 
    }

    return ret_val;
}

ret Time_SetCurTime(uint8_t hour, uint8_t min, uint8_t sec)
{
    ret ret_val=TIME_SUCCESS;
    
    ret_val|=BSP_RTC_SetCurTime(hour, min, sec);
    if(ret_val!=TIME_SUCCESS)
    {
        ret_val=TIME_FAIL;
    }

    return ret_val;
}

ret Time_GetCurTime(uint8_t *hour, uint8_t *min, uint8_t *sec)
{
    ret ret_val=TIME_SUCCESS;
    uint8_t get_hour, get_min, get_sec;

    ret_val|=BSP_RTC_GetCurTime(&get_hour, &get_min, &get_sec);
    if(ret_val!=TIME_SUCCESS)
    {
        ret_val=TIME_FAIL;
    }
    *hour=get_hour;
    *min=get_min;
    *sec=get_sec;

    return ret_val;
}

double Time_GetRunTimeSec(void)
{
    double time;
    time=BSP_Time_GetRunTimeSeconds();
    return time;
}

double Time_GetRunTimeMillis(void)
{
    double time;
    time=BSP_Time_GetRunTimeMillis();
    return time;
}