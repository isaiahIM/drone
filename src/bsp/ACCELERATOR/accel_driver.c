#include "accel_driver.h"


uint8_t BSP_Accel_HW_Initalize(void)
{
    printf("----------------START BSP_Accel_HW_Initalize()--------------------------\n");
    printf("----------------END BSP_Accel_HW_Initalize--------------------------\n\n");
    
    return BSP_ACCEL_OK;
}

uint8_t BSP_Accel_ChkConnect(uint8_t num)
{
    printf("------------------START BSP_Accel_ChkConnect()---------------\n ");
    printf("num: %d\n", num);
    printf("------------------END BSP_Accel_ChkConnect()---------------\n ");
    
    return BSP_ACCEL_CONNECTED;
}

uint8_t BSP_Accel_SetReolution(uint8_t num, uint8_t resolution)
{
    printf("------------------START BSP_Accel_SetReolution()---------------\n ");
    printf("num: %d, resolution: %d\n", num, resolution);
    printf("------------------END BSP_Accel_SetReolution()---------------\n ");
    
    return BSP_ACCEL_OK;
}

uint8_t BSP_Accel_SetCaptureFreq(uint8_t num, uint32_t freq)
{
    printf("------------------START BSP_Accel_SetCaptureFreq()---------------\n ");
    printf("num: %d, frequency: %d\n", num, freq);
    printf("------------------END BSP_Accel_SetCaptureFreq()---------------\n ");
    
    return BSP_ACCEL_OK;
}
uint8_t BSP_Accel_SetCommunicateFreq(uint8_t num, uint32_t freq)
{
    printf("------------------START BSP_Accel_SetCommunicateFreq()---------------\n ");
    printf("num: %d, frequency: %d\n", num, freq);
    printf("------------------END BSP_Accel_SetCommunicateFreq()---------------\n ");
    
    return BSP_ACCEL_OK;
}

uint8_t BSP_Accel_GetX(uint8_t num, uint32_t *x)
{
    printf("------------------START BSP_Accel_GetX()---------------\n ");
    *x=123;
    printf("num: %d, x: %d\n", num, *x);
    printf("------------------END BSP_Accel_GetX()---------------\n ");
    
    return BSP_ACCEL_OK;
}

uint8_t BSP_Accel_GetY(uint8_t num, uint32_t *y)
{
    printf("------------------START BSP_Accel_GetY()---------------\n ");
    *y=510;
    printf("num: %d, y: %d\n", num, *y);
    printf("------------------END BSP_Accel_GetY()---------------\n ");

    return BSP_ACCEL_OK;
}

uint8_t BSP_Accel_GetZ(uint8_t num, uint32_t *z)
{
    printf("------------------START BSP_Accel_GetZ()---------------\n ");
    *z=8530;
    printf("num: %d, y: %d\n", num, *z);
    printf("------------------END BSP_Accel_GetZ()---------------\n ");

    return BSP_ACCEL_OK;
}