#include "gyro_driver.h"


uint8_t BSP_Gyro_HW_Initalize(void)
{
    printf("----------------START BSP_Gyro_HW_Initalize()--------------------------\n");
    printf("----------------END BSP_Gyro_HW_Initalize--------------------------\n\n");
    
    return BSP_GYRO_OK;
}

uint8_t BSP_Gyro_ChkConnect(uint8_t num)
{
    printf("------------------START BSP_Gyro_ChkConnect()---------------\n ");
    printf("num: %d\n", num);
    printf("------------------END BSP_Gyro_ChkConnect()---------------\n ");
    
    return BSP_GYRO_CONNECTED;
}

uint8_t BSP_Gyro_SetReolution(uint8_t num, uint8_t resolution)
{
    printf("------------------START BSP_Gyro_SetReolution()---------------\n ");
    printf("num: %d, resolution: %d\n", num, resolution);
    printf("------------------END BSP_Gyro_SetReolution()---------------\n ");
    
    return BSP_GYRO_OK;
}

uint8_t BSP_Gyro_SetCaptureFreq(uint8_t num, uint32_t freq)
{
    printf("------------------START BSP_Gyro_SetCaptureFreq()---------------\n ");
    printf("num: %d, frequency: %d\n", num, freq);
    printf("------------------END BSP_Gyro_SetCaptureFreq()---------------\n ");
    
    return BSP_GYRO_OK;
}
uint8_t BSP_Gyro_SetCommunicateFreq(uint8_t num, uint32_t freq)
{
    printf("------------------START BSP_Gyro_SetCommunicateFreq()---------------\n ");
    printf("num: %d, frequency: %d\n", num, freq);
    printf("------------------END BSP_Gyro_SetCommunicateFreq()---------------\n ");
    
    return BSP_GYRO_OK;
}

uint8_t BSP_Gyro_GetX(uint8_t num, int32_t *p_x)
{
    printf("------------------START BSP_Gyro_GetX()---------------\n ");
    *p_x=123;
    printf("num: %d, x: %d\n", num, *p_x);
    printf("------------------END BSP_Gyro_GetX()---------------\n ");
    
    return BSP_GYRO_OK;
}

uint8_t BSP_Gyro_GetY(uint8_t num, int32_t *p_y)
{
    printf("------------------START BSP_Gyro_GetY()---------------\n ");
    *p_y=510;
    printf("num: %d, y: %d\n", num, *p_y);
    printf("------------------END BSP_Gyro_GetY()---------------\n ");

    return BSP_GYRO_OK;
}

uint8_t BSP_Gyro_GetZ(uint8_t num, int32_t *p_z)
{
    printf("------------------START BSP_Gyro_GetZ()---------------\n ");
    *p_z=8530;
    printf("num: %d, y: %d\n", num, *p_z);
    printf("------------------END BSP_Gyro_GetZ()---------------\n ");

    return BSP_GYRO_OK;
}