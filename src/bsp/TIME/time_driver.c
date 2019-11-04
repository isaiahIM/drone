#include "time_driver.h"

uint8_t BSP_Time_Initalize(void)
{
    printf("---------START BSP_Time_Initalize()---------\n");
    printf("----------END BSP_Time_Initalize()-----------\n");
    return BSP_TIME_OK;
}

double BSP_Time_GetRunTimeSeconds(void)
{
    printf("--------------START BSP_Time_GetRunTimeSeconds()------------ ");
    printf("--------------END BSP_Time_GetRunTimeSeconds()------------ ");
    return 0.002;
}

double BSP_Time_GetRunTimeMillis(void)
{
    printf("--------------START BSP_Time_GetRunTimeMillis()------------ ");
    printf("--------------END BSP_Time_GetRunTimeMillis()------------ ");
    return 2.0;
}